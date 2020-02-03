/*
 * Negative-nice wrapper
 * A little wrapper wich sets the priority of "prog" nagative
 * Written by Menno Duurma.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>

/* We need this for geteuid() */
#include <sys/types.h>

/* We need these for setpriority  */
#include <sys/time.h>
#include <sys/resource.h>

/* Let's get to it */
int main(int argc, char *argv[], char *envp[])
{

    /* Path to the program to exec */
    char prog[] = "/usr/libexec/Xorg";

    int i;
    char *buf;

    buf = getenv("X_NICE");

    /*
     * See: /usr/src/linux/Documentation/prctl/no_new_privs.txt
     */
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1) {
        fprintf(stderr, "Error: no_new_privs = %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "no_new_privs = %d\n",
            prctl(PR_GET_NO_NEW_PRIVS, 0, 0, 0, 0));

    if (buf == NULL) {
	fprintf(stderr, "X_NICE is unset\n");
	fprintf(stderr, "Defaulting to: 0\n");
	i = 0;
    } else {
	i = atoi(&buf[0]);
	if ((i < -20) || (i > 19)) {
	    fprintf(stderr, "X_NICE must be between -20 and 19\n");
	    fprintf(stderr, "Defaulting to: 0\n");
	    i = 0;
	}
    }

    /* See if we where called correctly */
    if ((i < 0) && (geteuid() != 0)) {
	fprintf(stderr, "Error - X_NICE = %d,  you're not root.", i);
	fprintf(stderr, "Try setting this wrapper SUID to root.");
	fprintf(stderr, "Defaulting to: 0.\n");
	i = 0;
    }

    /* Lets try to make it run faster */
    if (setpriority(PRIO_PROCESS, 0, i) == -1) {
	fprintf(stderr, "Failed to set nice valve %d - %s\n", i,
		strerror(errno));
	fprintf(stderr, "Defaulting to: 0.\n");
    }

    /* Tell the viewers wat is going to happen */
    fprintf(stderr, "Starting %s with priority %d\n", prog, i);

    /* Lets fire up the basterd */
    if (execve(prog, argv, envp) == -1) {
	fprintf(stderr, "Failed to exec %s - %s\n", prog, strerror(errno));
	exit(1);
    }

    return 0;
}
