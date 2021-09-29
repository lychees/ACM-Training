#include <bits/stdc++.h>

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second

using namespace std;

typedef long long LL;

const int oo = 0x3f3f3f3f;

template<typename T> bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T> bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

const int maxn = 100;

int n;
pair<int, int> a[maxn + 5], b[(maxn << 1) + 5];

int dp[2][(maxn << 1) + 5][(maxn << 1) + 5][(maxn << 1) + 5];

int ans = 0;

inline void init()
{
	scanf("%d", &n);
	REP(i, 0, n)
		scanf("%d%d", &a[i].x, &a[i].y);
}

inline void extend(const int &i, const int &cur, const int &nxt, const int &j, const int &k, const int &k0)
{
	int l = b[i].x, r = b[i].y;
	if ((j == n << 1 || l > b[j].x) && (l < b[k].x || r > b[k0].y))
	{
		if (k0 == n << 1 || l >= b[k0].y) 
		{
			chkmax(dp[nxt][k0][i][i], dp[cur][j][k][k0] + r - l);
		}
		else
		{
			int tmp = dp[cur][j][k][k0];
			int newk = k;
			if (l < b[k].x) newk = i, tmp += b[k].x - max(l, b[j].y);
			int newk0 = k0;
			if (r > b[k0].y) newk0 = i, tmp += r - b[k0].y;
			chkmax(dp[nxt][j][newk][newk0], tmp);
		}
	}
}

inline void solve()
{
	sort(a, a + n);
	REP(i, 0, n)
		b[i << 1] = mp(a[i].x - a[i].y, a[i].x), b[i << 1 | 1] = mp(a[i].x, a[i].x + a[i].y);
	b[n << 1].x = oo;
	b[n << 1].y = -oo;
	memset(dp, -oo, sizeof dp);
	dp[0][n << 1][n << 1][n << 1] = 0;
	REP(i, 0, n)
	{
		int cur = i & 1, nxt = !cur;
		REP(j, 0, n << 1 | 1)
			REP(k, 0, n << 1 | 1)
				REP(k0, 0, n << 1 | 1)
					if (dp[cur][j][k][k0] >= 0)
					{
						extend(i << 1, cur, nxt, j, k, k0);
						extend(i << 1 | 1, cur, nxt, j, k, k0);
						chkmax(dp[nxt][j][k][k0], dp[cur][j][k][k0]);
					}
	}
	ans = 0;
	REP(j, 0, n << 1 | 1)
		REP(k, 0, n << 1 | 1)
			REP(k0, 0, n << 1 | 1)
				chkmax(ans, dp[n & 1][j][k][k0]);
}

inline void output()
{
	printf("%d\n", ans);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	init();
	solve();
	output();
	return 0;
} 
