/**
 * Prototypes for built-in commands
 *
 */
#ifndef BUILTIN_H
#define BUILTIN_H
#include <string.h>

int is_builtin(char *cmd)
{
    /* last char should be '\0' */
    if (NULL != cmd && '\0' == cmd[strlen(cmd)]
            && 0 == strcmp("quit", cmd))
        return 1;

    return 0;
}

extern int cmd_quit(int argc, char **argv);



#endif
