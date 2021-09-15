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
	static double f[MaxN + 1][MaxH + 1];
	static double g[MaxN + 1][MaxH + 1];
	static double subF[MaxN + 1][MaxH + 1][MaxH + 1];
	static double subG[MaxN + 1][MaxH + 1][MaxH + 1];

	cin >> name >> n >> hm;
	if (name == "Alice")
	{
		static double p_h[MaxH + 1];
		for (int h = 0; h <= hm; h++)
			p_h[h] = getHProb(h);
		static double p_lh[MaxH + 2];
		for (int h = 0; h <= hm + 1; h++)
			p_lh[h] = getLHProb(h);

		static double prePow[MaxH + 2][MaxH + 2][MaxN + 1];
		for (int h1 = 0; h1 <= hm + 1; h1++)
			for (int h2 = h1; h2 <= hm + 1; h2++)
			{
				double d = p_lh[h1] / p_lh[h2];
				prePow[h1][h2][0] = 1;
				for (int i = 1; i <= n; i++)
					prePow[h1][h2][i] = prePow[h1][h2][i - 1] * d;
			}

		for (int i = 1; i <= n; i++)
		{
			if (i == 1)
			{
				for (int curH = 0; curH <= hm; curH++)
					f[i][curH] = g[i][curH] = 1;
			}
			else
			{
				for (int curH = 0; curH <= hm; curH++)
				{
					f[i][curH] = 0;
					for (int nextH = 0; nextH <= hm; nextH++)
					{
						if (nextH < curH)
						{
							subF[i][curH][nextH] = subF[i - 1][curH][nextH] * p_lh[nextH];
							subF[i][curH][nextH] += (g[i - 1][nextH] + (1 << nextH)) * prePow[nextH + 1][hm + 1][i - 1] * p_h[nextH] / p_lh[nextH + 1];
						}
						else
						{
							subF[i][curH][nextH] = subF[i - 1][curH][nextH] * p_lh[curH];
							subF[i][curH][nextH] += (f[i - 1][nextH] + (1 << curH)) * p_h[nextH];
						}
						f[i][curH] += subF[i][curH][nextH];
					}

					g[i][curH] = 0;
					for (int nextH = 0; nextH <= curH; nextH++)
					{
						subG[i][curH][nextH] = subG[i - 1][curH][nextH] * p_lh[nextH] / p_lh[curH + 1];
						subG[i][curH][nextH] += (g[i - 1][nextH] + (1 << nextH)) * prePow[nextH + 1][curH + 1][i - 1] * p_h[nextH] / p_lh[nextH + 1];
						g[i][curH] += subG[i][curH][nextH];
					}
				}
			}
		}
		
		double e = 0;
		for (int curH = 0; curH <= hm; curH++)
			e += getHProb(curH) * f[n][curH];
		printf("%.10f\n", e);
	}
	else if (name == "Bob")
	{
	}

	return 0;
}
