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
	static double f[MaxN + 1][MaxH + 1][MaxH + 1];
	static double sum1[MaxN + 1][MaxH + 1];
	static double sum2[MaxN + 1][MaxH + 1][MaxH + 1];
	cin >> name >> n >> hm;
	if (name == "Alice")
	{

		for (int i = 1; i <= n; i++)
		{
			if (i == 1)
			{
				for (int curH = 0; curH <= hm; curH++)
					for (int limH = curH; limH <= hm; limH++)
						f[i][curH][limH] = 1;
			}
			else
			{
				for (int curH = 0; curH <= hm; curH++)
					for (int limH = curH; limH <= hm; limH++)
					{
						f[i][curH][limH] = 0;
						if (curH > 0)
							f[i][curH][limH] += (f[i - 1][0][0] + 1) * pow(getLHProb(1, limH), i - 2) * getHProb(0, limH);

						for (int nextH = 1; nextH < curH; nextH++)
							f[i][curH][limH] += sum1[i - 1][nextH] * pow(getLHProb(nextH, limH), i) * getLHProb(limH + 1);

						if (curH > 0)
							f[i][curH][limH] += sum2[i - 1][curH][limH] * pow(getLHProb(curH, limH), i);
						else
						{
							for (int nextH = curH; nextH <= limH; nextH++)
								f[i][curH][limH] += (f[i - 1][nextH][limH] + pow(2, curH)) * getHProb(nextH, limH);
						}
					}
			}

			for (int nextH = 1; nextH < hm; nextH++)
			{
				sum1[i][nextH] = sum1[i - 1][nextH] + (f[i][nextH][nextH] + pow(2, nextH))
					* pow(getLHProb(nextH + 1), i - 1)
					* pow(getLHProb(nextH), - i - 1)
					* getHProb(nextH);
			}
			for (int curH = 0; curH <= hm; curH++)
				for (int limH = curH; limH <= hm; limH++)
				{
					sum2[i][curH][limH] = sum2[i - 1][curH][limH];
					for (int nextH = curH; nextH <= limH; nextH++)
					{
						sum2[i][curH][limH] += (f[i][nextH][limH] + pow(2, curH))
							* getHProb(nextH)
							* pow(getLHProb(curH), - i - 1)
							* pow(getLHProb(limH + 1), i);
					}
				}
		}
		
		double e = 0;
		for (int curH = 0; curH <= hm; curH++)
			e += getHProb(curH) * f[n][curH][hm];
		printf("%.10f\n", e);
	}
	else if (name == "Bob")
	{
	}

	return 0;
}
