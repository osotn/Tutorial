#include <stdio.h>

#define DBG_CODE(code) {code;}

int main()
{
	DBG_CODE(int a);
	DBG_CODE(int a; printf("a=%d\n", a));
	return 0;;
}
