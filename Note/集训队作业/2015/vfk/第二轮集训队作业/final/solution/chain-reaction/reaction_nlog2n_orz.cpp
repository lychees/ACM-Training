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

inline void polymul(int n, int *a, int *b, int *c)
{
	static int da[MaxTN * 2];
	static int db[MaxTN * 2];

	int tl = 0;
	int tn = 1;
	while (tn < n * 2)
		tn <<= 1, tl++;

	for (int i = 1; i < tn; i++)
		preRevB[i] = (preRevB[i >> 1] >> 1) | (i & 1) << (tl - 1);

	int curG = modpow(FFT_G, (P - 1) / tn);
	preGPow[0] = 1;
	for (int i = 1; i < tn; i++)
		preGPow[i] = (s64)preGPow[i - 1] * curG % P;

	copy(a, a + n, da);
	fill(da + n, da + tn, 0);
	fft(tn, da, da);

	copy(b, b + n, db);
	fill(db + n, db + tn, 0);
	fft(tn, db, db);

	for (int i = 0; i < tn; i++)
		da[i] = (s64)da[i] * db[i] % P;
	reverse(preGPow + 1, preGPow + tn);

	fft(tn, da, da);

	int revTN = modpow(tn, P - 2);
	for (int i = 0; i < n; i++)
		c[i] = (s64)da[i] * revTN % P;
}

inline int *polymulcto(int n, int *a, int c)
{
	for (int i = 0; i < n; i++)
		a[i] = (s64)a[i] * c % P;
	return a;
}

inline int *polyint(int n, int *a)
{
	for (int i = n - 1; i >= 1; i--)
		a[i] = (s64)preRevP[i] * a[i - 1] % P;
	a[0] = 0;
	return a;
}
inline int *polyder(int n, int *a)
{
	for (int i = 0; i < n - 1; i++)
		a[i] = (s64)(i + 1) * a[i + 1] % P;
	a[n - 1] = 0;
	return a;
}

inline void polyinv_next(int n, int *a, int *x)
{
	static int b[MaxTN];
	polymul(n * 2, a, x, b);
	polymul(n * 2, b, x, b);

	for (int i = n; i < n * 2; i++)
		x[i] = (2ll * x[i] + P - b[i]) % P;
}

inline void polyexp_next(int tm, int *a, int *x, int *invx)
{
	static int b[MaxTN];
	polyinv_next(tm, x, invx);

	copy(x, x + tm * 2, b);
	polyder(tm * 2, b);
	polymul(tm * 2, b, invx, b);
	polyint(tm * 2, b);

	for (int i = 0; i < tm * 2; i++)
		b[i] = (b[i] + P - a[i]) % P;
	polymul(tm * 2, b, x, b);
	for (int i = 0; i < tm * 2; i++)
		x[i] = (x[i] + P - b[i]) % P;

	polyinv_next(tm, x, invx);
}

int a[MaxTN];
int f[MaxTN];

inline void solve(int le, int ri)
{
	if (le + 1 == ri)
		return;

	int mid = (le + ri) / 2;

	solve(le, mid);

	static int ta[MaxTN];
	static int tb[MaxTN];
	copy(f + le, f + mid, ta);
	fill(ta + mid - le, ta + ri - le, 0);
	polymul(ri - le, ta, f, tb);
	polymul(ri - le, tb, a, tb);

	for (int i = mid; i < ri; i++)
		f[i] = (f[i] + (s64)tb[i - le - 1] * preRevP[i]) % P;

	if (le * 2 <= ri)
	{
		polymul(ri - le, ta, ta, tb);
		polymul(ri - le, tb, a, tb);
		for (int i = mid; i < ri; i++)
			if (i >= le * 2 - 1)
				f[i] = (f[i] + P - (s64)tb[i - le * 2 - 1] * preRevP[i] % P * ((P + 1) / 2) % P) % P;
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
