#include <iostream>
#include <cstdio>
using namespace std;

typedef long long s64;

const int P = 998244353;

const int MaxN = 200000;

int main()
{
	int n;
	static char strA[MaxN + 1];

	cin >> n;
	scanf("%s", strA);

	static int fact[MaxN + 1];
	static int re[MaxN + 1];
	static int rfact[MaxN + 1];
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = (s64)fact[i - 1] * i % P;
	re[1] = 1;
	for (int i = 2; i <= n; i++)
		re[i] = (P - (s64)re[P % i] * (P / i) % P) % P;
	rfact[0] = 1;
	for (int i = 1; i <= n; i++)
		rfact[i] = (s64)rfact[i - 1] * re[i] % P;

	static int f[MaxN + 1];
	static int g[MaxN + 1];
	f[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		f[i] = 0;
		for (int j = 2; j <= i - 1; j++)
			if (strA[i - j - 1] == '1')
				f[i] = (f[i] + (s64)rfact[i - j - 1] * g[j]) % P;
		f[i] = (s64)f[i] * re[i] % P;
		f[i] = (s64)f[i] * ((P + 1) / 2) % P;

		g[i] = 0;
		for (int j = 1; j < i; j++)
			g[i] = (g[i] + (s64)f[j] * f[i - j]) % P;
	}

	for (int i = 1; i <= n; i++)
		printf("%d\n", (int)((s64)f[i] * fact[i] % P));

	return 0;
}
