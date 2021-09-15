#include <iostream>
#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

typedef long long s64;
typedef pair<s64, int> PII;

const s64 S64_MAX = 9223372036854775807ll;
const s64 INF = S64_MAX >> 1;

const int MaxN = 100000;
const int MaxM = 100000;
const int MaxNA = 21;
const int MaxA0 = 10000;

inline s64 getint()
{
	char c;
	while (c = getchar(), ('0' > c || c > '9') && c != '-');

	if (c != '-')
	{
		s64 res = c - '0';
		while (c = getchar(), '0' <= c && c <= '9')
			res = res * 10 + c - '0';
		return res;
	}
	else
	{
		s64 res = 0;
		while (c = getchar(), '0' <= c && c <= '9')
			res = res * 10 + c - '0';
		return -res;
	}
}

struct Heap
{
	int n;
	PII a[MaxN + MaxM];

	void push(PII v)
	{
		int p = ++n;
		a[p] = v;
		while (p > 1 && a[p] > a[p >> 1])
			swap(a[p], a[p >> 1]), p >>= 1;
	}
	bool empty()
	{
		return n == 0;
	}
	void clear()
	{
		n = 0;
	}
	PII top()
	{
		return a[1];
	}
	void pop()
	{
		swap(a[1], a[n]);
		n--;

		if (n >= 1)
		{
			int p = 1;
			while (true)
			{
				int lp = p << 1, rp = p << 1 | 1;
				if (lp > n)
					break;
				int target = (rp > n || a[lp] > a[rp]) ? lp : rp;
				if (a[target] <= a[p])
					break;
				swap(a[p], a[target]);
				p = target;
			}
		}
	}
};

int main()
{
	s64 h;
	int n, m;

	int nA = 0;
	static s64 a[MaxNA];

	cin >> h >> n >> m;
	
	nA = 0;
	a[nA++] = getint();

	static bool taken[MaxN];
	static bool valid[MaxN];
	static s64 pos[MaxN];
	static int cost[MaxN];
	for (int i = 0; i < n; i++)
		pos[i] = getint() - 1, cost[i] = getint();

	static s64 dist[MaxA0];
	dist[0] = 0;
	fill(dist + 1, dist + a[0], INF);

	static Heap q;
	for (int i = 0; i < n; i++)
		if (!taken[i] && (valid[i] = dist[pos[i] % a[0]] <= pos[i]))
			q.push(PII(cost[i], -i));

	while (m--)
	{
		int type = getint();
		if (type == 1)
		{
			q.clear();

			a[nA++] = getint();

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

			for (int i = 0; i < n; i++)
				if (!taken[i] && (valid[i] = dist[pos[i] % a[0]] <= pos[i]))
					q.push(PII(cost[i], -i));
		}
		else if (type == 2)
		{
			int x = getint() - 1, y = getint();
			cost[x] -= y;
			if (!taken[x] && valid[x])
				q.push(PII(cost[x], -x));
		}
		else if (type == 3)
		{
			while (true)
			{
				if (q.empty())
				{
					printf("0\n");
					break;
				}
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
					printf("%d\n", cost[v]);
					break;
				}
			}
		}
	}

	return 0;
}
