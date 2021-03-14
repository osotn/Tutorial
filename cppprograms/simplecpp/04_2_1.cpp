#include <simplecpp>
main_program{
	int n;
	cin >> n;
//	turtleSim();

	double I, T, S;
	I = 1, T = 1, S = 1;
	repeat(n){
		T /= I;
		S += T;
		I++;
	}
	cout << S << endl;
//	wait(10);
}
