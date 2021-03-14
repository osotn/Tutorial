/* offsetof: user space demo program */


#define offsetof(type, member)	(&((type*)0)->member)
#define container_of(ptr, type, member) ((type *)((char*)ptr - (char*)offsetof(type, member)))

#include <stdio.h>

int main()
{
	struct S {
		int a;
		int b;
		int c;
		int d;
	};

	void *p = NULL;
	struct S s = {1, 2, 3};
	struct S *ps = NULL;

	p = &((struct S*)0)->d;
	printf(" offsetof (struct S, d) = %p, must be %p\n",
		offsetof(struct S, d), p);

	ps = (struct S*)((char *)&s.d - (char *)offsetof(struct S, d));

	printf(" container_of(&s.d, struct S, d) = %p, must be %p, &s = %p\n",
		container_of(&s.d, struct S, d), ps, &s);
}
