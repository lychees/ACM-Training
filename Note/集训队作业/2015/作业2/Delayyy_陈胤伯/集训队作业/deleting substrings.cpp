#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 410;
const int inf = 1e9;

int n, v[N], a[N], ans[N];
int f[N][N][2], bo[N][N][2];

int dfs(int l, int r, int ty) {
	int &ret = f[l][r][ty];
	if (bo[l][r][ty]) return ret;
	bo[l][r][ty] = 1, ret = -inf;
	if (!ty) {
		for (int t = l; t <= r; ++t)
			if (a[t] >= a[l] && a[t] >= a[r]) {
				int len = min(2 * a[t] - a[l] - a[r] + 1, n);
				ret = max(ret, dfs(l, t, 1) + dfs(t, r, 1) + v[len]);
			}
		for (int i = l; i < r; ++i)
			ret = max(ret, dfs(l, i, 0) + dfs(i + 1, r, 0));
		if (l > r) ret = 0;
	} else {
		if (l == r) ret = 0;
		else if (a[l] == a[r]) ret = -inf;
		else {
			int dv = a[l] < a[r] ? 1 : -1;
			for (int i = l + 1; i <= r; ++i)
				if (a[l] + dv == a[i]) {
					ret = max(ret, dfs(l + 1, i - 1, 0) + dfs(i, r, 1));
				}
		}
	}
	return ret;
}
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", v + i);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);

	for (int i = 1; i <= n; ++i) {
		ans[i] = ans[i - 1];
		for (int j = i; j >= 1; --j)
			ans[i] = max(ans[i], ans[j - 1] + dfs(j, i, 0));
	}
	printf("%d\n", ans[n]);
}
