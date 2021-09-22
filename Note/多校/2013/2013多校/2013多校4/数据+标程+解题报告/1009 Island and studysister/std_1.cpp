#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
#define N 101
int sta;
int d[N][N];
int dp[1 << 17][17];
bool in[1 << 17][17];
int dp_1[1 << 16], dp_2[1 << 16];
int main() {
	int t, cas = 1;
	scanf(" %d", &t);
	while (t--) {
		int n, m;
		scanf(" %d %d", &n, &m);
//		if(cas==13) printf("%d %d\n",n,m);
		memset(d, 0x3f, sizeof(d));
		for (int i = 0; i < m; i++) {
			int x, y, s;
			scanf(" %d %d %d", &x, &y, &s);
//			if(cas==13) printf("%d %d %d\n",x,y,s);
			d[x][y] = min(d[x][y], s);
			d[y][x] = d[x][y];
		}

		queue<int> qu;
		qu.push(1);
		qu.push(0);
		memset(in, 0, sizeof(in));
		memset(dp, 0x3f, sizeof(dp));
		dp[1][0] = 0;
		in[1][0] = true;

		while (!qu.empty()) {
			int s_sta = qu.front();
			qu.pop();
			int s = qu.front() + 1;
			qu.pop();
			in[s_sta][s - 1] = false;

			for (int i = 0; i < n; i++) {
				int to = i + 1;
				int t_sta = (1 << i) | s_sta;
				if (to == 1)
					continue;
				if (dp[t_sta][to - 1] > dp[s_sta][s - 1] + d[s][to]) {
					dp[t_sta][to - 1] = dp[s_sta][s - 1] + d[s][to];
					if (!in[t_sta][to - 1]) {
						in[t_sta][to - 1] = 1;
						qu.push(t_sta);
						qu.push(to - 1);
					}
				}
			}
		}

		memset(dp_1, 0x3f, sizeof(dp_1));
		for (int i = 1; i < (1 << n); i++) {
			for (int j = 0; j < n; j++) {
				dp_1[i >> 1] = min(dp_1[i >> 1], dp[i][j]);
			}
		}

		int tar = 0, k;
		scanf(" %d", &k);
//		if(cas==13) printf("%d\n",k);
		while (k--) {
			int x;
			scanf(" %d", &x);
//			if(cas==13) printf("%d ",x);
			tar |= (1 << (x - 2));
		}
		int ans = INF;
		int tol = (1 << (n - 1)) - 1;
		memcpy(dp_2, dp_1, sizeof(dp_1));
		for (int i = 1; i < (1 << (n - 1)); i++) {
			for (int j = i; j; j = (j - 1) & i) {
				dp_2[i] = min(dp_2[i], max(dp_1[j], dp_1[i ^ j]));
			}
		}
		for (int i = tol; i; i--) {
			for (int j = i;; j = (j - 1) & i) {
				if ((i & tar) == tar) {
					ans = min(ans, max(dp_1[j], dp_2[i ^ j]));
				}
				if (j == 0)
					break;
			}
		}
		if (ans == INF)
			ans = -1;
		printf("Case %d: %d\n", cas++, ans);
	}
	return 0;
}