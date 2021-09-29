#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MaxN = 30000;
const int MaxH = 30;

int hm;

double getHProb(int h)
{
	if (h == hm)
		return pow(2, -hm);
	else
		return pow(2, -(h + 1));
}
double getLHProb(int h)
{
	if (h == hm + 1)
		return 1;
	else
		return 1 - pow(2, -h);
}
double getHProb(int h, int limH)
{
	return getHProb(h) / getLHProb(limH + 1);
}
double getLHProb(int h, int limH)
{
	return getLHProb(h) / getLHProb(limH + 1);
}

int main()
{
	string name;
	int n;
	cin >> name >> n >> hm;
	if (name == "Alice")
	{
		static double f[2][MaxH + 1];
		static double g[2][MaxH + 1];
		static double subF[2][MaxH + 1][MaxH + 1];
		static double subG[2][MaxH + 1][MaxH + 1];
		static double prePow[MaxH + 2][MaxH + 2][2];

		static double p_h[MaxH + 1];
		for (int h = 0; h <= hm; h++)
			p_h[h] = getHProb(h);
		static double p_lh[MaxH + 2];
		for (int h = 0; h <= hm + 1; h++)
			p_lh[h] = getLHProb(h);

		for (int h1 = 0; h1 <= hm + 1; h1++)
			for (int h2 = h1; h2 <= hm + 1; h2++)
				prePow[h1][h2][0] = 1;
		for (int i = 1; i <= n; i++)
		{
			int c = i % 2, p = (i - 1) % 2;
			for (int h1 = 0; h1 <= hm + 1; h1++)
				for (int h2 = h1; h2 <= hm + 1; h2++)
					prePow[h1][h2][c] = prePow[h1][h2][p] * (p_lh[h1] / p_lh[h2]);
			if (i == 1)
			{
				for (int curH = 0; curH <= hm; curH++)
					f[c][curH] = g[c][curH] = 1;
			}
			else
			{
				for (int curH = 0; curH <= hm; curH++)
				{
					f[c][curH] = 0;
					for (int nextH = 0; nextH <= hm; nextH++)
					{
						if (nextH < curH)
						{
							subF[c][curH][nextH] = subF[p][curH][nextH] * p_lh[nextH];
							subF[c][curH][nextH] += (g[p][nextH] + (1 << nextH)) * prePow[nextH + 1][hm + 1][p] * p_h[nextH] / p_lh[nextH + 1];
						}
						else
						{
							subF[c][curH][nextH] = subF[p][curH][nextH] * p_lh[curH];
							subF[c][curH][nextH] += (f[p][nextH] + (1 << curH)) * p_h[nextH];
						}
						f[c][curH] += subF[c][curH][nextH];
					}

					g[c][curH] = 0;
					for (int nextH = 0; nextH <= curH; nextH++)
					{
						subG[c][curH][nextH] = subG[p][curH][nextH] * p_lh[nextH] / p_lh[curH + 1];
						subG[c][curH][nextH] += (g[p][nextH] + (1 << nextH)) * prePow[nextH + 1][curH + 1][p] * p_h[nextH] / p_lh[nextH + 1];
						g[c][curH] += subG[c][curH][nextH];
					}
				}
			}
		}
		
		double e = 0;
		for (int curH = 0; curH <= hm; curH++)
			e += getHProb(curH) * f[n % 2][curH];
		printf("%.10f\n", e);
	}
	else if (name == "Bob")
	{
		cout << n << endl;
	}

	return 0;
}
