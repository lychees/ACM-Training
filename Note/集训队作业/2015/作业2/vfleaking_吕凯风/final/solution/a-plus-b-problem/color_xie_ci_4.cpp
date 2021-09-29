#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

const int MaxN = 500;

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
	const int MaxNVer = 1 + MaxN + MaxN + 1;
	const int MaxNE = MaxN * (3 + MaxN);

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

	namespace NF = NetworkFlows;

	NF::nVer = 1 + n + n + 1;
	NF::source = 0, NF::terminal = 1 + n + n;
	NF::init();

	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += bVal[i];
		NF::addEdge(NF::source, i, bVal[i]);

		sum += wVal[i];
		NF::addEdge(i, NF::terminal, wVal[i]);

		NF::addEdge(i, n + i, penalty[i]);
		for (int j = 1; j < i; j++)
		{
			if (qL[i] <= a[j] && a[j] <= qR[i])
				NF::addEdge(n + i, j, INT_MAX);
		}
	}

	NF::calcMaxFlows();
	cout << sum - NF::outcome_flow << endl;

	return 0;
}
