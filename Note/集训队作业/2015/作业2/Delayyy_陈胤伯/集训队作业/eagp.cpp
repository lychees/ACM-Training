#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

typedef pair<int,int> cp;

const int N = 200020;
const int mod = 100711433;

int q, pe[N];
int n, dep[N], pep[N];
int be[N], ed[N], times;

struct edge {
	int to, nx, dl;
} ee[N + N];
int eq[N], en = 1;

int fa[N][21], fw[N][21];

int tr[N], cc[N], ans[N];
vector<cp> vec[N];

cp ups[N], dws[N];
int upx[N], upn;
int dwx[N], dwn, dwb[N];

int fpm(int a, int b) {
	int w = 1;
	for (a %= mod; b; b >>= 1, a = (long long)a * a % mod)
		if (b & 1) w = (long long)w * a % mod;
	return w;
}
int inv(int x) {
	return fpm(x, mod - 2);
}
void dfs(int d, int p) {
	be[d] = ++times;
	for (int j = eq[d], k; k = ee[j].to, j; j = ee[j].nx)
		if (k != p) {
			fa[k][0] = d;
			dep[k] = dep[d] + 1;
			dfs(k, d);
		} else ee[j].dl = 1;
	ed[d] = times;
}
int lca(int u, int v, int& lcc) {
	int flag = 0;
	if (dep[u] < dep[v]) swap(u, v), flag = 1;
	int _u = u;
	int dt = dep[u] - dep[v], _dt = dt;
	for (int j = 0; j < 20; j ++)
		if (dt >> j & 1) u = fa[u][j];
	if (u == v) {
		int o = _u;
		if (!_dt) return u;
		dt = _dt - 1;
		for (int j = 0; j < 20; j ++)
			if (dt >> j & 1) o = fa[o][j];
		lcc = o;
		return u;
	}
	for (int j = 19; j >= 0; j --)
		if (fa[u][j] != fa[v][j]) u = fa[u][j], v = fa[v][j];
	lcc = !flag? u: v;
	return fa[u][0];
}
int get(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int dt = dep[u] - dep[v], ret = 0;
	for (int j = 0; j < 20; j ++)
		if (dt >> j & 1) ret = (ret + fw[u][j]) % mod, u = fa[u][j];
	if (u == v) return ret;
	for (int j = 19; j >= 0; j --)
		if (fa[u][j] != fa[v][j]) {
			ret = (ret + fw[u][j]) % mod, u = fa[u][j];
			ret = (ret + fw[v][j]) % mod, v = fa[v][j];
		}
	ret = (ret + fw[u][0]) % mod;
	ret = (ret + fw[v][0]) % mod;
	return ret;
}
inline void inc(int& a, int b) {
	a = (a + b) % mod;
}
void clean() {
	for (int i = 1; i <= n; i ++) vec[i].clear();
	memset(tr, 0, sizeof(tr));
}
void add(int w, int v) {
	for (int j = w; j <= n; j += j & -j) inc(tr[j], v);
}
int ask(int w) {
	int ret = 0;
	for (int j = w; j; j -= j & -j) inc(ret, tr[j]);
	return ret;
}
void work(int d) {
	int sz = vec[d].size();
	for (int l = 0; l < sz; l ++) add(vec[d][l].first, vec[d][l].second);
	int temp = (ask(ed[d]) - ask(be[d] - 1) + mod) % mod;
	inc(ans[d], (long long)temp * cc[d] % mod);
	for (int j = eq[d]; j; j = ee[j].nx)
		if (!ee[j].dl) work(ee[j].to);
}
void calc() {
	work(1);
}
void deal_up() {
	clean();
	for (int i = 1; i <= upn; i ++) {
		int D = pep[ups[i].first] - 1, x = upx[i];
		long long ww = inv(pe[D]);
		vec[ups[i].second].push_back(make_pair(be[ups[i].first], ww * x % mod));
	}
	for (int i = 1; i <= n; i ++) cc[i] = (long long)pep[i] * pe[pep[i]] % mod;
	calc();

	clean();
	for (int i = 1; i <= upn; i ++) {
		int D = pep[ups[i].first] - 1, x = upx[i];
		long long ww = (long long)D * inv(pe[D]) % mod; ww = mod - ww;
		vec[ups[i].second].push_back(make_pair(be[ups[i].first], ww * x % mod));
	}
	for (int i = 1; i <= n; i ++) cc[i] = pe[pep[i]];
	calc();
}
void deal_dw() {
	clean();
	for (int i = 1; i <= dwn; i ++) {
		int D = dep[dws[i].first] - dwb[i], x = dwx[i];
		long long ww;
		if (D >= 0) ww = inv(pe[D]);
		else ww = pe[-D];
		vec[dws[i].first].push_back(make_pair(be[dws[i].second], ww * x % mod));
	}
	for (int i = 1; i <= n; i ++) cc[i] = (long long)dep[i] * pe[dep[i]] % mod;
	calc();

	clean();
	for (int i = 1; i <= dwn; i ++) {
		int D = dep[dws[i].first] - dwb[i], x = dwx[i];
		long long ww;
		if (D >= 0) ww = (long long)D * inv(pe[D]) % mod;
		else ww = (long long)(mod + D) * pe[-D] % mod;
		ww = mod - ww;
		vec[dws[i].first].push_back(make_pair(be[dws[i].second], ww * x % mod));
	}
	for (int i = 1; i <= n; i ++) cc[i] = pe[dep[i]];
	calc();
}
int main() {
	scanf("%d %d", &n, &q);
	for (int i = 1, u, v; i < n; i ++) {
		scanf("%d %d", &u, &v);
		ee[++en] = (edge){v, eq[u]}, eq[u] = en;
		ee[++en] = (edge){u, eq[v]}, eq[v] = en;
	}

	dep[1] = 1;
	dfs(1, 0);
	for (int i = 1; i <= n; i ++) pep[i] = n + 1 - dep[i];
	for (int j = 1; j < 20; j ++)
		for (int i = 1; i <= n; i ++) fa[i][j] = fa[fa[i][j - 1]][j - 1];

	for (int i = 0; i <= n; i ++) pe[i] = !i? 1: (long long)pe[i - 1] * q % mod;

	int cmds1, cmds2, x, u, v;
	scanf("%d %d", &cmds1, &cmds2);
	while (cmds1 --) {
		scanf("%d %d %d", &x, &u, &v);
		int lc2, lc = lca(u, v, lc2), ori;
		if (lc != u) ups[++upn] = make_pair(u, lc2), upx[upn] = x;
		ori = dep[u] - dep[lc] + 1;
		dws[++dwn] = make_pair(lc, v), dwx[dwn] = x, dwb[dwn] = ori;
	}

	deal_up();
	deal_dw();

	for (int i = 1; i <= n; i ++) fw[i][0] = ans[fa[i][0]];
	for (int j = 1; j < 20; j ++)
		for (int i = 1; i <= n; i ++)
			fw[i][j] = (fw[i][j - 1] + fw[fa[i][j - 1]][j - 1]) % mod;

	while (cmds2 --) {
		int u, v;
		scanf("%d %d", &u, &v);
		int lc2, lc = lca(u, v, lc2);

		int ret = get(u, v);
		ret = (ret + ans[u]) % mod;
		ret = (ret + ans[v]) % mod;
		ret = (ret - ans[lc] + mod) % mod;

		printf("%d\n", ret);
	}
}
