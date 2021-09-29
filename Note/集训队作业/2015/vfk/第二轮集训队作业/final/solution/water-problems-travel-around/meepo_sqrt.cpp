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

struct halfEdge
{
	int u;
	halfEdge *next;
};
halfEdge adj_pool[MaxN], *adj_tail = adj_pool;

int n;
int fa[MaxN + 1];
halfEdge *adj[MaxN + 1];

inline void addEdge(int v, int u)
{
	adj_tail->u = u, adj_tail->next = adj[v], adj[v] = adj_tail++;
}

s64 f[MaxN + 1];
int nl[MaxN + 1];
int d[MaxN + 1];
s64 ds[MaxN + 1];
int dm[MaxN + 1];
int dmp[MaxN + 1], dms[MaxN + 1], dmc[MaxN + 1];

int sta_n;
int sta[MaxN];

int max_sta_n;
s64 tot_back = 0;

s64 dfs(int r)
{
	relax(max_sta_n, sta_n);

	if (!adj[r])
		return f[r];

	s64 res = S64_MAX;
	for (halfEdge *e = adj[r]; e; e = e->next)
	{
		int v = e->u;
		dmc[r] = max(dmp[v], dms[v]);

		int old_sta_n = sta_n;
		while (sta_n > 0 && dmc[sta[sta_n - 1]] <= dmc[r])
			sta_n--, tot_back++;
		int old_val = sta[sta_n];
		sta[sta_n++] = r;

		f[v] = S64_MAX;
		int p = sta_n;
		if (p > 0 && dmc[sta[p - 1]] < d[v])
			p--;
		if (p > 0)
		{
			int u = sta[p - 1];
			tension(f[v], f[u] + (ds[u] - ds[v] - (s64)d[u] * (nl[u] - nl[v])));
		}
		if (!adj[r]->next)
			tension(f[v], f[r] + 1);

		tension(res, dfs(v));

		sta[--sta_n] = old_val;
		sta_n = old_sta_n;
	}
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
			addEdge(fa[v], v);
		}
		else
			v = fa[v];
	}

	for (int v = 2; v <= n; v++)
		d[v] = d[fa[v]] + 1;
	for (int v = n; v >= 2; v--)
	{
		if (!adj[v])
			ds[v] = dm[v] = d[v], nl[v] = 1;
		ds[fa[v]] += ds[v];
		relax(dm[fa[v]], dm[v]);
		nl[fa[v]] += nl[v];
	}
	for (int v = 1; v <= n; v++)
	{
		int adj_v_n = 0;
		static int adj_v[MaxN];

		for (halfEdge *e = adj[v]; e; e = e->next)
			adj_v[adj_v_n++] = e->u;

		int l;
		l = d[v];
		for (int i = 0; i < adj_v_n; i++)
			dmp[adj_v[i]] = l, relax(l, dm[adj_v[i]]);
		l = d[v];
		for (int i = adj_v_n - 1; i >= 0; i--)
			dms[adj_v[i]] = l, relax(l, dm[adj_v[i]]);
	}

	sta_n = 0;
	f[1] = 0;
	cout << dfs(1) << endl;

	cerr << max_sta_n << endl;
	cerr << tot_back << endl;

	return 0;
}
