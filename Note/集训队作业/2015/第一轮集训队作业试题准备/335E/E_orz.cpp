#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MaxN = 1000;
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
						for (int nextH = 0; nextH < curH; nextH++)
							for (int j = 1; j < i; j++)
								f[i][curH][limH] += (f[j][nextH][nextH] + pow(2, nextH))
									* pow(getLHProb(nextH + 1, limH), i - 1)
									* pow(getLHProb(nextH, nextH), i - j - 1)
									* getHProb(nextH, nextH);
						for (int j = 1; j < i; j++)
							for (int nextH = curH; nextH <= limH; nextH++)
								f[i][curH][limH] += (f[j][nextH][limH] + pow(2, curH))
									* pow(getLHProb(curH, limH), i - j - 1)
									* getHProb(nextH, limH);
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
