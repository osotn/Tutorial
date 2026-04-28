#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    printf("Int, sizeo(int) = %u \n", (unsigned)sizeof(int));
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_unsigned(unsigned x) {
    printf("Unsigned, sizeof(unsigned) = %u \n", (unsigned)sizeof(unsigned));
    show_bytes((byte_pointer) &x, sizeof(unsigned));
}

void show_float(float x) {
    printf("Float, sizeo(float) = %u \n", (unsigned)sizeof(float));
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    printf("Void, sizeo(void*) = %u \n", (unsigned)sizeof(void*));
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void show_string(char *s) {
    printf("String, \"%s\", strlen(s) = %u \n", s, (unsigned)strlen(s));
    show_bytes((byte_pointer) s, strlen(s) + 1);
}

void show_func(void *f, size_t s) {
    printf("Function, size = %u \n", (unsigned)s);
    show_bytes((byte_pointer) f, s); 
}

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

int sum(int a, int b) {
	return a + b;
}

int foo(int i) {
	return i;
}

int show_min_max(void) {
    printf("INT_MAX = %d \n", INT_MAX);
    show_int(INT_MAX);
    printf("INT_MIN = %d \n", INT_MIN);
    show_int(INT_MIN);
    printf("UINT_MAX = %u \n", UINT_MAX);
    show_unsigned(UINT_MAX);
    printf("UINT_MIN = %u \n", 0);
    show_unsigned(0);
   
    
    return 0;
}

int main() {
    test_show_bytes(12345);
    show_string("12345");

    printf("sum = %p \n", sum);
    printf("foo = %p \n", foo);
    show_func(sum, (byte_pointer)foo - (byte_pointer)sum);
    show_min_max();

    return 0;
}

