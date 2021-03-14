#include <stdio.h>
#include <string.h>

void reverse_str(char * s)
{
	char *p = s;
	char  t;

	while (*p++);
	p -= 2;

	while (p > s)
	{
		t  = *s;
		*s++ = *p;
		*p-- = t;
	}
}

char rem_to_symbol(int n)
{
	if (n >= 16)
		return '?';

	if (n < 10)
		return '0'+n;

	return 'a'+(n-10);
}


char s_string[256];
char * num_to_base_string(int num, int base)
{
	char *p = s_string;
	int  sign = 0;
	int  rem;

	if (base <= 0)
		return NULL;

	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}

	while (num)
	{
		*p++ = rem_to_symbol(num % base);
		num /= base;
	}
	
	if (sign)
		*p++ = '-';

	*p = '\0';
	reverse_str(s_string);
	return s_string;
}


int main()
{
	char str[] = "hello, world!!!";

	printf("Change: on %s:\n", str);
	reverse_str(str);
	printf("%s:\n", str);	

	printf(" 123456789 base 10 = %s\n", num_to_base_string(123456789, 10));
	printf(" -9876 base 10 = %s\n", num_to_base_string(-9876, 10));
	printf(" 1786 base 16 = %s\n", num_to_base_string(1786, 16));

	return 0;
}
