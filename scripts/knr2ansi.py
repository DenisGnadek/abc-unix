#!/usr/bin/env python3
"""Convert K&R-style function definitions to ANSI prototypes in-place.

Given one or more C source files, this script searches for functions that use
old-style (K&R) parameter declarations and rewrites their signatures to modern
ANSI form. Only the function header is touched; the body stays untouched.

Usage:
    python scripts/knr2ansi.py path/to/file.c [more.c ...]

Use --dry-run to see which functions would change without editing files.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

_IDENTIFIER_RE = re.compile(r"[A-Za-z_][0-9A-Za-z_]*")
_KEYWORDS = {"if", "for", "while", "switch", "case", "return"}


def _strip_c_comments(text: str) -> str:
    """Remove /* ... */ and // ... comments from a snippet."""
    result: List[str] = []
    i = 0
    length = len(text)
    while i < length:
        ch = text[i]
        nxt = text[i + 1] if i + 1 < length else ""
        if ch == "/" and nxt == "*":
            end = text.find("*/", i + 2)
            if end == -1:
                break
            i = end + 2
            continue
        if ch == "/" and nxt == "/":
            end = text.find("\n", i + 2)
            if end == -1:
                break
            i = end
            continue
        result.append(ch)
        i += 1
    return "".join(result)


def _split_param_names(param_chunk: str) -> List[str]:
    cleaned = _strip_c_comments(param_chunk)
    names = [item.strip() for item in cleaned.split(",")]
    return [name for name in names if name]


def _split_declarators(text: str) -> List[str]:
    decls: List[str] = []
    current: List[str] = []
    depth_paren = depth_bracket = 0
    for ch in text:
        if ch == "," and depth_paren == depth_bracket == 0:
            piece = "".join(current).strip()
            if piece:
                decls.append(piece)
            current = []
            continue
        current.append(ch)
        if ch == "(":
            depth_paren += 1
        elif ch == ")":
            depth_paren = max(0, depth_paren - 1)
        elif ch == "[":
            depth_bracket += 1
        elif ch == "]":
            depth_bracket = max(0, depth_bracket - 1)
    tail = "".join(current).strip()
    if tail:
        decls.append(tail)
    return decls


def _extract_name(decl: str, candidates: Sequence[str]) -> Optional[str]:
    cand_set = set(candidates)
    match_name: Optional[str] = None
    for match in _IDENTIFIER_RE.finditer(decl):
        token = match.group(0)
        if token in cand_set:
            match_name = token
    if match_name:
        return match_name
    identifiers = _IDENTIFIER_RE.findall(decl)
    return identifiers[-1] if identifiers else None


def _split_base_and_decls(statement: str, name_regex: re.Pattern[str]) -> Optional[Tuple[str, str]]:
    stmt = statement.strip()
    if stmt.endswith(";"):
        stmt = stmt[:-1]
    match = name_regex.search(stmt)
    if not match:
        return None
    base = stmt[: match.start()].rstrip()
    decls = stmt[match.start():]
    ptr_prefix = []
    while base.endswith("*"):
        ptr_prefix.append("*")
        base = base[:-1].rstrip()
    decls = "".join(reversed(ptr_prefix)) + decls
    return base.strip(), decls.strip()


def _parse_param_block(block: str, param_names: Sequence[str]) -> Optional[Dict[str, str]]:
    if not param_names:
        return {}
    stripped = block.strip()
    if not stripped:
        return None
    if any(symbol in stripped for symbol in "{}"):
        return None
    lowered = stripped.lower()
    if any(keyword in lowered for keyword in _KEYWORDS):
        return None
    if "=" in stripped or "#" in stripped:
        return None
    if ";" not in stripped:
        return None

    pattern = re.compile(r"\b(" + "|".join(re.escape(name) for name in param_names) + r")\b")
    mapping: Dict[str, str] = {}
    for raw in stripped.split(";"):
        stmt = raw.strip()
        if not stmt:
            continue
        split_result = _split_base_and_decls(stmt + ";", pattern)
        if not split_result:
            continue
        base, decls = split_result
        if not base:
            continue
        for decl in _split_declarators(decls):
            name = _extract_name(decl, param_names)
            if not name:
                continue
            type_with_name = f"{base} {decl}".strip()
            mapping[name] = " ".join(type_with_name.split())
    if len(mapping) != len(param_names):
        missing = [name for name in param_names if name not in mapping]
        if missing:
            return None
    return mapping


def _skip_whitespace_and_comments(text: str, start: int) -> int:
    i = start
    length = len(text)
    while i < length:
        ch = text[i]
        nxt = text[i + 1] if i + 1 < length else ""
        if ch in " \t\r\n":
            i += 1
            continue
        if ch == "/" and nxt == "*":
            end = text.find("*/", i + 2)
            if end == -1:
                return length
            i = end + 2
            continue
        if ch == "/" and nxt == "/":
            end = text.find("\n", i + 2)
            if end == -1:
                return length
            i = end + 1
            continue
        break
    return i


def _skip_string_literal(text: str, start: int) -> int:
    quote = text[start]
    i = start + 1
    length = len(text)
    while i < length:
        ch = text[i]
        if ch == "\\":
            i += 2
            continue
        if ch == quote:
            return i + 1
        i += 1
    return length


