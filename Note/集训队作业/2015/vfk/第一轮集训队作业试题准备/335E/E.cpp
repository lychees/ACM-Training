#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MaxN = 30000;
const int MaxH = 30;

int main()
{
	string name;
	int n, hm;
	cin >> name >> n >> hm;
	if (name == "Alice")
	{
		double e = n;
		double p = 1;
		double v = 1;
		for (int h = 1; h <= hm; h++)
		{
			p /= 2;
			v *= 2;
			
			double w = 1;
			for (int l = 1; l < n; l++, w *= 1 - p)
				e += (n - l) * p * w * (1 - (l - 1) / (v - 1)) / 2;
		}
		printf("%.10f\n", e);
	}
	else if (name == "Bob")
	{
		cout << n << endl;
	}

	return 0;
}
