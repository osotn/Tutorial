#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	double x,y;
	
	if (argc != 3)
	{
		printf("Usage: pow x y\n");
		return 1;
	}

	x = strtod(argv[1], NULL);
	y = strtod(argv[2], NULL);
	printf("pow %f %f = %f\n", x, y, pow(x,y));
	return 0;
} 
