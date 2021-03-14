#include <stdio.h>
#include <math.h>

const int  TWO =  2;
const double PI =  4.0*atan(1.0);

int main()
{
	int r = 10;
	double period = TWO * PI * r;

	printf("Period = %f\n", period);
	return 0;
}
