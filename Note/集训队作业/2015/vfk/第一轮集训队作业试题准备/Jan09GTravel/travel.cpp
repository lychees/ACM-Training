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
halfEdge *faE[MaxN + 1];
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

int seg[MaxN * 4 + 1];

void seg_build(int p, int pL, int pR)
{
	seg[p] = INT_MAX;
	if (pL == pR)
		return;
	int pM = (pL + pR) / 2;
	seg_build(p << 1 | 0, pL, pM);
	seg_build(p << 1 | 1, pM + 1, pR);
}
void seg_set(int p, int pL, int pR, int q, int val)
{
	if (pL == pR)
	{
		seg[p] = val;
		return;
	}

	tension(seg[p << 1 | 0], seg[p]);
	tension(seg[p << 1 | 1], seg[p]);
	seg[p] = INT_MAX;

	int pM = (pL + pR) / 2;
	if (q <= pM)
		seg_set(p << 1 | 0, pL, pM, q, val);
	else
		seg_set(p << 1 | 1, pM + 1, pR, q, val);
}
int seg_query(int p, int pL, int pR, int q)
{
	if (pL == pR)
		return seg[p];
	int pM = (pL + pR) / 2;
	if (q <= pM)
		return min(seg[p], seg_query(p << 1 | 0, pL, pM, q));
	else
		return min(seg[p], seg_query(p << 1 | 1, pM + 1, pR, q));
}
void seg_cover(int p, int pL, int pR, int qL, int qR, int val)
{
	if (qL <= pL && pR <= qR)
	{
		tension(seg[p], val);
		return;
	}
	int pM = (pL + pR) / 2;
	if (qL <= pM)
		seg_cover(p << 1 | 0, pL, pM, qL, qR, val);
	if (pM < qR)
		seg_cover(p << 1 | 1, pM + 1, pR, qL, qR, val);
}

void dfs(int v)
{
	sta[++sta_n] = v;
	seg_set(1, 1, n, sta_n, INT_MAX);
	
	for (halfEdge *e = adj[v]; e; e = e->next)
	{
		if (fa[e->u][0] == v)
			dfs(e->u);
		else if (fa[v][0] != e->u)
		{
			int lca = getLCA(v, e->u);
			if (dep[lca] + 1 <= sta_n)
				seg_cover(1, 1, n, dep[lca] + 1, sta_n, dist[e->u] + e->w + dist[v]);
		}
	}

	outcome[v] = seg_query(1, 1, n, dep[v]);
	if (outcome[v] != INT_MAX)
		outcome[v] -= dist[v];

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

	pre_dfs(1);

	sta_n = 0;
	seg_build(1, 1, n);
	dfs(1);

	for (int v = 2; v <= n; v++)
		printf("%d\n", outcome[v] != INT_MAX ? outcome[v] : -1);

	return 0;
}
