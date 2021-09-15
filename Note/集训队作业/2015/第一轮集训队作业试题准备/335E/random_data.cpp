#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
	int seed;
	cin >> seed;
	srand(seed);

	cout << "Alice" << endl;
	cout << rand() % 10 + 2 << " " << rand() % 10 << endl;

	return 0;
}
