/* timeout: set time limit on a process*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

int pid;	/* child process id */
char *progname;

void onalarm(int);	/* kill child when alarm arrives */
void error(char *s1, char *s2);

int main(int argc, char *argv[])
{
	int sec = 10, status;

	progname = argv[0];
	if (argc > 1 && argv[1][0] == '-') {
		sec = atoi(&argv[1][1]);
		argc--;
		argv++;
	}

	if (argc < 2)
		error("Usage: %s [-10] command\n", progname);
	if ((pid = fork()) == 0) {
		execvp(argv[1], &argv[1]);
		error("couldn't start %s", argv[1]);
	}
	signal(SIGALRM, onalarm);
	alarm(sec);
	if (wait(&status) == -1 || (status & 0177) != 0)
		error("%s killed", argv[1]);
	return (status >> 8) & 0x3777;
}

void onalarm(int i)
{
	kill(pid, SIGKILL);
}

void error(char *s1, char *s2)
{
	if (progname)
		fprintf(stderr, "%s: ", progname);
	fprintf(stderr, s1, s2);
	if (errno > 0 && errno < sys_nerr)
		fprintf(stderr, " (%s)", sys_errlist[errno]);
	fprintf(stderr, "\n");
	exit(1); 
}

