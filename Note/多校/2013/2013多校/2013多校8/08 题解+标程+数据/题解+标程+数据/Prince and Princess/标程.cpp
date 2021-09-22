#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int head[500000], L;
struct Edge
{
    int to, next;
} edge[499999 * 2];
int N;
struct List
{
    long long dp, sum;
    List *next[20];
} list[500001];
long long ans = 0;
int f[500000], p[500000], r[500000];
long long calc(int v, List *q)
{
    if (!q)
        return 0x7fffffffffffffffLL;
    return q -> dp - (long long)p[v] * q -> sum;
}
long long getDP(int v, List *p)
{
    long long ret = calc(v, p);
    for (int i = 19; i >= 0; --i)
        if (p -> next[i] && p -> next[i] -> next[0] && calc(v, p -> next[i] -> next[0]) < calc(v, p -> next[i]))
            p = p -> next[i];
    return min(ret, calc(v, p -> next[0]));
}
bool check(List *a, List *b, List *c)
{
    long long num1 = a -> dp - b -> dp, num2 = b -> dp - c -> dp;
    long long dem1 = a -> sum - b -> sum, dem2 = b -> sum - c -> sum;
    if (num1 / dem1 != num2 / dem2)
        return num1 / dem1 < num2 / dem2;
    else
        return num1 % dem1 <= num2 % dem2;
}
List *getPos(List *p, List *q) // AC°æ
{
    if (!q -> next[0] || !check(p, q, q -> next[0]))
        return q;
    for (int i = 19; i >= 0; --i)
        if (q -> next[i] && q -> next[i] -> next[0] && check(p, q -> next[i], q -> next[i] -> next[0]))
            q = q -> next[i];
    return q -> next[0];
}
/*List *getPos(List *p, List *q) // ³¬Ê±°æ
{
    if (!q -> next[0] || !check(p, q, q -> next[0]))
        return q;
    for (int i = 0; 1; )
        if (q -> next[i] && q -> next[i] -> next[0] && check(p, q -> next[i], q -> next[i] -> next[0]))
            q = q -> next[i];
        else
            break;
    return q -> next[0];
}*/
//void dfs(int u, int fu)
void bfs(int s)
{
	queue <pair <int, int> > que;
	que.push(make_pair(s, -1));
	while (!que.empty())
	{
		int u = que.front().first, fu = que.front().second;
		//printf("%d %d\n", u, fu);
		que.pop();
		List *now = &list[fu], *tmp = &list[u];
		tmp -> dp = getDP(u, now);
		tmp -> sum = now -> sum + f[u];
	    ///dp[v] = min{dp[u] + (sum[v] - sum[u]) * p[v] + r[v]}
		///dp[v] = min{dp[u] - sum[u] * p[v]} + sum[v] * p[v] + r[v];
		tmp -> dp += (long long) p[u] * tmp -> sum + r[u];
	    tmp -> next[0] = getPos(tmp, now);
		now = tmp;
		for (int i = 1; i < 20; ++i)
			if (now -> next[i - 1])
				now -> next[i] = now -> next[i - 1] -> next[i - 1];
			else
				break;
		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].to;
			if (v == fu)
				continue;
			que.push(make_pair(v, u));
		}
		if (u)
			ans += tmp -> dp;
	}
}
void add_edge(int u, int v)
{
    edge[L].to = v;
    edge[L].next = head[u];
    head[u] = L++;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output1.txt","w",stdout);
    int t;
    scanf("%d", &t);
    for (int cas = 1; cas <= t; ++cas)
    {
        int n;
        scanf("%d", &n);
        memset(head, -1, 4 * n);
        L = N = 0;
        for (int i = 0; i < n; ++i)
            scanf("%d%d%d", &f[i], &p[i], &r[i]);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(--u, --v);
            add_edge(v, u);
        }
		for (int i = 0; i <= n; ++i)
			memset(list[i].next, 0, sizeof(list[i].next));
        list[0].dp = list[0].sum = 0;
        ans = 0;
		bfs(0);
        printf("Case %d: %lld\n", cas, ans);
    }
    return 0;
}
