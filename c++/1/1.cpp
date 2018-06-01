#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
  cout << "Hello, World!" << endl;
  cout << dec << 15 << endl;
  cout << oct << 15 << endl;
  cout << hex << 15 << endl;
  cout << 3.14 << endl;
  cout << (char)27 << endl;

  cout << "Enter a number" << endl;
  int number;
  cin >> number;
  cout << dec << number << endl;
  cout << oct << number << endl;
  cout << hex << number << endl;

  system("echo \"Hello\"");

  return 0;
}
