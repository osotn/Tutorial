/* pick: offer choice on each argument */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*progname;	/* program name for error message */

void pick(char *s); 			/* offer choice of s */
int ttyin(void);			/* process response form /dev/tty */
FILE *efopen(char *file, char *mode);	/* fopen file, die if can't */

int main(int argc, char *argv[])
{
	int i;
	char buf[BUFSIZ];

	progname = argv[0];

	if (argc == 2 && strcmp(argv[1], "-") == 0)	/* pick - */
		while (fgets(buf, sizeof buf, stdin) != NULL) {
			buf[strlen(buf) - 1] = '\0';	/* drop newline */
			pick(buf);
		}
	else
		for (i = 1; i < argc; i++)
			pick(argv[i]);

	return 0;
}

void pick(char *s)
{
	fprintf(stderr, "%s? ", s);
	if (ttyin() == 'y')
		printf("%s\n", s);
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

