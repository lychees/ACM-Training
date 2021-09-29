#include <cstdio>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#define pii pair<int, int>
#define NE(x, _y, an) es[++nes].y=_y, es[nes].ang=an, es[nes].h=s[x], s[x]=nes
using namespace std;

const int N = 3005, M = 20000, inf = 1<<28;
const double pi = 3.1415926535897932384626433832795;
map<string, int> Mp;
struct pt{int x, y, h;} a[N];
struct edge{int y, h; double ang;} es[M];
int n, m, nes, Ln, s[M], l[M], d[N], L[M];
bool v[N], b[N];
inline bool cmp(int a, int b) {return es[a].ang < es[b].ang;}
void init() {
	Mp.clear(); nes = 1;
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; ++i) b[i]=s[i]=0;
	char cx[5], cy[5];
	int x, y, S=1;
	for (int i=1; i<=n; ++i) {
		scanf("%s%d%d%d", cx, &a[i].x, &a[i].y, &a[i].h);
		Mp[string(cx)] = i;
		if (a[i].x < a[S].x) S = i;
	}
	double an;
	for (int i=1; i<=m; ++i) {
		scanf("%s%s", cx, cy);
		x = Mp[string(cx)], y = Mp[string(cy)];
		an = atan2(a[y].y-a[x].y, a[y].x-a[x].x);
		NE(x, y, an); NE(y, x, an<0?an+pi:an-pi);
	}
	int ln;
    for (int i=1; i<=n; ++i) {
        ln = 0;
        for (int w=s[i]; w; w=es[w].h) l[++ln] = w;
        sort(l+1, l+ln+1, cmp);
        for (int j=1; j<ln; ++j) es[l[j]].h = l[j+1];
        es[l[ln]].h = l[1];
        s[i] = l[1];
    }
    b[S] = true;
    for (int w=s[S]; es[w^1].h!=s[S]; w=es[w^1].h)
		b[es[w].y] = true;
    for (int i=1; i<=n; ++i) {
    	x = es[s[i]].h;
    	es[s[i]].h = 0;
    	s[i] = x;
	}
}
void dij() {
	priority_queue< pii, vector< pii >, greater< pii > > H;
	for (int i=1; i<=n; ++i) d[i] = inf, v[i] = false;
	for (int i=1; i<=n; ++i) if (b[i]) d[i] = 0, H.push(make_pair(0, i));
	int dis, x;
	for (int i=1; i<n; ++i) {
		while (v[H.top().second]) H.pop();
		x = H.top().second, dis = max(H.top().first, a[x].h);
		v[x] = true; H.pop();
		for (int w=s[x]; w; w=es[w].h)
			if (dis < d[es[w].y]) {
				d[es[w].y] = dis;
				H.push(make_pair(dis, es[w].y));
			}
	}
}
void bfs(int x, int lim) {
	int ls=1, le=1, to; l[1]=x, v[x]=true;
	for (; ls<=le; ++ls)
		for (int w=s[l[ls]]; w; w=es[w].h) {
			to = es[w].y;
			if (!v[to] && a[to].h < lim)
				v[to] = true, l[++le] = to;
		}
}
void run() {
	init();
	dij();
	Ln = 0;
	for (int i=1; i<=n; ++i) v[i] = false;
	for (int i=1; i<=n; ++i) if (!v[i] && d[i] > a[i].h) {
		bfs(i, d[i]);
		L[++Ln] = d[i];
	}
	sort(L+1, L+Ln+1);
	for (int i=1; i<=Ln; ++i) printf("%d\n", L[i]);
	if (!Ln) puts("0");
}
int main() {
	run();
	return 0;
}
