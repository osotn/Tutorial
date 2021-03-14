#include <simplecpp>
main_program{
	double	xL = 0,
		xR = 2,
		xM, epsilon = 0.00001;
	int 	n = 0;
	while (xR - xL >= epsilon) {
		xM = (xL + xR)/2;
		if ((xL*xL - 2 > 0 && xM*xM -2 > 0) ||
		    (xL*xL - 2 < 0 && xM*xM -2 < 0))
			xL = xM;
		else
			xR = xM;
		++n;
	}
	cout << xL << ", n = " << n << endl;
}	
