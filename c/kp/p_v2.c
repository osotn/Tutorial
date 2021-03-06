/* p: print input in chuncks (version 2) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGESIZE	22

char *progname;	/* program name for error messages */

FILE *efopen(char *file, char *mode);	/* fopen file, die if can't */
void print(FILE *fp, int pagesize);	/* print fp in pagesize chunks */
int ttyin(void);			/* process response from /dev/tty */

int main(int argc, char *argv[])
{
	int i, pagesize = PAGESIZE;
	FILE *fp;

	progname = argv[0];

	if (argc > 1 && argv[1][0] == '-') {
		pagesize = atoi(&argv[1][1]);
		argc--;
		argv++;
	}

	if (argc == 1)
		print(stdin, pagesize);
	else
 		for (i = 1; i < argc; i++) {
			fp = efopen(argv[i], "r");
			print(fp, pagesize);
			fclose(fp);
		}
	return 0;
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

void print(FILE *fp, int pagesize)
{
	static int lines = 0;	/* number of lines so far */
	char buf[BUFSIZ]; 

	while (fgets(buf, sizeof buf, fp) != NULL)
		if (++lines < pagesize)
			fputs(buf, stdout);
		else {
			buf[strlen(buf)-1] = '\0';
			fputs(buf, stdout);
			fflush(stdout);
			ttyin();
			lines = 0;
		}
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
			system(buf + 1);	/* BUG here */
			printf("!\n");
		}
		else
			return buf[0];
	}
}
	
