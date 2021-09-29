#include <iostream>
#include <cstdio>
#include <climits>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int MaxN = 100000;
const int MaxLogN = 17;
const int MaxM = 200000;

template <class T>
inline bool tension(T &a, const T &b)
{
	if (b < a)
	{
		a = b;
		return true;
	}
	return false;
}

struct halfEdge
{
	int u, w;
	halfEdge *next;
};
halfEdge adj_pool[MaxM * 2], *adj_tail = adj_pool;

int n, m;
halfEdge *adj[MaxN + 1];
int dist[MaxN + 1];

inline void addEdge(int v, int u, int w)
{
	adj_tail->u = u, adj_tail->w = w, adj_tail->next = adj[v], adj[v] = adj_tail++;
}

int outcome[MaxN + 1];

int dep[MaxN + 1];
int fa[MaxN + 1][MaxLogN + 1];

void pre_dfs(int v)
{
	dep[v] = dep[fa[v][0]] + 1;
	for (int j = 0; fa[v][j]; j++)
		fa[v][j + 1] = fa[fa[v][j]][j];
	for (halfEdge *e = adj[v]; e; e = e->next)
		if (dist[v] + e->w == dist[e->u])
			fa[e->u][0] = v, pre_dfs(e->u);
}

int getLCA(int v, int u)
{
	if (dep[v] < dep[u])
		swap(v, u);
	for (int k = 0, delta = dep[v] - dep[u]; delta > 0; delta >>= 1, k++)
		if (delta & 1)
			v = fa[v][k];
	if (v == u)
		return v;
	int k = 0;
	while (k >= 0)
	{
		if (fa[v][k] == fa[u][k])
			k--;
		else
		{
			v = fa[v][k];
			u = fa[u][k];
			k++;
		}
	}
	return fa[v][0];
}

int sta_n;
int sta[MaxN + 1];

void dfs(int v)
{
	sta[++sta_n] = v;
	for (halfEdge *e = adj[v]; e; e = e->next)
	{
		if (fa[e->u][0] == v)
			dfs(e->u);
		else if (fa[v][0] != e->u)
		{
			int lca = getLCA(v, e->u);
			for (int i = dep[lca] + 1; i <= sta_n; i++)
				tension(outcome[sta[i]], dist[e->u] + e->w + dist[v] - dist[sta[i]]);
		}
	}
	sta_n--;
}

int main()
{
	cin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		addEdge(v, u, w), addEdge(u, v, w);
	}

	priority_queue<PII> q;
	for (int v = 1; v <= n; v++)
		dist[v] = INT_MAX;
	dist[1] = 0, q.push(PII(-0, 1));

	while (!q.empty())
	{
		PII cur = q.top();
		q.pop();
		if (cur.first != -dist[cur.second])
			continue;
		int v = cur.second;

		for (halfEdge *e = adj[v]; e; e = e->next)
			if (tension(dist[e->u], dist[v] + e->w))
				q.push(PII(-dist[e->u], e->u));
	}

	for (int v = 1; v <= n; v++)
		outcome[v] = INT_MAX;

	pre_dfs(1);

	sta_n = 0;
	dfs(1);

	for (int v = 2; v <= n; v++)
		printf("%d\n", outcome[v] != INT_MAX ? outcome[v] : -1);

	return 0;
}
