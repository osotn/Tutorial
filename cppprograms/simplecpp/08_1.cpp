#include <simplecpp>
main_program{
	double x; cin >> x;
	cout << "Calculationg sin(x) for x = " << x << endl;

	double s = 0, t = x;
	for (int k = 1;  k < 10; k++) {
		s = s + t;
		t = -t * x * x/(2*k)/(2*k+1);
		cout << "No of terms: " << k << " Value: " << s
			<< " Error estimate: " << t << endl;
	}
	cout << endl << "From library function: " << sin(x) << endl;
}
