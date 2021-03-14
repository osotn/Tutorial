#include <iostream>
#include <cstring>
using namespace std;

template<class T>
T Max(T x, T y) { 

	cout << "Max (x = " << x << "y = " << y << ");" << endl; 
	return x > y ? x : y; 

}

template<>
char *Max<char *>(char *x, char *y) {
	cout << "Max<char *x>()" << endl;
	return strcmp(x,y) > 0 ? x : y; 

}

int main() {
	char *s1 = "hello";
	char *s2 = "hi";

	int i = 3, j = 5;

	cout << "Max = " << Max(3,5) << endl;
	cout << "Max = " << Max(s1, s2) << endl;
	cout << "Max<char *> =" << Max<char *>(s1,s2) << endl;

	return 0;
}


