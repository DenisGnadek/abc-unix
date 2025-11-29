/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1991. */

/* bvis.h: Public declarations for Visible Procedures */

/* b1grab.c */
Visible Procedure release(value v);
Visible Procedure uniql(value *ll);
Visible Procedure regrab(value *v, intlet len);
Visible Procedure rrelease(value v);

/* b1file.c */
Visible Procedure free_path(char *path);
Visible Procedure endfile(void);

/* b1memo.c */
Visible Procedure regetmem(ptr *v, unsigned syze);
Visible Procedure freemem(ptr p);
Visible Procedure bufpush(bufadm *bp, char c);
Visible Procedure bufcpy(bufadm *bp, char *s);
Visible Procedure bufreinit(bufadm *bp);
Visible Procedure bufinit(bufadm *bp);
Visible Procedure buffree(bufadm *bp);
Visible Procedure bufncpy(bufadm *bp, char *s, int len);

/* b1mess.c */
Visible Procedure putmess(int m);
Visible Procedure freemem(ptr p);
Visible Procedure putSmess(int m, string s);
Visible Procedure putDSmess(int m, int d, string s);
Visible Procedure initmess(void);
Visible Procedure endmess(void);
Visible Procedure put2Cmess(int m, char c1, char c2);

/* b1outp.c */
Visible Procedure c_putstr(string s);
Visible Procedure c_putdata(string data);
Visible Procedure c_putnewline(void);
Visible Procedure c_flush(void);
Visible Procedure init_interpreter_output(int height, int width);
Visible Procedure re_interpreter_output(void);
Visible Procedure putnewline(FILE *file);
Visible Procedure putstr(FILE *file, string s);
Visible Procedure doflush(FILE *file);
Visible Procedure putchr(FILE *file, char c);

/* e1cell.c */
Visible Procedure discard(register cell *p);

/* e1comm.c */
Visible Procedure abced_file(string filename, intlet errline, literal kind, bool creating, bool *changed);
Visible Procedure initbed(void);
Visible Procedure endbed(void);

/* e1deco.c*/
Visible Procedure delfocus(register path *pp);

/* e1edoc.c */
Visible Procedure dumpev(register environ *ep, string m);
Visible Procedure clrenv(environ *ep);
Visible Procedure higher(register environ *ep);
Visible Procedure dbmess(register environ *ep);

