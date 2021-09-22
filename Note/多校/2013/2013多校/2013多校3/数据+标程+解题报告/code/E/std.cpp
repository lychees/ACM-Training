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
int fact[MAX_K];
int S[MAX_N][MAX_K];

void prepare() {
	int n = 50000, k = 500;
	S[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			S[i][j] = S[i - 1][j - 1] + S[i - 1][j] * j;
			S[i][j] %= MOD;
		}
	}
	fact[0] = 1;
	for (int j = 1; j <= k; ++j) {
		fact[j] = fact[j - 1] * j % MOD;
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			S[i][j] = S[i][j] * fact[j] % MOD;
		}
	}
}

inline void rex(int&x) {
	if (x >= MOD)
		x -= MOD;
}

struct Data {
	int a[MAX_K];
	void clear() {
		memset(a, 0, sizeof a);
	}
	Data() {
		clear();
	}
	inline int&operator[](int i) {
		return a[i];
	}
	Data&operator+=(Data&o) {
		for (int i = 0; i <= k; ++i) {
			a[i] += o[i];
			rex(a[i]);
		}
		return *this;
	}
	Data&operator-=(Data&o) {
		for (int i = 0; i <= k; ++i) {
			a[i] += MOD - o[i];
			rex(a[i]);
		}
		return *this;
	}
	Data&operator=(Data&o) {
		memcpy(a, o.a, sizeof a);
	}
};

void update(Data&a) {
	for (int i = k; i >= 1; --i) {
		a[i] += a[i - 1];
		rex(a[i]);
	}
}

Data down[MAX_N], up[MAX_N];
//down
void dfs(int u, int par) {
	down[u].clear();
	down[u][0] = 1;
	for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e) {
		if (*e != par) {
			dfs(*e, u);
			static Data t;
			t = down[*e];
			update(t);
			down[u] += t;
		}
	}
}

void dfs2(int u, int par) {
	up[u].clear();
	if (par != -1) {
		static Data t, x;
		t = up[par], x = down[u];
		t += down[par];
		update(x);
		t -= x;
		update(t);
		up[u] = t;
	}

	for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e) {
		if (*e != par) {
			dfs2(*e, u);
		}
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

	dfs(0, -1);
	dfs2(0, -1);

	for (int i = 0; i < n; ++i) {
		static Data ret;
		ret = down[i];
		ret += up[i];
		int ans = 0;
		for (int j = 0; j <= k; ++j) {
			ans += ret[j] * S[k][j];
			ans %= MOD;
		}
		cout << ans << endl;
	}
}

int main() {
	prepare();
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		work();
	}
	return 0;
}
