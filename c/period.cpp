#include <iostream>
#include <cmath>

const int TWO = 2;
const double PI = 4.0*atan(1.0);

int main()
{
	int r = 10;
	double period = TWO * PI * r;

	std::cout << "Period = " << period << std::endl;
	return 0;
}