/* e1erro.c*/
Visible Procedure ederr(int m);
Visible Procedure ederrS(int m, string s);
Visible Procedure ederrC(int m, char c);
Visible Procedure edmessage(string s);
Visible Procedure asserr(string file, int line);
Visible Procedure debug(string fmt, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
Visible Procedure stsline(int totlines, int topline, int scrlines, value copybuffer, bool recording);
Visible Procedure enderro(void);
Visible Procedure init_erro(void);
Visible Procedure end_erro(void);

/* e1eval.c*/
Visible Procedure evalcoord(register node n, register int jch, int *py, int *px, int *plevel);

/* e1getc.c*/
Visible Procedure initgetc(void);
Visible Procedure endgetc(void);
Visible Procedure pollinterrupt(void);
Visible Procedure initkeys(void);
Visible Procedure initoperations(void);
Visible Procedure undefine(int code, int deflen, string def);


/* e1goto.c*/
Visible Procedure gotofix(environ *ep, int y, int x);

/* e1gram.c*/
Visible Procedure setroot(int isym);
Visible Procedure initgram(void);
Visible Procedure initkeys(void);
Visible Procedure initclasses(void);
Visible Procedure endnoderepr(void);

/* e1line.c*/
Visible Procedure oneline(register environ *ep);

/* e1node.c*/
Visible Procedure setchild(register node *pn, register int i, register node n);
Visible Procedure markpath(register path *pp, register markbits new);
Visible Procedure unmkpath(register path *pp, register int del);
Visible Procedure treereplace(register path *pp, register node n);
Visible Procedure top(register path *pp);
Visible Procedure touchpath(register path *pp);
Visible Procedure putintrim(register value *pn, register int head, register int tail, register string str);

/* e1outp.c*/
Visible Procedure startactupdate(bool nofocus);
Visible Procedure outline(register cell *p, register int lineno);
Visible Procedure endactupdate(void);
Visible Procedure savefocus(register environ *ep);
Visible Procedure setfocus(register cell *tops);

/* e1que1.c*/
Visible Procedure preptoqueue(node n, register queue *pq);
Visible Procedure addtoqueue(register queue *pq, register node n);
Visible Procedure stringtoqueue(register string str, register queue *pq);
Visible Procedure splitnode(register node n, register queue *pq);
Visible Procedure nosuggtoqueue(register environ *ep, queue *pq);
Visible Procedure fixfocus(register environ *ep, register int len);
Visible Procedure subsettoqueue(register node n, register int s1, register int s2, register queue *pq);

/* e1que2.c*/
Visible Procedure qshow(queue q, string where);

/* e1scrn.c*/
Visible Procedure actupdate(value copybuffer, bool recording, bool lasttime);
Visible Procedure virtupdate(environ *oldep, environ *newep, int highest);
Visible Procedure initterm(void);
Visible Procedure endterm(void);
Visible Procedure endshow(void);
Visible Procedure setindent(int x);
Visible Procedure cmdprompt(string prompt);

/* e1spos.c */
Visible Procedure initpos(void);
Visible Procedure endpos(void);
Visible Procedure delpos(char *fname);
Visible Procedure movpos(char *ofname, char *nfname);

/* e1sugg.c */
Visible Procedure addsugg(string str, int builtin);
Visible Procedure acksugg(environ *ep);
Visible Procedure killsugg(environ *ep, string *pstr);
Visible Procedure ackhowsugg(environ *ep);
Visible Procedure killhowsugg(environ *ep);
Visible Procedure check_last_unit(environ *ep, int curr);
Visible Procedure readsugg(path p);
Visible Procedure writesugg(path p);
Visible Procedure initcensugg(void);
Visible Procedure initsugg(void);
Visible Procedure endsugg(void);
Visible Procedure endclasses(void);

/* e1supr.c */
Visible Procedure subgrow(register environ *ep, bool ignorespaces, bool deleting);
Visible Procedure subgrsubset(register environ *ep, bool ignorespaces);
Visible Procedure shrsubset(register environ *ep);
Visible Procedure ritevhole(register environ *ep);
Visible Procedure leftvhole(register environ *ep);
Visible Procedure s_up(register environ *ep);
Visible Procedure s_downi(register environ *ep, register int i);
Visible Procedure grow(environ *ep, bool deleting);
Visible Procedure shrink(register environ *ep);
Visible Procedure s_down(register environ *ep);
Visible Procedure s_downrite(register environ *ep);
Visible Procedure fixit(register environ *ep);

/* i1nua.c */
Visible Procedure app_print(FILE *fp, real v);

/* i1nuc.c */
Visible Procedure printnum(FILE *fp, value v);

/* i1num.c */
Visible Procedure initapp(void);
Visible Procedure endapp(void);
Visible Procedure initnum(void);
Visible Procedure endnum(void);
Visible Procedure set_random(value v);

/* i1nur.c */
Visible Procedure rat_init(void);
Visible Procedure endrat(void);

/* i1tra.c */
Visible Procedure ins_range(value lwb, value upb, value *pl);

/* i2ana.c */
Visible Procedure analyze(parsetree t, value *targs);
Visible Procedure cleanup(void);

/* i2dis.c */
Visible Procedure display(FILE *file, parsetree v, bool one_line);

/* i2exp.c */
Visible Procedure do_dya(expadm *adm, parsetree v);
Visible Procedure reduce(expadm *adm);
Visible Procedure selection(txptr q, parsetree *v);
Visible Procedure initexp(expadm *adm, int n, char level);
Visible Procedure endstack(expadm *adm);
Visible Procedure push_item(expadm *adm, parsetree v);
Visible Procedure trim_target(txptr q, parsetree *v);

/* i2fix.c */
Visible Procedure f_eunparsed(parsetree *pt);
Visible Procedure f_cunparsed(parsetree *pt);
Visible Procedure f_trim_target(parsetree v, char trim);

/* i2gen.c */
Visible Procedure jumpto(parsetree t);
Visible Procedure fix(parsetree *pt, char flag);
Visible Procedure hold(struct state *pl);
Visible Procedure let_go(struct state *pl);
Visible Procedure fix_nodes(parsetree *pt, parsetree *code);

/* i2syn.c */
Visible Procedure skipsp(txptr *tx0);
Visible Procedure findceol(void);
Visible Procedure req(string s, txptr q, txptr *ftx, txptr *ttx);
Visible Procedure upto(txptr q, string s);
Visible Procedure need(string s);
Visible Procedure veli(void);
Visible Procedure upto1(txptr q, int m);
Visible Procedure initsyn(void);
Visible Procedure endsyn(void);
Visible Procedure first_ilev(void);

/* i3bws.c */
Visible Procedure lst_wss(void);
Visible Procedure goto_ws(void);
Visible Procedure initbws(void);
Visible Procedure endbws(void);

/* i3com.c */
Visible Procedure idelpos(value fname);
Visible Procedure imovpos(value ofname, value nfname);

/* i3env.c */
Visible Procedure setprmnv(void);
Visible Procedure sv_context(context *sc);
Visible Procedure set_context(context *sc);
Visible Procedure initenv(void);
Visible Procedure endenv(void);
Visible Procedure e_replace(value v, value *t, value k);
Visible Procedure e_delete(value *t, value k);
Visible Procedure re_env(void);
Visible Procedure lst_ttgs(void);
Visible Procedure initprmnv(void);
Visible Procedure extbnd_tags(value btl, envtab et);
Visible Procedure sethowtoname(value v);

/* i3err.c */
Visible Procedure bye(int ex);
Visible Procedure immexit(int status);
Visible Procedure putserr(string s);
Visible Procedure flusherr(void);
Visible Procedure syserr(int m);
Visible Procedure memexh(void);
Visible Procedure pprerrV(int m, value v);
Visible Procedure pprerr(int m);
Visible Procedure parerrV(int m, value v);
Visible Procedure parerr(int m);
Visible Procedure fixerrV(int m, value v);
Visible Procedure fixerr(int m);
Visible Procedure interr(int m);
Visible Procedure int_signal(void);
Visible Procedure putsSerr(string fmt, string s);
Visible Procedure putsDSerr(string fmt, int d, string s);
Visible Procedure puts2Cerr(string fmt, char c1, char c2);
Visible Procedure putsCerr(string fmt, char c);
Visible Procedure interrV(int m, value v);
Visible Procedure initfmt(void);
Visible Procedure initerr(void);
Visible Procedure re_errfile(void);
Visible Procedure checkerr(void);
Visible Procedure typerrV(int m, value v);

/* i3fil.c */
Visible Procedure f_delete(char *file);
Visible Procedure f_close(FILE *usrfile);
Visible Procedure f_rename(value fname, value nfname);

/* i3fpr.c */
Visible Procedure initfpr(void);
Visible Procedure endfpr(void);

/* i3imm.c */
Visible Procedure process(void);

/* i3ini.c */
Visible Procedure endall(void);
Visible Procedure pre_init(void);
Visible Procedure checkfileargs(int argc, char **argv);
Visible Procedure init(void);
Visible Procedure abc(int argc, char **argv);
Visible Procedure crashend(void);

/* i3int.c */
Visible Procedure execthread(parsetree start);

/* i3in2.c */
Visible Procedure load_global(value v, value name, bool err);
Visible Procedure nl(value n);

/* i3loc.c */
Visible Procedure check_location(loc l);
Visible Procedure put(value v, loc l);
Visible Procedure put_with_check(value v, loc l);
Visible Procedure l_delete(loc l);
Visible Procedure l_insert(value v, loc l);
Visible Procedure l_remove(value v, loc l);
Visible Procedure bindlocation(loc l);
Visible Procedure unbind(loc l);
Visible Procedure l_del(loc l);

/* i3scr.c */
Visible Procedure flushout(void);
Visible Procedure wri(FILE *fp, value v, bool coll, bool outer, bool perm);
Visible Procedure oline(void);
Visible Procedure writ(value v);
Visible Procedure writnewline(void);
Visible Procedure read_eg(loc l, btype t);
Visible Procedure read_raw(loc l);
Visible Procedure re_screen(void);
Visible Procedure init_scr(void);
Visible Procedure end_scr(void);
Visible Procedure re_outfile(void);
Visible Procedure vs_ifile(void);

/* i3sou.c */
Visible Procedure del_target(value name);
Visible Procedure putval(value v, char *dir, char *name, literal ct, bool silently);
Visible Procedure puttarval(value v, char *dir, value fname, value tname, bool silently);
Visible Procedure put_perm(void);
Visible Procedure create_unit(void);
Visible Procedure edit_unit(void);
Visible Procedure edit_target(void);
Visible Procedure initperm(void);
Visible Procedure endperm(void);
Visible Procedure initsou(void);
Visible Procedure endsou(void);
Visible Procedure lst_uhds(void);
Visible Procedure rem_unit(parsetree u, wsenvptr wse);
Visible Procedure def_target(value name, value t);
Visible Procedure clear_perm(void);

/* i3sta.c */
Visible Procedure push(value v);
Visible Procedure ret(void);
Visible Procedure call_refinement(value name, parsetree def, bool test);
Visible Procedure x_user_command(value name, parsetree actuals, value def);
Visible Procedure endsta(void);

/* i3typ.c */
Visible Procedure must_agree(btype t, btype u, int m);

/* e1etex.c */
Visible Procedure e_fstrval(string s);
Visible Procedure e_concto(value *s, value t);

/* i1btr.c */
Visible Procedure relbtree(btreeptr pnode, literal it);
Visible Procedure uniqlbtreenode(btreeptr *pptr, literal it);

/* i1obj.c */
Visible Procedure rel_subvalues(value v);

/* i1tex.c */
Visible Procedure endstrval(void);
Visible Procedure fstrval(string s);
Visible Procedure concato(value *v, value t);
Visible Procedure convtext(void (*outproc)(void), value v, char quote);

/* i1lta.c */
Visible Procedure cpynptrs(btreeptr *to, btreeptr *from, int n);
Visible Procedure movnitms(itemptr to, itemptr from, intlet n, intlet iw);
Visible Procedure cpynitms(itemptr to, itemptr from, intlet n, intlet it);

/* i2tca.c */
Visible Procedure type_check(parsetree v);
Visible Procedure initstc(void);
Visible Procedure endstc(void);
Visible Procedure del_types(void);
Visible Procedure adjust_types(bool no_change);
Visible Procedure rectypes(void);
Visible Procedure put_types(void);

/* i2tce.c */
Visible Procedure start_vars(void);
Visible Procedure add_var(polytype tvar);
Visible Procedure end_vars(void);
Visible Procedure setreprtable(void);
Visible Procedure starterrvars(void);
Visible Procedure enderrvars(void);
Visible Procedure badtyperr(polytype a, polytype b);
Visible Procedure delreprtable(void);
Visible Procedure adderrvar(polytype t);

/* i2tcp.c */
Visible Procedure putsubtype(polytype sub, polytype u, intlet isub);
Visible Procedure new_externals(void);
Visible Procedure p_release(polytype u);
Visible Procedure repl_type_of(polytype u, polytype p);
Visible Procedure usetypetable(value t);
Visible Procedure deltypetable(void);
Visible Procedure initpol(void);
Visible Procedure endpol(void);

/* i2tcu.c */
Visible Procedure unify(polytype a, polytype b, polytype *pu);

/* i4bio.c */
Visible Procedure abcio(int type, char *tabname);
Visible Procedure bioerr(int m);
Visible Procedure bioerrV(int m, value v);

/* i4grp.c */
Visible Procedure rec_wsgroup(void);

/* i4inp.c */
Visible Procedure abcinput(char *name_arg);

/* i4lis.c */
Visible Procedure abclist(FILE *ofp);

/* i4out.c */
Visible Procedure abcoutput(char *name_arg);

/* i4pack.c */
Visible Procedure abcpack(FILE *ofp);

/* i4rec.c */
Visible Procedure rec_workspace(void);
Visible Procedure rec_suggestions(void);

/* trm.c */
Visible int trmstart(int *plines, int *pcols, int *pflags);
Visible Procedure trmend(void);
Visible Procedure trmundefined(void);
Visible Procedure trmsense(string sense, string format, int *py, int *px);
Visible Procedure trmputdata(int yfirst, int ylast, register int indent, register string data, register string mode);
Visible Procedure trmscrollup(register int yfirst, register int ylast, register int by);
Visible Procedure trmsync(int y, int x);
Visible Procedure trmbell(void);
Visible Procedure trmshow(char *s);
Visible int trminput(void);
Visible int trmavail(void);
Visible int trmsuspend(void);
