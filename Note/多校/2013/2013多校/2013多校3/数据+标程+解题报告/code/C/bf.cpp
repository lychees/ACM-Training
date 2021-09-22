#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_N = 20;
int dp[1 << MAX_N][MAX_N];
bool can[MAX_N + 1][MAX_N + 1];
int n, mod;

void rex(int&x) {
	if (x >= mod)
		x -= mod;
}

void work() {
	cin >> n >> mod;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			can[i][j] = __gcd(i + 1, j + 1) == 1;
		}
	}
	for (int i = 0; i < n; ++i) {
		dp[1 << i][i] = 1;
	}

	for (int vis = 0; vis < (1 << n) - 1; ++vis) {
		for (int lst = 0; lst < n; ++lst)
			if (vis >> lst & 1) {
				int c = dp[vis][lst];
				if (c == 0)
					continue;
				for (int nxt = 0; nxt < n; ++nxt)
					if (~vis >> nxt & 1) {
						if (can[lst][nxt]) {
							rex(dp[vis | (1 << nxt)][nxt] += c);
						}
					}
			}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += dp[(1 << n) - 1][i];
	}
	cout << ans % mod << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		work();
	}
	return 0;
}
