#include <cstdio>
#include <cstring>
#include <algorithm>
#define PI pair<int, int>
#define MP make_pair
#define x first
#define y second
const int maxn = 100100;
using namespace std;
int N, m;
inline bool in(int x, int y) {
	return x >= -m && x <= m && y >= -m && y <= m;
}
PI p[maxn];
PI a[maxn], b[maxn], c[maxn], d[maxn];
int ea, eb, ec, ed;
bool chk() {
	int i, j, k;
	ea = eb = ec = ed = -1;
	for(i = 0; i < N; ++i) {
		if(in(p[i].x+m, p[i].y-m)) {
			while(ea >= 0 && a[ea].y >= p[i].y-m) {
				ea--;
			}
			if(ea >= 0 && a[ea].x==p[i].x+m) {
				continue;
			}
			a[++ea] = MP(p[i].x+m, p[i].y-m);
		}
		if(in(p[i].x+m, p[i].y+m)) {
			while(eb >= 0 && b[eb].y <= p[i].y+m) {
				eb--;
			}
			if(eb >= 0 && b[eb].x==p[i].x+m) {
				continue;
			}
			b[++eb] = MP(p[i].x+m, p[i].y+m);
		}
	}
	for(i = N-1; i >= 0; --i) {
		if(in(p[i].x-m, p[i].y-m)) {
			while(ec >= 0 && c[ec].y >= p[i].y-m) {
				ec--;
			}
			if(ec >= 0 && c[ec].x==p[i].x-m) {
				continue;
			}
			c[++ec] = MP(p[i].x-m, p[i].y-m);
		}
		if(in(p[i].x-m, p[i].y+m)) {
			while(ed >= 0 && d[ed].y <= p[i].y+m) {
				ed--;
			}
			if(ed >= 0 && d[ed].x==p[i].x-m) {
				continue;
			}
			d[++ed] = MP(p[i].x-m, p[i].y+m);
		}
	}
	int na = 0, nb = 0, nc = ec+1, nd = ed+1;
	int v1, v2;
	for(i = -m; i <= m; ++i) {
		if(nc > 0 && c[nc-1].x == i) {
			nc--;
		}
		if(nd > 0 && d[nd-1].x == i) {
			nd--;
		}
		v1 = m+1, v2 = -m-1;
		if(na <= ea) {
			v1 = min(v1, a[na].y);
		}
		if(nb <= eb) {
			v2 = max(v2, b[nb].y);
		}
		if(nc <= ec) {
			v1 = min(v1, c[nc].y);
		}
		if(nd <= ed) {
			v2 = max(v2, d[nd].y);
		}
		if(v1-1 > v2) {
			return 0;
		}
		if(na <= ea && a[na].x == i) {
			na++;
		}
		if(nb <= eb && b[nb].x == i) {
			nb++;
		}
	}
	return 1;
}
int main() {
    freopen("mummy.in","r",stdin);
    freopen("mummy.out","w",stdout);
	int i, j, k, cases = 1;
	int ll, rr;
	while(scanf("%d", &N), N+1) {
		for(i = 0; i < N; ++i) {
			scanf("%d %d", &p[i].x, &p[i].y);
		}
		sort(p, p+N);
		ll = -1, rr = 1000000;
		while(rr-ll > 1) {
			m = (ll+rr)/2;
			if(chk()) {
				rr = m;
			} else {
				ll = m;
			}
		}
		m = rr;
		printf("Case %d: ", cases++);
		if(chk()) {
			printf("%d\n", rr);
		} else {
			puts("never");
		}
	}
	return 0;
}
