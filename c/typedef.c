#include <stdio.h>




int func(int a)
{
    printf("func() is called, a = %d\n", a);
    return 0;
}


typedef int(*func_PTR)(int a);
typedef int func_TYPE(int a);



int main()
{
    func_PTR    f_PTR  = func;
    func_TYPE  *f_PTR2 = func;

    func(1);
    f_PTR(2);
    f_PTR2(3);

    printf("sizeof(f_PTR) = %ld, sizeof(func_PTR) = %ld, sizeof(func) = %ld, sizeof(&func) = %ld\n", sizeof(f_PTR), sizeof(func_PTR), sizeof(func), sizeof(&func));
    printf("sizeof(func_TYPE) = %ld, sizeof(func_TYPE*) = %ld,  sizeof(f_PTR2) = %ld\n", sizeof(func_TYPE), sizeof(func_TYPE*), sizeof(f_PTR2));


    return 0;
}
