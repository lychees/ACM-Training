#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

// Generate all possible permutations of the digits of a number
string kernel(long long n) {
  std::string s = std::to_string(n);
  std::sort(s.begin(), s.end());
  return s;
}

map<string, vector<long long>> H;

int main() {
  // Loop through all possible numbers
  for (long long n = 1; n < 10000; n++) {
    string t = kernel(n*n*n);
    H[t].push_back(n*n*n);
    if (H[t].size() >= 5) {
        sort(H[t].begin(), H[t].end());
        cout << *H[t].begin() << endl;
        exit(0);
    }
  }
  return 0;
}