def _find_matching_paren(text: str, open_idx: int) -> Optional[int]:
    depth = 1
    i = open_idx + 1
    length = len(text)
    while i < length and depth > 0:
        ch = text[i]
        if ch == "(":
            depth += 1
            i += 1
            continue
        if ch == ")":
            depth -= 1
            i += 1
            continue
        if ch in {'"', "'"}:
            i = _skip_string_literal(text, i)
            continue
        i += 1
    return i - 1 if depth == 0 else None


def _collect_prefix_start(text: str, line_start: int) -> int:
    start = line_start
    while True:
        prev_newline = text.rfind("\n", 0, start - 1)
        if prev_newline == -1:
            return 0
        candidate = text[prev_newline + 1 : start]
        stripped = candidate.strip()
        if not stripped:
            return start
        if any(ch in stripped for ch in "();{}"):
            return start
        if (stripped.startswith("#") or stripped.startswith("/*")
            or stripped.startswith("*") or stripped.startswith("//")):
            return start
        start = prev_newline + 1


def _convert_one(text: str, open_idx: int) -> Optional[Tuple[int, int, str, str]]:
    j = open_idx - 1
    while j >= 0 and text[j].isspace():
        j -= 1
    if j < 0 or not (text[j].isalnum() or text[j] == "_"):
        return None
    name_end = j + 1
    while j >= 0 and (text[j].isalnum() or text[j] == "_"):
        j -= 1
    name_start = j + 1
    if j >= 0 and text[j] in ".>":
        if text[j] == ">" and j - 1 >= 0 and text[j - 1] == "-":
            return None
        if text[j] == ".":
            return None
    params_end = _find_matching_paren(text, open_idx)
    if params_end is None:
        return None
    params_chunk = text[open_idx + 1 : params_end]
    after_params = _skip_whitespace_and_comments(text, params_end + 1)
    between_header_and_block = text[params_end + 1 : after_params]
    if between_header_and_block.strip() == "":
        if "\n" in between_header_and_block:
            between_header_and_block = "\n"
        else:
            between_header_and_block = between_header_and_block[:1]
    if after_params >= len(text):
        return None
    next_char = text[after_params]
    if next_char in ";[":
        return None
    if next_char == "{":
        return None
    brace_idx = text.find("{", after_params)
    if brace_idx == -1:
        return None
    decl_block = text[after_params:brace_idx]
    param_names = _split_param_names(params_chunk)
    if not param_names and decl_block.strip():
        return None
    mapping = _parse_param_block(decl_block, param_names)
    if mapping is None and param_names:
        return None

    line_start = text.rfind("\n", 0, name_start) + 1
    prefix_start = _collect_prefix_start(text, line_start)
    prefix_section = text[prefix_start:name_start]
    indent_match = re.match(r"\s*", text[line_start:name_start])
    indent = indent_match.group(0) if indent_match else ""
    prefix_tokens = " ".join(prefix_section.strip().split())
    if not prefix_tokens:
        prefix_core = indent + "int"
    else:
        prefix_core = indent + prefix_tokens
    if not prefix_core.endswith((" ", "\t")):
        prefix_core += " "

    if param_names:
        try:
            ordered = [mapping[name] for name in param_names]
        except KeyError:
            return None
        new_param_list = ", ".join(ordered)
    else:
        new_param_list = "void"

    header_start = prefix_start
    decl_block_end = after_params + len(decl_block)
    trailing_ws = text[decl_block_end:brace_idx]
    fn_name = text[name_start:name_end]
    new_header = f"{prefix_core}{fn_name}({new_param_list})"
    replacement = new_header + between_header_and_block + trailing_ws
    original = text[header_start:brace_idx]
    return header_start, brace_idx, replacement, original


def convert_text(text: str) -> Tuple[str, int]:
    i = 0
    pieces: List[str] = []
    last = 0
    conversions = 0
    length = len(text)
    while i < length:
        idx = text.find("(", i)
        if idx == -1:
            break
        result = _convert_one(text, idx)
        if not result:
            i = idx + 1
            continue
        start, end, replacement, _ = result
        if start < last:
            i = idx + 1
            continue
        pieces.append(text[last:start])
        pieces.append(replacement)
        last = end
        conversions += 1
        i = end
    pieces.append(text[last:])
    return "".join(pieces), conversions


def process_file(path: Path, dry_run: bool) -> int:
    try:
        text = path.read_text()
    except OSError as exc:
        print(f"error: cannot read {path}: {exc}", file=sys.stderr)
        return 0
    new_text, count = convert_text(text)
    if count and not dry_run:
        path.write_text(new_text)
    return count


def main(argv: Optional[Sequence[str]] = None) -> int:
    parser = argparse.ArgumentParser(description="Convert K&R function definitions to ANSI prototypes")
    parser.add_argument("files", nargs="+", type=Path, help="C source files to rewrite")
    parser.add_argument("--dry-run", action="store_true", help="Show how many functions would change without editing files")
    args = parser.parse_args(argv)

    total = 0
    for file_path in args.files:
        count = process_file(file_path, args.dry_run)
        total += count
        if count:
            action = "would convert" if args.dry_run else "converted"
            print(f"{file_path}: {action} {count} function(s)")
        else:
            print(f"{file_path}: no K&R definitions found")
    return 0 if total or args.dry_run else 0


if __name__ == "__main__":
    sys.exit(main())
