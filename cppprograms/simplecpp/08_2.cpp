#include <simplecpp>
main_program{
	double p, q; cin >> p >> q;
	int n; cin >> n;
	double w = (q-p)/n;
	double area = 0;

	for (int i = 0;  i < n; i++) {
		area += w / (p + i*w);
	}
	cout << "Integral from "<< p <<" to " << q << " equals " << area << " (log(x) = " << log(q) << ")" << endl;
}
