#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

const int MaxN = 100000;
const int MaxM = 200000;

struct edge
{
	int v, u, w;
	edge(){}
	edge(const int &_v, const int &_u, const int &_w)
		: v(_v), u(_u), w(_w){}
};

int main(int argc, char **argv)
{
	registerGen(argc, argv, 1);

	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int l_max = atoi(argv[3]);

	int eli_n = 0;
	static edge eli[MaxM];
	static set<pair<int, int> > eS;
	static int dist[MaxN + 1];
	dist[1] = 0;
	for (int v = 2; v <= n; v++)
	{
		int u;
		if (v == 2)
			u = 1;
		else
			u = rnd.next(max(1, (v + 1) / 2 - l_max), (v + 1) / 2 - 1) * 2 - v % 2;
		dist[v] = dist[u] + rnd.next(1, 10);

		eli[eli_n++] = edge(u, v, dist[v] - dist[u]);
		eS.insert(make_pair(v, u));
		eS.insert(make_pair(u, v));
	}

	while (eli_n < m)
	{
		int v = rnd.next(1, n), u = rnd.next(1, n), w = rnd.next(1, 1000);
		if (v == u)
			continue;
		if (w <= abs(dist[v] - dist[u]))
			continue;
		if (eS.count(make_pair(v, u)))
			continue;
		eli[eli_n++] = edge(v, u, w);
		eS.insert(make_pair(v, u));
		eS.insert(make_pair(u, v));
	}

	shuffle(eli, eli + eli_n);

	static int lab[MaxN + 1];
	for (int v = 1; v <= n; v++)
		lab[v] = v;
	shuffle(lab + 2, lab + n + 1);

	printf("%d %d\n", n, m);
	for (int i = 0; i < eli_n; i++)
	{
		if (rnd.next(100) < 50)
			swap(eli[i].v, eli[i].u);
		printf("%d %d %d\n", lab[eli[i].v], lab[eli[i].u], eli[i].w);
	}

	return 0;
}
