#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long s64;

const int P = 998244353;
const int FFT_G = 3;

const int MaxN = 200000;

const int MaxTN = 262144;

int preGPow[MaxTN * 2];
int preRevB[MaxTN * 2];
int preRevP[MaxN + 1];

inline int modpow(int a, const int &n)
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

void fft(int n, int *a, int *out)
{
	if (out == a)
	{
		for (int i = 0; i < n; i++)
			if (preRevB[i] < i)
				swap(out[preRevB[i]], a[i]);
	}
	else
	{
		for (int i = 0; i < n; i++)
			out[preRevB[i]] = a[i];
	}
	int nl = 0;
	while ((1 << nl) < n)
		nl++;
	for (int l = 0; l < nl; l++)
	{
		int m = 1 << l;
		int g = preGPow[1 << (nl - l - 1)];
		for (int s = 0; s < n; s += m * 2)
		{
			int cg = 1;
			for (int i = s; i < s + m; i++)
			{
				int o = out[i], e = (s64)out[i + m] * cg % P;
				out[i] = (o + e) % P;
				out[i + m] = (o + P - e) % P;
				cg = (s64)cg * g % P;
			}
		}
	}
}

void fft_init(int tn)
{
	int tl = 0;
	while ((1 << tl) < tn)
		tl++;

	for (int i = 1; i < tn; i++)
		preRevB[i] = (preRevB[i >> 1] >> 1) | (i & 1) << (tl - 1);

	int curG = modpow(FFT_G, (P - 1) / tn);
	preGPow[0] = 1;
	for (int i = 1; i < tn; i++)
		preGPow[i] = (s64)preGPow[i - 1] * curG % P;
}
void fft_rev(int tn)
{
	reverse(preGPow + 1, preGPow + tn);
}

inline void polymul(int n, int *a, int *b, int *c)
{
	static int da[MaxTN * 2];
	static int db[MaxTN * 2];

	int tn = 1;
	while (tn < n * 2)
		tn <<= 1;

	fft_init(tn);

	copy(a, a + n, da);
	fill(da + n, da + tn, 0);
	fft(tn, da, da);

	copy(b, b + n, db);
	fill(db + n, db + tn, 0);
	fft(tn, db, db);

	for (int i = 0; i < tn; i++)
		da[i] = (s64)da[i] * db[i] % P;
	fft_rev(tn);

	fft(tn, da, da);

	int revTN = modpow(tn, P - 2);
	for (int i = 0; i < n; i++)
		c[i] = (s64)da[i] * revTN % P;
}

int a[MaxTN];
int f[MaxTN];

inline void solve(int le, int ri)
{
	if (le + 1 == ri)
		return;

	int mid = (le + ri) / 2;

	solve(le, mid);

	int tn = 1;
	while (tn < ri - le)
		tn <<= 1;
	tn <<= 1;
	int revTN = modpow(tn, P - 2);

	fft_init(tn);

	static int ta[MaxTN * 2];
	static int tb[MaxTN * 2];
	static int tc[MaxTN * 2];
	static int td[MaxTN * 2];
	copy(f + le, f + mid, ta);
	fill(ta + mid - le, ta + tn, 0);

	fft(tn, ta, ta);

	copy(f, f + ri - le, tb);
	fill(tb + ri - le, tb + tn, 0);
	fft(tn, tb, tb);

	copy(a, a + ri - le, tc);
	fill(tc + ri - le, tc + tn, 0);
	fft(tn, tc, tc);

	fft_rev(tn);

	for (int i = 0; i < tn; i++)
		td[i] = (s64)ta[i] * tb[i] % P * tc[i] % P;
	fft(tn, td, td);
	for (int i = 0; i < tn; i++)
		td[i] = (s64)td[i] * revTN % P;

	for (int i = mid; i < ri; i++)
		f[i] = (f[i] + (s64)td[i - le - 1] * preRevP[i]) % P;

	if (le * 2 <= ri)
	{
		for (int i = 0; i < tn; i++)
			td[i] = (s64)ta[i] * ta[i] % P * tc[i] % P;
		fft(tn, td, td);
		for (int i = 0; i < tn; i++)
			td[i] = (s64)td[i] * revTN % P;
		for (int i = mid; i < ri; i++)
			if (i >= le * 2 - 1)
				f[i] = (f[i] + P - (s64)td[i - le * 2 - 1] * preRevP[i] % P * ((P + 1) / 2) % P) % P;
	}

	solve(mid, ri);
}

int main()
{
	int n;
	static char strA[MaxN + 1];

	cin >> n;
	scanf("%s", strA);

	preRevP[1] = 1;
	for (int i = 2; i <= n; i++)
		preRevP[i] = (P - (s64)preRevP[P % i] * (P / i) % P) % P;

	static int fact[MaxN + 1];
	static int rfact[MaxN + 1];
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = (s64)fact[i - 1] * i % P;

	rfact[0] = 1;
	for (int i = 1; i <= n; i++)
		rfact[i] = (s64)rfact[i - 1] * preRevP[i] % P;

	for (int i = 0; i < n; i++)
		a[i] = (strA[i] == '1') * rfact[i];

	f[1] = 1;
	solve(0, n + 1);

	for (int i = 1; i <= n; i++)
		printf("%d\n", (int)((s64)f[i] * fact[i] % P));

	return 0;
}
