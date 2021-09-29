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

int n;
int fa[MaxN + 1];
int dep[MaxN + 1];
int tarv[MaxN + 1];
vector<int> adj[MaxN + 1];

int n_leaves[MaxN + 1];
s64 f[MaxN + 1], g[MaxN + 1];
int h[MaxN + 1];

void dp(int v)
{
	int vl = (int)adj[v].size();
	if (vl == 0)
	{
		n_leaves[v] = 1;
		return;
	}

	f[v] = S64_MAX;
	for (int i = 0; i < vl; i++)
		dp(adj[v][i]);

	for (int i = 0; i < vl; i++)
	{
		s64 cur = 0;

		int d = 0;
		for (int j = 0; j < vl; j++)
			if (j != i)
			{
				relax(d, h[adj[v][j]] + 1);
				cur += g[adj[v][j]] + n_leaves[adj[v][j]];
			}
		int nv = tarv[adj[v][i]];
		cur += dep[nv] - dep[v] - min(dep[nv] - dep[v], d);
		cur += f[nv];

		tension(f[v], cur);

		g[v] += g[adj[v][i]] + n_leaves[adj[v][i]];
		n_leaves[v] += n_leaves[adj[v][i]];
		relax(h[v], h[adj[v][i]] + 1);
	}

	tarv[v] = adj[v].size() == 1 ? tarv[adj[v][0]] : v;
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
		dep[v] = dep[fa[v]] + 1;
	for (int v = n; v >= 1; v--)
		tarv[v] = adj[v].size() == 1 ? tarv[adj[v][0]] : v;

	dp(1);

	cout << f[1] << endl;

	return 0;
}
