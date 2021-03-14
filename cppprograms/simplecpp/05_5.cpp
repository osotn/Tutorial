#include <simplecpp>
main_program{
	int m, n;
	cin >> m >> n;
	while( m % n != 0){
		int nextm = n;
		int nextn = m % n;
		m = nextm;
		n = nextn;
	}
	cout << n << endl;
}
