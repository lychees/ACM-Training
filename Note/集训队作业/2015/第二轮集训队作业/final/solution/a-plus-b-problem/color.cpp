#include <iostream>
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

const int MaxN = 5000;
const int MaxLogN = 13;

const int MaxNSegNode = MaxN * (MaxLogN + 1);
const int MaxNSegRes = 2 * (MaxLogN + 1);

// getint
inline int getint()
{
    char c;
    while (c = getchar(), ('0' > c || c > '9') && c != '-');
    
    if (c != '-')
    {
        int res = c - '0';
        while (c = getchar(), '0' <= c && c <= '9')
            res = res * 10 + c - '0';
        return res;
    }
    else
    {
        int res = 0;
        while (c = getchar(), '0' <= c && c <= '9')
            res = res * 10 + c - '0';
        return -res;
    }
}

// adjust
template <class T>
inline bool relax(T &a, const T &b)
{
	if (b > a)
	{
		a = b;
		return true;
	}
	return false;
}
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

// max flows
namespace NetworkFlows
{
	const int MaxNVer = 1 + MaxN + MaxN + MaxNSegNode + 1;
	const int MaxNE = MaxNSegNode * 2 + MaxN + MaxN + MaxN * (3 + MaxNSegRes);

	struct halfEdge
	{
		int u, w;
		halfEdge *next;
	};
	halfEdge adj_pool[MaxNE * 2], *adj_tail;

	int nVer;
	int source, terminal;
	halfEdge *adj[MaxNVer];

	inline void init()
	{
		fill(adj, adj + nVer, (halfEdge *)NULL);
		adj_tail = adj_pool;
	}
	inline void addEdge(const int &v, const int &u, const int &w)
	{
		adj_tail->u = u, adj_tail->w = w, adj_tail->next = adj[v], adj[v] = adj_tail++;
		adj_tail->u = v, adj_tail->w = 0, adj_tail->next = adj[u], adj[u] = adj_tail++;
	}

	inline halfEdge *opposite(halfEdge *e)
	{
		return adj_pool + ((e - adj_pool) ^ 1);
	}

	int outcome_flow;

	int dist[MaxNVer];
	int book[MaxNVer];

	int dfs(const int &v, const int &delta)
	{
		if (v == terminal)
			return delta;
		int flow = 0;
		for (halfEdge *i = adj[v]; i; i = i->next)
			if (i->w > 0 && dist[v] == dist[i->u] + 1)
			{
				int add = dfs(i->u, min(i->w, delta - flow));
				i->w -= add, opposite(i)->w += add;
				flow += add;

				if (flow == delta || dist[source] == INT_MAX)
					return flow;
			}
		if (flow == 0)
		{
			if (--book[dist[v]] == 0)
			{
				dist[source] = INT_MAX;
				return 0;
			}

			dist[v] = INT_MAX;
			for (halfEdge *i = adj[v]; i; i = i->next)
				if (i->w > 0 && dist[i->u] != INT_MAX)
					tension(dist[v], dist[i->u] + 1);
			if (dist[v] != INT_MAX)
				book[dist[v]]++;
		}
		return flow;
	}

	inline void calcMaxFlows()
	{
		fill(dist, dist + nVer, 0);
		fill(book, book + nVer, 0);
		book[0] = nVer;

		outcome_flow = 0;
		while (dist[source] != INT_MAX)
			outcome_flow += dfs(source, INT_MAX);
	}
}

struct seg_node
{
	seg_node *lc, *rc;
};
seg_node seg_pool[MaxNSegNode], *seg_tail = seg_pool;

seg_node *seg_add(seg_node *p, const int &pL, const int &pR, const int &val)
{
	seg_node *np = seg_tail++;
	if (p)
		*np = *p;
	else
		np->lc = np->rc = NULL;

	if (pL == pR)
		return np;

	int pMid = pL + pR >> 1;
	if (val <= pMid)
		np->lc = seg_add(np->lc, pL, pMid, val);
	else
		np->rc = seg_add(np->rc, pMid + 1, pR, val);
	return np;
}

