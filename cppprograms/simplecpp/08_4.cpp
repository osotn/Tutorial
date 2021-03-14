#include <simplecpp>
main_program{
	double	y; cin >> y;
	double xi = 1;
	while(abs(xi*xi - y) > 0.0001) {
		xi = (xi + y/xi)/2;
	}	
	cout << xi << endl;
}	
