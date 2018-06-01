#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
  ifstream in("2.cpp");
  string word;
  vector<string> v;

  while (in >> word)
    v.push_back(word);
  for(int i=0; i < v.size(); i++)
    cout << i << ":" << v[i] << endl;
}
