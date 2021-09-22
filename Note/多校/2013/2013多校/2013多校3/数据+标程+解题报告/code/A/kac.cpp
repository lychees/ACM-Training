#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int MAXN = 1000001, MAXM = 2000001;
struct Tflow{
	int tot, e[MAXN], v[MAXM], c[MAXM], next[MAXM], s, t;
	int d[MAXN], q[MAXN], l, r;
	void clear() { tot = 1; for (int i = 1; i <= t; i++) e[i] = 0; }
	void add(int a, int b, int w, bool flag = false)
	{
		if (flag) swap(a, b);
#ifdef __woshi5dmdeclj
		//cerr << a << " " << b << " " << w << endl;
#endif
		++tot; next[tot] = e[a]; e[a] = tot; v[tot] = b; c[tot] = w;
		++tot; next[tot] = e[b]; e[b] = tot; v[tot] = a; c[tot] = 0;
	}
	bool relable()
	{
		for (int i = 1; i <= t; i++) d[i] = -1; d[s] = 0; l = r = 1; q[1] = s;
		while(l <= r){
			int x = q[l++]; 
			for (int i = e[x]; i; i = next[i]) if (c[i] > 0 && d[v[i]] == -1){
				d[v[i]] = d[x] + 1; q[++r] = v[i];
			}
		}
		return d[t] != -1;
	}
	int find(int x, int f = 0x3f3f3f3f)
	{
		if (x == t) return f;
		int augc = f;
		for (int i = e[x]; i; i = next[i]) if (d[v[i]] == d[x] + 1 && c[i] > 0){
			int t = find(v[i], min(f, c[i]));
			c[i] -= t; c[i ^ 1] += t; f -= t;
			if (f == 0) break;
		}
		if (f != 0) d[x] = -1;
		return augc - f;
	}
	int run()
	{
		int t, ret = 0;
		while(relable()) while(t = find(s)) ret += t;
		return ret;
	}
} flow;
int log(int x) { return 31 - __builtin_clz(x); }
int n, m, Q, a[1001][1001], b[1001][1001];
int V[1001][1001], v[2][101][101][21][21];
const int INF = 2000000000;
int main()
{
#ifdef __woshi5dmdeclj
	freopen("temp.in", "r", stdin);
	freopen("temp.out", "w", stdout);
#endif
	
int T; scanf("%d", &T);
while(T--){
	int ans = 0, tot = 0;
	scanf("%d%d%d", &n, &m, &Q);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]), ans += a[i][j];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &b[i][j]), ans += b[i][j];
	flow.clear();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++){
			V[i][j] = ++tot;
			v[0][i][j][0][0] = tot;
			v[1][i][j][0][0] = tot;
		}
	for (int i = 0; (1 << i) <= n; i++)
		for (int j = 0; (1 << j) <= m; j++) if (i + j)
			for (int x = 1; x + (1 << i) - 1 <= n; x++)
				for (int y = 1; y + (1 << j) - 1 <= m; y++){
					v[0][x][y][i][j] = ++tot;
					v[1][x][y][i][j] = ++tot;
				}
	int s = tot + Q + 1, t = tot + Q + 2;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++){
		flow.add(s, V[i][j], a[i][j]);
		flow.add(V[i][j], t, b[i][j]);
	}
	for (int i = 0; (1 << i) <= n; i++)
		for (int j = 0; (1 << j) <= m; j++) if (i + j)
			for (int x = 1; x + (1 << i) - 1 <= n; x++)
				for (int y = 1; y + (1 << j) - 1 <= m; y++)
					for (int c = 0; c <= 1; c++){
						if (i && j) flow.add(v[c][x][y][i][j], v[c][x + (1 << i - 1)][y + (1 << j - 1)][max(0, i - 1)][max(0, j - 1)], INF, c);
						if (j) flow.add(v[c][x][y][i][j], v[c][x][y + (1 << j - 1)][max(0, i - 1)][max(0, j - 1)], INF, c);
						if (i) flow.add(v[c][x][y][i][j], v[c][x + (1 << i - 1)][y][max(0, i - 1)][max(0, j - 1)], INF, c);
						flow.add(v[c][x][y][i][j], v[c][x][y][max(0, i - 1)][max(0, j - 1)], INF, c);
					}
	
	while(Q--){
		int x1, y1, x2, y2, c, val;
		scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &c, &val);
		c ^= 1;
		++tot;  ans += val;
		if (c == 0) flow.add(s, tot, val);
		else flow.add(tot, t, val);
		int l1 = log(x2 - x1 + 1), l2 = log(y2 - y1 + 1);
		flow.add(tot, v[c][x1][y1][l1][l2], INF, c);
		flow.add(tot, v[c][x2 - (1 << l1) + 1][y1][l1][l2], INF, c);
		flow.add(tot, v[c][x1][y2 - (1 << l2) + 1][l1][l2], INF, c);
		flow.add(tot, v[c][x2 - (1 << l1) + 1][y2 - (1 << l2) + 1][l1][l2], INF, c);
	}
	flow.s = s; flow.t = t;
	cout << ans - flow.run() << endl;
}
}
