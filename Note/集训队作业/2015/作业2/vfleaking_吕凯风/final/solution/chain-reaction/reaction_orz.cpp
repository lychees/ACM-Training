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
	static int rfact[MaxN + 1];
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = (s64)fact[i - 1] * i % P;
	rfact[1] = 1;
	for (int i = 2; i <= n; i++)
		rfact[i] = (P - (s64)rfact[P % i] * (P / i) % P) % P;
	rfact[0] = 1;
	for (int i = 1; i <= n; i++)
		rfact[i] = (s64)rfact[i - 1] * rfact[i] % P;

	static int f[MaxN + 1];
	f[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		f[i] = 0;
		for (int j = 1; j <= i - 1; j++)
			for (int k = 1; j + k <= i - 1; k++)
				if (strA[i - j - k - 1] == '1')
					f[i] = (f[i] + (s64)fact[i - 1] * rfact[j] % P * rfact[k] % P * rfact[i - j - k - 1] % P * f[j] % P * f[k] % P) % P;
		f[i] = (s64)f[i] * ((P + 1) / 2) % P;
	}

	for (int i = 1; i <= n; i++)
		printf("%d\n", f[i]);

	return 0;
}
