#include <iostream>
#include <cstdio>
using namespace std;

typedef long long s64;

const int P = 998244353;

const int MaxN = 100000;

inline int modpow(int a, int n)
{
	int res = 1;
	int t = a;
	for (int i = n; i > 0; i >>= 1)
	{
		if (i & 1)
			res = (s64)res * t % P;
		t = (s64)t * t % P;
	}
	return res;
}

int main()
{
	int n, c, d, q;
	cin >> n >> c >> d >> q;

	c %= P - 1;
	d %= P - 1;

	c = (c + P - 1 - d) % (P - 1);

	static int f[MaxN + 1];
	for (int i = 1; i <= n; i++)
		f[i] = modpow(i, c);
	for (int i = 1; i <= n; i++)
		for (int j = i + i; j <= n; j += i)
			f[j] = (f[j] + P - f[i]) % P;

	q = 3;

	while (q--)
	{
		static int b[MaxN + 1];
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]), b[i] = (s64)b[i] * modpow(i, P - 1 - d) % P;

		for (int i = 1; i <= n; i++)
			for (int j = i + i; j <= n; j += i)
				b[j] = (b[j] + P - b[i]) % P;
		bool hasSol = true;
		for (int i = 1; i <= n; i++)
		{
			if (f[i] != 0)
				b[i] = (s64)b[i] * modpow(f[i], P - 2) % P;
			else
			{
				if (b[i] != 0)
				{
					hasSol = false;
					break;
				}
			}
		}
		if (!hasSol)
		{
			printf("-1\n");
			continue;
		}

		for (int i = n; i >= 1; i--)
			for (int j = i + i; j <= n; j += i)
				b[i] = (b[i] + P - b[j]) % P;

		for (int i = 1; i <= n; i++)
			b[i] = (s64)b[i] * modpow(i, P - 1 - d) % P;
		
		for (int i = 1; i <= n; i++)
			printf("%d ", b[i]);
		printf("\n");
	}

	return 0;
}
