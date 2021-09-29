#include <bits/stdc++.h>//by matthew99

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

#define ctz __builtin_ctz
#define bcnt __builtin_popcount

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int Mod = 998244353;

const int maxn = 16, maxmask = 1 << maxn, maxmask3 = 45000000;

int cnt[maxmask + 5][maxn + 1];
int dp[maxmask3 + 5];

int pw3[maxn + 5];
int bit3[maxmask + 5];

int n, m;
int adj[maxn + 5];

int bc[maxmask + 5], cz[maxmask + 5];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	pw3[0] = 1;
	REP(i, 0, n) pw3[i + 1] = pw3[i] * 3;
	REP(i, 0, 1 << n)
	{
		bit3[i] = 0;
		REP(j, 0, n) if (i >> j & 1) bit3[i] += pw3[j];
	}
	REP(i, 0, 1 << n) bc[i] = bcnt(i), cz[i] = ctz(i);
	REP(i, 0, m)
	{
		int x, y;
		scanf("%d%d", &x, &y), --x, --y;
		if (x > y) swap(x, y);
		adj[x] |= 1 << y, adj[y] |= 1 << x;
		cnt[1 << x | 1 << y][y] = 1;
	}
	REP(i, 0, 1 << n) REP(j, 0, n) if (cnt[i][j]) REP(k, cz[i] + 1, n) if (adj[j] >> k & 1)
		if (!(i >> k & 1)) (cnt[i | (1 << k)][k] += cnt[i][j]) %= Mod;
	int ans = 0;
	REP(i, 0, 1 << n) if (bc[i] >= 3) for (int j = i; ; j = (j - 1) & i)
	{
		int id = bit3[i] + bit3[j];
		if (i == j) 
		{
			for (int to = adj[cz[i]]; to > 0; to -= to & -to) (dp[id] += cnt[i][cz[to]]) %= Mod;
			dp[id] = (LL)dp[id] * ((Mod + 1) >> 1) % Mod;
		}
		else
		{
			int k = (i ^ j) & -(i ^ j);
			dp[id] = 0;
			for (int l = adj[cz[k]] & i; l > 0; l -= l & -l) (dp[id] += dp[bit3[i ^ k] + bit3[j & ~(l & -l)]]) %= Mod;
			(dp[id] += dp[bit3[i] + bit3[j | k]]) %= Mod;
		}
		(ans += dp[id]) %= Mod;
		if (!j) break;
	}
	printf("%d\n", ans);
	return 0;
}


