#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

double w, f[110][50];
int t[110][50], g[110][50], L[110], x[110], y[110];
int test, n;

double calculate(int a, int b, int t)
{
	double v = 400 + x[t] + (y[t] - x[t]) / 20. * (a - 20);
	return (a < b ? 50 * (b - a) : 0) + (abs(30 - a) * 10 + 2000) * L[t] / v;
}
int main()
{
	freopen("flight.in", "r", stdin);
	freopen("flight.out", "w", stdout);

	cin >> test;
	for (int num = 1; num <= test; ++num)  {
		cin >> n;
		for (int i = 1; i <= n; ++i)
			cin >> L[i] >> x[i] >> y[i];

		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(t, 0, sizeof(t));
		t[n + 1][20] = 1;
		
		for (int i = n; i; --i)  {
			for (int j = 20; j <= 40; ++j)
				for (int k = 20; k <= 40; ++k)
					if (t[i + 1][k])  {
						w = calculate(j, k, i) + f[i + 1][k];
						if (!t[i][j]  ||  w + 1e-8 < f[i][j])
							f[i][j] = w, g[i][j] = k;

						t[i][j] = 1;
					}
		}

		double res = 1e18;
		int h;
		for (int i = 20; i <= 40; ++i)
			if (t[1][i]  &&  f[1][i] + i * 50 < res)
				res = f[1][i] + i * 50, h = i;


		cout << "Flight " << num << ": ";
		int N = 1;
	  while (N <= n)  {
			cout << h << " ";
			h = g[N][h];  ++ N;
		}
		
		cout << (long long) ceil(res + 1e-8) << endl;
	}
}
