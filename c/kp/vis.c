/* vis: make funny characters visible (version 2) */

#include <stdio.h>
#include <ctype.h>

int strip = 0;	/* 1 => discard special characters */

void vis(FILE * fp);	/* make chars visible in FILE *fp */

int main (int argc, char *argv[])
{
	int i;
	FILE *fp = NULL;
	const char *prog_name = argv[0];

	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 's':	/* -s: strip funny chars */
			strip = 1; 
			break;
		default:
			fprintf(stderr, "%s: unknown arg %s\n",
				prog_name, argv[1]);
		}
		argc--;
		argv++;
	}

	if (argc == 1) {
		vis(stdin);
	}
	else {
		for (i = 1; i < argc; i++) {
			if ((fp = fopen(argv[i], "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n",
					prog_name, argv[i]);
				return 1;
			} else {
				vis(fp);
				fclose(fp);
			}
		}
	}
	return 0; //exit(0);
}

void vis(FILE * fp)
{
	int c;

	while ((c = getc(fp)) != EOF)
		if (isascii(c) &&
		    (isprint(c) || c == '\n' || c == '\t' || c == ' '))
			putchar(c);
		else if (!strip)
			printf("\\0x%02x", c);
}

