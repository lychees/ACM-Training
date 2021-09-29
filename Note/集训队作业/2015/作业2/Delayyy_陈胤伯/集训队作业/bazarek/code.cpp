#include <cstdio>
#include <algorithm>
  
#define foredge(u) for (int j = eq[u], v; v = ee[j].to, j; j = ee[j].nx)
#define gs(c) ((c < '0' || c > '9') && c != '-')
#define gc(c) c = getchar()
#define gf(c) if (c == '-') f = -f, gc(c)
#define read(x) x = ({ int w = 0, f = 1; char gc(c); while (gs(c)) gc(c); gf(c); while (!gs(c)) w = w * 10 + c - '0', gc(c); w * f; })
  
using namespace std;
   
const int N = 1010;
  
int n, c[N], f[N], good[N];
   
struct edge {
	int to, nx;
} ee[N * 2];
int eq[N], en = 1;
   
int ar[N], ap;
   
void link(int u, int v) {
	ee[++en] = (edge) {v, eq[u]}, eq[u] = en;
}
int solve(int u) {
	if (c[u] <= 0) {
		if (c[u] == -1) return f[u] = 1;
		if (c[u] == -2) return f[u] = 2;
		return f[u] = 3;
	}
	int cnt[4] = {0};
	foredge(u) {
		cnt[solve(v)]++;
	}
	if (cnt[1] > cnt[2] + cnt[3] % 2) return f[u] = 1;
	if (cnt[2] > cnt[1] + cnt[3] % 2) return f[u] = 2;
	return f[u] = 3;
}
void putall(int u) {
	if (!eq[u]) {
		if (!c[u]) good[u] = 1;
		return;
	}
	foredge(u) putall(v);
}
void workans(int u, int ty) {
	if (ty == 2) {
		if (f[u] == 2) {
			putall(u);
		}
		if (f[u] == 3) {
			if (!eq[u]) {
				good[u] = 1;
				return;
			}
			foredge(u) {
				if (f[v] == 3)
					workans(v, 2);
				if (f[v] == 1)
					workans(v, 3);
			}
		}
	}
	if (ty == 3) {
		int cnt[4] = {0};
		foredge(u) ++cnt[f[v]];
		if (cnt[3] % 2 == 0 && cnt[1] == cnt[2] + 1) {
			foredge(u) {
				if (f[v] == 3) workans(v, 2);
				if (f[v] == 1) workans(v, 3);
			}
		}
	}
}
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(c[i]);
		if (c[i] > 0) {
			for (int t = 1, j; t <= c[i]; ++t) {
				read(j);
				link(i, j);
			}
		}
	}
	if (solve(1) == 1) {
		printf("NIE\n");
	} else {
		printf("TAK ");
		workans(1, 2);
		for (int i = 1; i <= n; ++i)
			if (good[i]) ar[++ap] = i;
		printf("%d\n", ap);
		for (int i = 1; i <= ap; ++i)
			printf("%d%c", ar[i], i < ap? ' ': '\n');
	}
}
