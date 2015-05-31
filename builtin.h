/**
 * Anythings about built-in commands
 *
 */
#ifndef BUILTIN_H
#define BUILTIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "define.h"

/* TODO Defined job_t in this way cannot support multiple processes in a job */
struct job_t {              /* The job struct */
    pid_t pid;              /* job PID */
    int jid;                /* job ID [1, 2, ...] */
    int state;              /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE];  /* command line */
};

extern struct job_t jobs[MAXJOBS];

/**
 * cmd_fn is a function return int and require char** as its arg
 */
typedef void (cmd_fn)(char **);

/**
 * struct represents a builit-in command
 */
struct cmd_struct {
    char *cmd;
    cmd_fn* fn;
    char **argv;
};

/** Forward declarations **/
cmd_fn cmd_quit;
cmd_fn cmd_fg;
cmd_fn cmd_bg;
cmd_fn cmd_jobs;

void listjobs(struct job_t *jobs);
/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid);

/*
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv);

/** End forward declarations **/

/**
 * Array of built-in commands
 */
struct cmd_struct builtins[] = {
    {"quit", cmd_quit, NULL},
    {"jobs", cmd_jobs, NULL},
    {"bg", cmd_bg, NULL},
    {"fg", cmd_fg, NULL}
};

struct cmd_struct* getbuiltin(const char* cmd)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(builtins); ++i)
    {
        struct cmd_struct* p = builtins + i;
        if (!strcmp(p->cmd, cmd)) {
            return p;
        }
    }
    return NULL;
}

int is_builtin(char *cmd)
{
    return !!getbuiltin(cmd);
}

/* Builtin command implementations */

/**
 * quit
 * terminates the shell
 */
void cmd_quit(char **argv) {
    exit(0);
}

/**
 * jobs
 * list all background jobs
 */
void cmd_jobs(char **argv) {
    listjobs(jobs);
}

/**
 * bg <job>
 * restarts <job> by sending it a SIGCONT signal, and then runs it in the
 * background. The <job> can be either PID or JID
 */
void cmd_bg(char **argv) {
    do_bgfg(argv);
}

/**
 * fg <job>
 * restarts <job> by sending it a SIGCONT signal, and then runs it in the
 * foreground. The <job> can be either PID or JID
 */
void cmd_fg(char **argv) {
    do_bgfg(argv);
}





#endif
