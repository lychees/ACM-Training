#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_N = 50000 + 10;
const int MAX_K = 500 + 10;
const int MOD = 10007;
//5w,500

vector<int> E[MAX_N];
int n, k;

//n^k = Sk_i*i!*C_n,i
//down
int pw[MAX_N];

int ans;

void dfs(int u, int par, int d) {
	ans += pw[d];
	if (ans >= MOD)
		ans -= MOD;

	for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e) {
		if (*e != par)
			dfs(*e, u, d + 1);
	}
}

void work() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		E[i].clear();
	}
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a, --b;
		E[a].push_back(b), E[b].push_back(a);
	}

	for (int i = 0; i <= n; ++i) {
		pw[i] = 1;
		for (int j = 0; j < k; ++j) {
			pw[i] = 1LL * pw[i] * i % MOD;
		}
	}

	for (int i = 0; i < n; ++i) {
		ans = 0;
		dfs(i, -1, 0);
		cout << ans << endl;
	}
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		work();
	}
	return 0;
}
