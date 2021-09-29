#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int Mod = 998244353;

const int oo = 0x3f3f3f3f;

const int maxn = 38, maxm = 19;

int pw[maxn * (maxn - 1) + 5];

int n, m, ans;

int from[maxm + 5], to[maxm + 5], w[maxm + 5];

vector<int> v[maxn + 5];
int vis[maxn + 5], id[maxn + 5];

int tot = 0;
vector<int> seq;
void dfs(int x) { id[x] = SZ(seq), seq.pb(x), vis[x] = tot; for (auto y : v[x]) if (!~vis[y]) dfs(y); }

int sum[maxn + 5][maxn + 5];

inline void work(int x)
{
	seq.clear(), dfs(x);
	memset(sum[tot], 0, sizeof sum[tot]);
	REP(i, 0, 1 << SZ(seq))
	{
		int prod = 1;
		REP(j, 0, m) if (vis[from[j]] == tot && (((i >> id[from[j]]) ^ (i >> id[to[j]])) & 1)) 
			(prod <<= 1) %= Mod, prod = (LL)prod * (i >> id[from[j]] & 1 ? w[j] : 1 - w[j]) % Mod;
		(sum[tot][__builtin_popcount(i)] += prod) %= Mod;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	pw[0] = 1;
	REP(i, 0, n * (n - 1)) pw[i + 1] = (LL)pw[i] * ((Mod + 1) >> 1) % Mod;
	REP(i, 0, m)
	{
		scanf("%d%d%d", from + i, to + i, w + i), --from[i], --to[i], w[i] = (LL)w[i] * 796898467 % Mod;
		v[from[i]].pb(to[i]), v[to[i]].pb(from[i]);
	}
	memset(vis, -1, sizeof vis), tot = 0;
	REP(i, 0, n) if (!~vis[i]) work(i), ++tot;
	static int dp[maxn + 5][maxn + 5];
	memset(dp, 0, sizeof dp), dp[0][0] = 1;
	REP(i, 0, tot) REP(j, 0, n) if (dp[i][j]) REP(k, 0, n - j) (dp[i + 1][j + k] += (LL)dp[i][j] * sum[i][k] % Mod) %= Mod;
	ans = 0;
	REP(i, 0, n) (ans += (LL)dp[tot][i] * pw[i * (n - i)] % Mod) %= Mod;
	REP(i, 0, n * (n - 1)) ans = (LL)ans * 10000 % Mod;
	(ans += Mod) %= Mod;
	printf("%d\n", ans);
	return 0;
}

