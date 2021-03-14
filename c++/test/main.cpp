#include <iostream>
#include<cmath>

using namespace std; // using directive

//using std::count;

int multiply(int x, int y)
{
    return x*y;
}

int main()
{
    int slices = 5;
    //cin >> slices;
    cout << "You have " << slices << " slices of pizza." << std::endl;
    cout << "pow(2, 10) = " << std::pow(10, 2) << std::endl;
    cout << "multiply(2, 5) = " << multiply(2, 5) << std::endl;

    return 0;
}
