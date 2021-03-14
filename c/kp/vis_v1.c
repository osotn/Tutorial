/* vis: make funny characters visible (version 1) */

#include <stdio.h>
#include <ctype.h>

int main ()
{
	int c;

	while ((c = getchar()) != EOF)
		if (isascii(c) &&
		    (isprint(c) || c == '\n' || c == '\t' || c == ' '))
			putchar(c);
		else
			printf("\\0x%02x", c);
	return 0; //exit(0);
}
