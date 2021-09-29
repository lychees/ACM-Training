#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const double msc = 2 * acos(-1.);
using namespace std;

int c[40];
double rev[40];

bool check(double r)
{
	double x, y, z;
	for (int i = 2; i <= 4; ++i)  {
		rev[i] = 0;
		for (int j = 1; j < i; ++j)  {
			x = r - c[j];
			y = c[i] + c[j];
			z = r - c[i];
			z = acos((x * x + z * z - y * y) / 2 / x / z);
			rev[i] = max(rev[i], rev[j] + z);
		}

		if (rev[i] > msc)  return 0;
		for (int j = 1; j < i; ++j)  {
		  x = r - c[j];
		  y = c[i] + c[j];
		  z = r - c[i];
		  z = sqrt(x * x + z * z - 2 * x * z * cos(rev[i] - rev[j]));
		  if (z + 1e-5 < y)  return 0;
    }
	}

	return 1;
}
bool work(double t)
{
	if (check(t))  return 1;  swap(c[2], c[3]);
	if (check(t))  return 1;  swap(c[3], c[4]);
	return check(t);
}
int main()
{
	freopen("conduit.in", "r", stdin);
	freopen("conduit.out", "w", stdout);

	int num = 0;
	while (true)  {
		++num;

		cin >> c[1];
		if (c[1] == 0)  break;

		for (int i = 2; i <= 4; ++i)  cin >> c[i];

		double l = c[1] + 1, r = c[1] * 3, j;
		for (; j = (l + r) / 2, r - l > 1e-8; )
			if (work(j))  r = j;
			else  l = j;

		cout << "Case " << num << ": " << (int) round(j + 1e-8) << endl;
	}
}
