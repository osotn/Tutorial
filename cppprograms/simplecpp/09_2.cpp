#include <simplecpp>
main_program{
	for (int x = 1; x <= 20; x++)
		for (int y = x+1; y <= 20; y++)
			for (int z = y+1; z <=20; z++)
				if (x*x + y*y == z*z)
					cout << x << ' ' << y << ' ' << z << endl;
}
