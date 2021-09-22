/*#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int u = 100010;
vector<int> suc[u];//successors
vector<int> pre[u];//predecessors
vector<int> dom[u];//dominate
int fa[u];//DFS tree father
int dfn[u];//DFS order number
int semi[u];//smallest [dfn] in predecessors
int idom[u];//immediate dominator
int anc[u];//ancestor in disjoint set
int best[u];//[dfn] of the vertex with the smallest [semi] in ancestor chain
int id[u];//vertex number of [dfn]
__int64 sum[u];
int n, m, t;

void initial()
{
	for (int i = 1; i <= n; i++)
	{
		suc[i].clear();
		pre[i].clear();
		dom[i].clear();
		anc[i] = semi[i] = best[i] = i;
		sum[i] = dfn[i] = id[i] = fa[i] = idom[i] = 0;
	}
	t = 0;
}

void add(int x, int y)
{
	suc[x].push_back(y);
	pre[y].push_back(x);
}

int get(int x)
{
	if (x == anc[x]) return x;
	int y = get(anc[x]);
	if (semi[best[x]]>semi[best[anc[x]]]) best[x] = best[anc[x]];
	return anc[x] = y;
}

void dfs(int x)
{
	int y;
	dfn[x] = ++t, id[t] = x;
	for (int i = 0; i<suc[x].size(); i++)
	if (!dfn[y = suc[x][i]])
	{
		dfs(y);
		fa[dfn[y]] = dfn[x];
	}
}

void tarjan()
{
	for (int y = t; y>1; y--)
	{
		int x = fa[y];
		for (int i = 0; i<pre[id[y]].size(); i++)
		{
			int z = dfn[pre[id[y]][i]];
			if (!z) continue;
			get(z);
			semi[y] = min(semi[y], semi[best[z]]);
		}
		dom[semi[y]].push_back(y);
		anc[y] = x;
		for (int i = 0; i<dom[x].size(); i++)
		{
			int z = dom[x][i];
			get(z);
			idom[z] = semi[best[z]]<x ? best[z] : x;
		}
		dom[x].clear();
	}
	for (int i = 2; i <= t; i++)
	{
		if (idom[i] != semi[i]) idom[i] = idom[idom[i]];
		dom[idom[i]].push_back(i);
	}
	idom[1] = 0;
}

void calc(int x)
{
	sum[id[x]] += id[x];
	for (int i = 0; i<dom[x].size(); i++)
	{
		int y = dom[x][i];
		sum[id[y]] = sum[id[x]];
		calc(y);
	}
}

int main()
{
	while (cin >> n >> m)
	{
		initial();
		for (int i = 1; i <= m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		dfs(n);
		tarjan();
		calc(1);
		for (int i = 1; i<n; i++) printf("%I64d ", sum[i]);
		printf("%I64d\n", sum[n]);
	}
	return 0;
}*/