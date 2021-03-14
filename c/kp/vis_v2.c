/* vis: make funny characters visible (version 2) */

#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
	int c, strip = 0;

	if (argc > 1 && strcmp(argv[1], "-s") == 0)
		strip = 1;

	while ((c = getchar()) != EOF)
		if (isascii(c) &&
		    (isprint(c) || c == '\n' || c == '\t' || c == ' '))
			putchar(c);
		else if (!strip)
			printf("\\0x%02x", c);
	return 0; //exit(0);
}