int seg_res_n;
seg_node *seg_res[MaxNSegRes];

void seg_query(seg_node *p, const int &pL, const int &pR, const int &qL, const int &qR)
{
	if (!p)
		return;
	if (qL <= pL && pR <= qR)
	{
		seg_res[seg_res_n++] = p;
		return;
	}

	int pMid = pL + pR >> 1;
	if (qL <= pMid)
		seg_query(p->lc, pL, pMid, qL, qR);
	if (pMid < qR)
		seg_query(p->rc, pMid + 1, pR, qL, qR);
}

int main()
{
	int n;
	static int a[MaxN + 1];
	static int bVal[MaxN], wVal[MaxN + 1];
	static int qL[MaxN + 1], qR[MaxN + 1];
	static int penalty[MaxN + 1];

	cin >> n;
	for (int i = 1; i <= n; i++)
		a[i] = getint(), bVal[i] = getint(), wVal[i] = getint(), qL[i] = getint(), qR[i] = getint(), penalty[i] = getint();

	int seqA_n = 0;
	static int seqA[MaxN];
	for (int i = 1; i <= n; i++)
		seqA[seqA_n++] = a[i];
	sort(seqA, seqA + seqA_n);
	seqA_n = unique(seqA, seqA + seqA_n) - seqA;

	for (int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(seqA, seqA + seqA_n, a[i]) - seqA;
		qL[i] = lower_bound(seqA, seqA + seqA_n, qL[i]) - seqA;
		qR[i] = upper_bound(seqA, seqA + seqA_n, qR[i]) - seqA - 1;
	}

	static seg_node *tr[MaxN + 1];
	tr[0] = NULL;
	for (int i = 1; i <= n; i++)
		tr[i] = seg_add(tr[i - 1], 0, n - 1, a[i]);

	int nSegNode = seg_tail - seg_pool;

	namespace NF = NetworkFlows;

	NF::nVer = 1 + n + n + nSegNode + 1;
	NF::source = 0, NF::terminal = NF::nVer - 1;
	NF::init();

	int sum = 0;

	int shSeg = 1 + n + n;

	for (seg_node *p = seg_pool; p != seg_tail; p++)
	{
		if (p->lc)
			NF::addEdge(shSeg + p - seg_pool, shSeg + p->lc - seg_pool, INT_MAX);
		if (p->rc)
			NF::addEdge(shSeg + p - seg_pool, shSeg + p->rc - seg_pool, INT_MAX);
	}
	for (int i = 1; i <= n; i++)
	{
		seg_res_n = 0;
		seg_query(tr[i], 0, n - 1, a[i], a[i]);
		seg_node *cur = seg_res[0];

		seg_res_n = 0;
		seg_query(tr[i - 1], 0, n - 1, a[i], a[i]);
		seg_node *last = seg_res[0];

		NF::addEdge(shSeg + cur - seg_pool, i, INT_MAX);
		if (last)
			NF::addEdge(shSeg + cur - seg_pool, shSeg + last - seg_pool, INT_MAX);
	}
	for (int i = 1; i <= n; i++)
	{
		sum += bVal[i];
		NF::addEdge(NF::source, i, bVal[i]);

		sum += wVal[i];
		NF::addEdge(i, NF::terminal, wVal[i]);

		NF::addEdge(i, n + i, penalty[i]);
		if (qL[i] <= qR[i])
		{
			seg_res_n = 0;
			seg_query(tr[i - 1], 0, n - 1, qL[i], qR[i]);

			for (int j = 0; j < seg_res_n; j++)
				NF::addEdge(n + i, shSeg + seg_res[j] - seg_pool, INT_MAX);
		}
	}

	NF::calcMaxFlows();
	cout << sum - NF::outcome_flow << endl;

	return 0;
}
