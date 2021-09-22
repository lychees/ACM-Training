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
int dp[1 << MAX_N];
bool can[1 << MAX_N];

char s[MAX_N + 1];
void work() {
	scanf("%s", s);
	n = strlen(s);

	for (int set = 0; set < (1 << n); ++set) {
		char cur[MAX_N];
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (set >> i & 1)
				cur[cnt++] = s[i];
		}
		bool check = true;
		for (int l = 0, r = cnt - 1; l < r; ++l, --r) {
			if (cur[l] != cur[r]) {
				check = false;
				break;
			}
		}
		can[set] = check;
	}

	dp[0] = 0;
	for (int set = 1; set < (1 << n); ++set) {
		dp[set] = INF;
		for (int subset = set; subset > 0; (--subset) &= set)
			if (can[subset]) {
				dp[set] = min(dp[set], dp[set - subset] + 1);
			}
	}

	cout << dp[(1 << n) - 1] << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		work();
	}
}
