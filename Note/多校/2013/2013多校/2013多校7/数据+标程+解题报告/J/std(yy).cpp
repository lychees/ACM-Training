// File Name: std.cpp
// Author: YangYue
// Created Time: Tue Jul 23 13:27:35 2013
//headers 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef pair<LL, LL>PLL;
typedef pair<LL,int>PLI;

#define lch(n) ((n<<1))
#define rch(n) ((n<<1)+1)
#define lowbit(i) (i&-i)
#define sqr(x) ((x)*(x))
#define fi first
#define se second
#define MP make_pair
#define PB push_back

const int MaxN = 300005;
const double eps = 1e-7;
const double DINF = 1e100;
const int INF = 1000000006;
const LL LINF = 1000000000000000005ll;
const int MOD = (int) 1e9 + 7;

int n, m, K;
int cnt[MaxN];
LL ans[MaxN], fac[MaxN], invfac[MaxN];
LL fpow(LL a, LL t, int mod) {
	LL res = 1;
	for (; t; t >>= 1, a = a * a % mod)
		if (t & 1) res = res * a % mod;
	return res;
}
LL C(int n, int k) {
	return fac[n] * invfac[k] % MOD * invfac[n-k] % MOD;
}
int main()
{
	//freopen("in","r",stdin);

	fac[0] = invfac[0] = 1;
	for (int i = 1; i < MaxN; ++i) {
		fac[i] = fac[i-1] * i % MOD;
		invfac[i] = fpow(fac[i], MOD - 2, MOD);
	}
	//int cas = 0;
	while (scanf("%d%d%d",&n,&m,&K) != EOF) {
		//cerr << ++cas << endl;
		assert(n >= 1 && n <= 300000 && m >= 1 && m <= 300000 && K >= 1 && K <= n);
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i) {
			int x; scanf("%d", &x);
			++cnt[x];
			//a[i] = x;
		}

		for (int d = m; d; --d) {
			int a = 0;
			LL sum = 0;
			for (int i = d; i <= m; i += d) {
				a += cnt[i];
				if (i > d) sum = (sum + ans[i]) % MOD;
			}
			int x = n - a;
			if (x > K) {
				ans[d] = 0;
				continue;
			}
			LL res = fpow(m / d, x, MOD) * fpow(m / d - 1, K - x, MOD) % MOD;
			LL comb = C(n - x, K - x);
			ans[d] = (res * comb % MOD + MOD - sum) % MOD;
		}
		for (int i = 1; i < m; ++i) printf("%I64d ", ans[i]);
		printf("%I64d\n", ans[m]);
	}
	
	return 0;
}

// hehe ~


