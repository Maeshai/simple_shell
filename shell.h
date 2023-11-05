#ifndef SHELL_H_
#define SHELL_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

extern char **environ;

/** function prototypes **/

/* Error handling */
void cant_find(char *arv, int dsh, char *comnd);
void invalid_num(char *arv, int dsh, char *numb);
void error_perm(char *arv, int dsh, char *comnd);

/* Environment-related */
char *fetch_env(char *env_lbl);
void outpt_env(char **);
char *g_evr(char *env_lbl);

/* Input/output utilities */
void mk_cnvrt(int t);
void cpchar(char c);
void sps(char *s);
void pchar(char c);
void ps(char *s);

/* String manipulation utilities */
int slen(const char *s);
char *scopy(char *de, const char *sr);
char *scncat(char *de,const char *sr);
int scmp(const char *st1, const char *st2);

/* Command execution & tokenization */
char **tknize(char *strng);
char *g_comnd(char *comnd);
void tkn_free(char **tkn);
void ext_sh(char **tkn, char **arv, int dsh, int stats, char *bufr);
int c_evr(char **tkn, char **env, char *bufr);
char **g_tkn(char **bufr, int stats);
int exe_comnd(char **tkn, char **arv, int dsh, char **env);
int mk_asctoint(const char *s);

#endif
