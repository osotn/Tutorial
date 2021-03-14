/* zap: interactive process killer */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

char	*progname;	/* program name for error message */
char 	*ps = "ps -ag";

int strindex(char *s, char *t); 	/* return index of t in s, -1 if none  */
int ttyin(void);			/* process response form /dev/tty */
FILE *efopen(char *file, char *mode);	/* fopen file, die if can't */

int main(int argc, char *argv[])
{
	int pid;
	FILE *fin;
	char buf[BUFSIZ];

	progname = argv[0];

	if ((fin = popen(ps, "r")) == NULL) {
		fprintf(stderr, "%s: can't run %s\n", progname, ps);
		return -1;
	}

	fgets(buf, sizeof buf, fin);	/* get header line */
	fprintf(stderr, "%s", buf);
	while (fgets(buf, sizeof buf, fin) != NULL)
		if (argc == 1 || strindex(buf, argv[1]) >= 0) {
  			buf[strlen(buf) - 1] = '\0';	/* drop newline */
			fprintf(stderr, "%s? ", buf);
			if (ttyin() == 'y') {
				sscanf(buf, "%d", &pid);
				kill(pid, SIGKILL);
			}
		}
	
	return 0;
}

int strindex(char *s, char *t)
{
	int i, n;

	n = strlen(t);
	for (i = 0; s[i] != '\0'; i++)
		if (strncmp(s+i, t, n) == 0)
			return i;

	return -1;
}

int ttyin(void)
{
        char buf[BUFSIZ];
        static FILE *tty = NULL;

        if (tty == NULL)
                tty = efopen("/dev/tty", "r");

        for (;;) {
                if (fgets(buf, sizeof buf, tty) == NULL || buf[0] == 'q')
                        exit(0);
                else if (buf[0] == '!') {
                        system(buf + 1);        /* BUG here */
                        printf("!\n");
                }
                else
                        return buf[0];
        }
}

FILE *efopen(char *file, char *mode)
{
	FILE *fp;

	if ((fp = fopen(file, mode)) != NULL)
		return fp;

	fprintf(stderr, "%s: can't open file %s mode %s\n",
		progname, file, mode);
	exit(1);
	return NULL; /* never return */
}

