#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
using namespace std;

typedef long long s64;

const s64 S64_MAX = 9223372036854775807ll;

const int MaxN = 5000000;

template <class T>
inline void relax(T &a, const T &b)
{
	if (b > a)
		a = b;
}
template <class T>
inline void tension(T &a, const T &b)
{
	if (b < a)
		a = b;
}

inline int getint()
{
	char c;
	while (c = getchar(), '0' > c || c > '9');

	int res = c - '0';
	while (c = getchar(), '0' <= c && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

int main()
{
	int n;
	static char s[MaxN * 2 + 1];
	static int fa[MaxN + 1];
	static int deg[MaxN + 1];
	static s64 f[MaxN + 1];
	static int nl[MaxN + 1];
	static int d[MaxN + 1];
	static s64 ds[MaxN + 1];
	static int dm[MaxN + 1];
	static int up[MaxN + 1];
	static int next[MaxN + 1];

	cin >> n;
	scanf("%s", s);
	for (int i = 0, v = 0, tot = 0; i < n * 2; i++)
	{
		if (s[i] == '(')
		{
			tot++;
			fa[tot] = v;
			v = tot;
		}
		else
			v = fa[v];
	}

	for (int v = 2; v <= n; v++)
		d[v] = d[fa[v]] + 1, deg[fa[v]]++;
	for (int v = n; v >= 2; v--)
	{
		if (deg[v] == 0)
			ds[v] = dm[v] = d[v], nl[v] = 1;

		int curv = v;
		while (curv && d[curv] <= dm[fa[v]])
		{
			up[curv] = fa[v];
			curv = next[curv];
		}
		while (next[fa[v]] && d[next[fa[v]]] <= dm[v])
		{
			up[next[fa[v]]] = fa[v];
			next[fa[v]] = next[next[fa[v]]];
		}
		if (dm[v] >= dm[fa[v]])
			next[fa[v]] = curv;

		ds[fa[v]] += ds[v];
		relax(dm[fa[v]], dm[v]);
		nl[fa[v]] += nl[v];
	}

	f[1] = 0;
	for (int v = 2; v <= n; v++)
	{
		f[v] = S64_MAX;
		if (up[v])
		{
			int u = up[v];
			tension(f[v], f[u] + (ds[u] - ds[v] - (s64)d[u] * (nl[u] - nl[v])));
		}
		if (deg[fa[v]] == 1)
			tension(f[v], f[fa[v]] + 1);
	}

	s64 res = S64_MAX;
	for (int v = 1; v <= n; v++)
		if (deg[v] == 0)
			tension(res, f[v]);

	cout << res << endl;

	return 0;
}
