#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
using namespace std;

typedef long long s64;

const s64 S64_MAX = 9223372036854775807ll;

const int MaxN = 5000000;

template <class T>
inline int size(const T &a)
{
	return (int)a.size();
}

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

int n;
int fa[MaxN + 1];
vector<int> adj[MaxN + 1];

s64 f[MaxN + 1];
int nl[MaxN + 1];
int d[MaxN + 1];
s64 d_s[MaxN + 1];
int d_m[MaxN + 1];
int d_m_p[MaxN + 1], d_m_s[MaxN + 1];

int sta_n;
int sta[MaxN];

s64 dfs(int v)
{
	sta[sta_n] = v;

	if (sta_n == 0)
		f[v] = 0;
	else
	{
		f[v] = S64_MAX;

		for (int i = sta_n - 1; i >= 0; i--)
		{
			int u = sta[i], c = sta[i + 1];

			int cur_d_m = max(d_m_p[c], d_m_s[c]);
			tension(f[v], f[u] + (d_s[u] - d_s[v] - (s64)d[u] * (nl[u] - nl[v])) + max(sta_n - cur_d_m, 0));
		}
	}
	sta_n++;

	s64 res = S64_MAX;
	if (size(adj[v]) == 0)
		res = f[v];
	else
	{
		for (int i = 0; i < size(adj[v]); i++)
			tension(res, dfs(adj[v][i]));
	}

	sta_n--;
	return res;
}

int main()
{
	static char s[MaxN * 2 + 1];
	cin >> n;
	scanf("%s", s);
	for (int i = 0, v = 0, tot = 0; i < n * 2; i++)
	{
		if (s[i] == '(')
		{
			tot++;
			fa[tot] = v;
			v = tot;
			adj[fa[v]].push_back(v);
		}
		else
			v = fa[v];
	}

	for (int v = 2; v <= n; v++)
		d[v] = d[fa[v]] + 1;
	for (int v = n; v >= 2; v--)
	{
		if (size(adj[v]) == 0)
			d_s[v] = d_m[v] = d[v], nl[v] = 1;
		d_s[fa[v]] += d_s[v];
		relax(d_m[fa[v]], d_m[v]);
		nl[fa[v]] += nl[v];
	}
	for (int v = 1; v <= n; v++)
	{
		int l;
		l = d[v];
		for (int i = 0; i < size(adj[v]); i++)
			d_m_p[adj[v][i]] = l, relax(l, d_m[adj[v][i]]);
		l = d[v];
		for (int i = size(adj[v]) - 1; i >= 0; i--)
			d_m_s[adj[v][i]] = l, relax(l, d_m[adj[v][i]]);
	}

	sta_n = 0;
	cout << dfs(1) << endl;

	return 0;
}
