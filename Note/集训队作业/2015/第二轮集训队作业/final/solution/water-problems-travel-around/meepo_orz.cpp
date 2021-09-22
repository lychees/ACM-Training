#include <iostream>
#include <cstdio>
#include <bitset>
#include <utility>
#include <queue>
#include <set>
using namespace std;

const int MaxN = 12;

int n;
vector<int> adj[MaxN];

struct status
{
	int book;
	int v, u;
	vector< pair<int, int> > path;

	friend inline bool operator<(const status &lhs, const status &rhs)
	{
		if (lhs.book != rhs.book)
			return lhs.book < rhs.book;
		if (lhs.v != rhs.v)
			return lhs.v < rhs.v;
		return lhs.u < rhs.u;
	}
};

int main()
{
	static int fa[MaxN];
	static char s[MaxN * 2 + 1];

	cin >> n;
	scanf("%s", s);
	for (int v = 0; v < n; v++)
		adj[v].push_back(v);
	for (int i = 0, v = 0, tot = -1; i < n * 2; i++)
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

	status sta;
	sta.book = 0;
	sta.v = sta.u = 0;
	sta.book |= 1 << 0;
	sta.path.push_back(make_pair(0, 0));

	set<status> status_set;
	queue< pair<status, int> > q;
	status_set.insert(sta), q.push(make_pair(sta, 0));

	while (!q.empty())
	{
		sta = q.front().first;
		int dist = q.front().second;
		q.pop();

		if (sta.book == (1 << n) - 1)
		{
			cout << dist << endl;
			break;
		}

		int vl = (int)adj[sta.v].size();
		int ul = (int)adj[sta.u].size();
		for (int i = 0; i < vl; i++)
			for (int j = 0; j < ul; j++)
			{
				int nv = adj[sta.v][i];
				int nu = adj[sta.u][j];

				status next = sta;
				next.book |= 1 << nv;
				next.book |= 1 << nu;
				next.v = nv, next.u = nu;
				next.path.push_back(make_pair(nv, nu));

				if (!status_set.count(next))
					status_set.insert(next), q.push(make_pair(next, dist + 1));

				next.v = nv, next.u = nv;
				if (!status_set.count(next))
					status_set.insert(next), q.push(make_pair(next, dist + 1));

				next.v = nu, next.u = nu;
				if (!status_set.count(next))
					status_set.insert(next), q.push(make_pair(next, dist + 1));
			}
	}

	return 0;
}
