#include "testlib.h"
#include <cstdio>
#include <queue>
#include <set>
#include <utility>
using namespace std;

typedef long long s64;
typedef pair<s64, int> PII;

const s64 S64_MAX = 9223372036854775807ll;
const s64 INF = S64_MAX >> 1;

const int MaxN = 100000;
const int MaxNA = 21;
const int MaxA0 = 10000;

int main(int argc, char **argv)
{
	registerGen(argc, argv, 1);

	s64 h;
	int n, m;
	int a_0;

	int nA = 0;
	static s64 a[MaxNA];

	sscanf(argv[1], "%lld", &h);
	sscanf(argv[2], "%d", &n);
	sscanf(argv[3], "%d", &m);
	sscanf(argv[4], "%d", &a_0);

	printf("%lld %d %d %d\n", h, n, m, a_0);

	nA = 0;
	a[nA++] = a_0;

	set<int> posS;

	static bool taken[MaxN];
	static bool valid[MaxN];
	static s64 pos[MaxN];
	static int cost[MaxN];
	for (int i = 0; i < n; i++)
	{
		s64 p;
		do
			p = rnd.next(1ll, h);
		while (posS.count(p));

		posS.insert(p);

		pos[i] = p - 1, cost[i] = rnd.next(1000000000);

		printf("%lld %d\n", p, cost[i]);
	}

	static s64 dist[MaxA0];
	dist[0] = 0;
	fill(dist + 1, dist + a[0], INF);

	int rest = 0;
	priority_queue<PII> q;
	for (int i = 0; i < n; i++)
		if (!taken[i] && (valid[i] = dist[pos[i] % a[0]] <= pos[i]))
			rest++, q.push(PII(cost[i], -i));

	int nT1 = 0;

	while (m--)
	{
		int type;
		do
		{
			if (rnd.next(100) <= 10)
			{
				if (nT1 < 20)
				{
					type = 1;
					break;
				}
			}
			else if (rnd.next(90) <= 80)
			{
				if (rest > 0)
				{
					type = 2;
					break;
				}
			}
			else
			{
				type = 3;
				break;
			}
		}
		while (true);

		if (type == 1)
		{
			nT1++;

			while (!q.empty())
				q.pop();

			s64 a_x;
			do
			{
				if (rnd.next(100) < 5) {
					a_x = rnd.next(1ll, h);
				} else {
					a_x = rnd.next(1ll, min(h, 1000000ll));
				}
			}
			while (a_x == 1);

			printf("1 %lld\n", a_x);

			a[nA++] = a_x;

			dist[0] = 0;
			fill(dist + 1, dist + a[0], INF);
			q.push(PII(-dist[0], -0));

			while (!q.empty())
			{
				PII cur = q.top();
				q.pop();
				if (cur.first != -dist[-cur.second])
					continue;
				int v = -cur.second;

				for (int i = 1; i < nA; i++)
				{
					int u = (v + a[i]) % a[0];
					if (dist[v] + a[i] < dist[u])
					{
						dist[u] = dist[v] + a[i];
						q.push(PII(-dist[u], -u));
					}
				}
			}

			rest = 0;
			for (int i = 0; i < n; i++)
				if (!taken[i] && (valid[i] = dist[pos[i] % a[0]] <= pos[i]))
					q.push(PII(cost[i], -i)), rest++;
		}
		else if (type == 2)
		{
			int x;
			if (rnd.next(100) <= 10)
				x = -q.top().second;
			else
			{
				do
					x = rnd.next(n);
				while (!(!taken[x] && valid[x]));
			}

			int y = rnd.next(cost[x]);

			printf("2 %d %d\n", x + 1, y);

			cost[x] -= y;
			if (!taken[x] && valid[x])
				q.push(PII(cost[x], -x));
		}
		else if (type == 3)
		{
			printf("3\n");
			while (true)
			{
				if (q.empty())
					break;
				else
				{
					PII cur = q.top();
					q.pop();

					if (cur.first != cost[-cur.second])
						continue;
					int v = -cur.second;
					if (taken[v])
						continue;
					taken[v] = true;
					rest--;
					break;
				}
			}
		}
	}

	return 0;
}
