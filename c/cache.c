#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	long long result = 0;
	int *matrix = NULL;
	int n,i,j;

	if (argc == 1)
	{
		printf("Usage: 'prog 1024' or 'prog 1024 1'\n");
		return -1;
	}
	
	n = atoi(argv[1]);
	matrix = (int *)malloc(n*n*sizeof(int));
			
	
	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			matrix[i*n + j] = rand();

	if (argc == 2)
	{
		for (i=0; i<n; i++)
			for (j=0; j<n; j++)
				result += matrix[i*n + j];
	}
	else
	{
		for (i=0; i<n; i++)
			for (j=0; j<n; j++)
				result += matrix[j*n + i];	
	}

	free(matrix);
	return (int)result + (int)(result >> 32);
}

