#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

typedef long long int64;
const int MAX_N = 16, INF = ~0U >> 2;
int n;
int dp[1 << MAX_N][MAX_N][MAX_N]; //rest,i,j

char s[MAX_N + 1];
void work() {
	scanf("%s", s);
	n = strlen(s);

	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			dp[0][i][j] = 0;
		}
	}

	for (int rest = 1; rest < (1 << n); ++rest) {
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i; j < n; ++j) {
				//rest,i,j
				int&ret = dp[rest][i][j] = INF;
				if (i < j)
					ret = min(dp[rest][i + 1][j], dp[rest][i][j - 1]);
				if (s[i] == s[j] && (rest >> i & 1) && (rest >> j & 1)) {
					int nrest = rest & (~(1 << i)) & (~(1 << j));
					if (nrest == 0)
						ret = min(ret, dp[nrest][i][j] + 1);
					else
						ret = min(ret, dp[nrest][i][j]);
				}
			}
		}
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i; j < n; ++j) {
				dp[rest][i][j] = min(dp[rest][i][j], dp[rest][0][n - 1] + 1);
			}
		}
	}

	cout << dp[(1 << n) - 1][0][n - 1] << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		work();
	}
}
