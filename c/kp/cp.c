/* cp: minimal version */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0644	/* RW for owner, R for group and others */
char *progname;

void error(char *s1, char *s2);	/* print error message and die */

int main(int argc, char *argv[])
{
	int f1, f2, n;
	char buf[BUFSIZ];

	progname = argv[0];
	if (argc != 3)
		error("Usage: %s for to", progname);
	if ((f1 = open(argv[1], 0)) == -1)
		error("can't open %s", argv[1]);
	if ((f2 = creat(argv[2], PERMS)) == -1)
		error("can't create %s", argv[2]);

	while ((n = read(f1, buf, sizeof buf)) > 0)
		if (write(f2, buf, n) != n)
			error("write error", (char *)0);

	return 0;
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

