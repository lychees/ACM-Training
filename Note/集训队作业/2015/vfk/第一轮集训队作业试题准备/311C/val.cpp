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

int main()
{
	registerValidation();

	s64 h;
	int n, m;
	int a_0;

	int nA = 0;
	static s64 a[MaxNA];
	
	h = inf.readLong(1ll, 1000000000000000000ll, "h");
	inf.readSpace();
	n = inf.readInt(1, 100000, "n");
	inf.readSpace();
	m = inf.readInt(1, 100000, "m");
	inf.readSpace();
	a_0 = inf.readInt(1, 10000, "k");
	inf.readEoln();

	nA = 0;
	a[nA++] = a_0;

	set<s64> posS;

	static bool taken[MaxN];
	static bool valid[MaxN];
	static s64 pos[MaxN];
	static int cost[MaxN];
	for (int i = 0; i < n; i++)
	{
		pos[i] = inf.readLong(1ll, h, "pos") - 1;
		inf.readSpace();
		cost[i] = inf.readInt(1, 1000000000, "c_i");
		inf.readEoln();
		
		ensuref(posS.count(pos[i]) == 0, "posS!!!");
		posS.insert(pos[i]);
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
		int type = inf.readInt(1, 3, "type");

		if (type == 1)
		{
			inf.readSpace();
			nT1++;
			ensuref(nT1 <= 20, "nT1 > 20");

			while (!q.empty())
				q.pop();

			s64 a_x = inf.readLong(1ll, h, "a_x");

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
			inf.readSpace();
			int x = inf.readInt(1, n, "x") - 1;
			inf.readSpace();
			int y = inf.readInt(0, cost[x] - 1, "y");
			
			cost[x] -= y;
			ensuref(!taken[x], "taken x");
			if (!taken[x] && valid[x])
				q.push(PII(cost[x], -x));
		}
		else if (type == 3)
		{
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
		inf.readEoln();
	}
	inf.readEof();
}
