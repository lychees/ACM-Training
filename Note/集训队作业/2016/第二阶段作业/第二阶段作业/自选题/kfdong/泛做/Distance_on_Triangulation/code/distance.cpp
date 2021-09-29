#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define pb push_back
#define mkp make_pair
#define fir first
#define sec second
using namespace std;
 
const int MaxN = 100010, MaxM = MaxN << 2;
class Graph {
public:
    int r[MaxM], l[MaxM], point[MaxM], tot;
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            r[i] = l[i] = i;
        }
        tot = n;
    }
    void add_edge(int x, int y) {
        point[++tot] = y;
        r[tot] = x;
        l[tot] = l[x];
        l[r[tot]] = tot;
        r[l[tot]] = tot;
    }
    void remove_edge(int t) {
        r[l[t]] = r[t];
        l[r[t]] = l[t];
    }
    void restore_edge(int t) {
        l[r[t]] = t;
        r[l[t]] = t;
    }
}   G;
 
int ans[MaxN];
int qx[MaxN], qy[MaxN], n, m;
 
void input() {
    scanf("%d", &n);
    G.init(n);
    for (int i = 2; i <= n; ++i) {
        G.add_edge(i, i - 1);
        G.add_edge(i - 1, i);
    }
    G.add_edge(1, n);
    G.add_edge(n, 1);
    for (int i = 1; i <= n - 3; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G.add_edge(u, v);
        G.add_edge(v, u);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) 
        scanf("%d%d", qx + i, qy + i);
}
 
int p[MaxN], size[MaxN], dist[4][MaxN];
bool mark[MaxN];
int side[MaxN];
 
void bfs(int s, int *dist) {
    static int q[MaxN];
    static bool vis[MaxN];
    int l = 0, r = 0;
    q[++r] = s;
    vis[s] = 1;
    dist[s] = 0;
    while (l != r) {
        int u = q[++l];
        for (int i = G.r[u]; i != u; i = G.r[i])
            if (mark[G.point[i]] && !vis[G.point[i]]) {
                vis[G.point[i]] = 1;
                dist[G.point[i]] = dist[u] + 1;
                q[++r] = G.point[i];
            }
    }
    for (int i = 1; i <= r; ++i) vis[q[i]] = 0;
}
 
void solve(vector <int> &p, vector <int> &q, int posl, int posr) {
    int ptot = p.size(), qtot = q.size();
    for (int i = 0; i < ptot; ++i)
        if (!side[p[i]]) mark[p[i]] = 1;
    bfs(posl, dist[0]);
    bfs(posr, dist[1]);
    for (int i = 0; i < ptot; ++i)
        if (!side[p[i]]) mark[p[i]] = 0;
    for (int i = 0; i < ptot; ++i)
        if (side[p[i]]) mark[p[i]] = 1;
    bfs(posl, dist[2]);
    bfs(posr, dist[3]);
    for (int i = 0; i < ptot; ++i)
        if (side[p[i]]) mark[p[i]] = 0;
    for (int i = 0; i < qtot; ++i) {
        int u = qx[q[i]], v = qy[q[i]];
        if (side[u] ^ side[v]) {
            ans[q[i]] = min(dist[side[u] * 2][u] + dist[side[v] * 2][v], 
                            dist[side[u] * 2 + 1][u] + dist[side[v] * 2 + 1][v]);
        }
    }
}
 
int cnt = 0;
 
void divide(vector <int> &p, vector <int> &q) {
    int ptot = p.size(), qtot = q.size();
    if (ptot <= 3) {
        for (int i = 0; i < qtot; ++i) ans[q[i]] = 1;
        return;
    }
    //find the divide edge
    for (int i = 0; i < ptot; ++i) {
        mark[p[i]] = 1;
        size[p[i]] = i;
    }
    int sz = ptot, mx = 0, posl = 0, posr = 0;
    for (int i = 0; i < ptot; ++i) 
        for (int j = G.r[p[i]]; j != p[i]; j = G.r[j]) 
            if (mark[G.point[j]] && (size[G.point[j]] > size[p[i]])) {
                int tmp = size[G.point[j]] - size[p[i]];
                int now = min(tmp, sz - tmp);
                if (now > mx) {
                    mx = now;
                    posl = p[i];
                    posr = G.point[j];
                }
            }
    for (int i = 0; i < ptot; ++i) mark[p[i]] = 0;
    for (int i = 0; i < ptot; ++i)
        if ((size[posl] <= size[p[i]]) && (size[p[i]] <= size[posr])) side[p[i]] = 0;
        else side[p[i]] = 1;
 
    solve(p, q, posl, posr);
 
    //divide
    vector <int> ql, qr;
    for (int i = 0; i < qtot; ++i) {
        if ((side[qx[q[i]]] == 0) && (side[qy[q[i]]] == 0)) ql.pb(q[i]);
        if ((side[qx[q[i]]] == 1) && (side[qy[q[i]]] == 1)) qr.pb(q[i]);
    }
    vector <int> pl, pr;
    for (int i = 0; i < ptot; ++i) {
        if ((size[posl] <= size[p[i]]) && (size[p[i]] <= size[posr])) pl.pb(p[i]);
        if ((size[p[i]] <= size[posl]) || (size[posr] <= size[p[i]])) pr.pb(p[i]);
    }
 
    vector <int> edge;
    //left
    for (uint i = 0; i < pl.size(); ++i) mark[pl[i]] = 1;
    for (uint i = 0; i < pl.size(); ++i)
        for (int j = G.r[pl[i]]; j != pl[i]; j = G.r[j])
            if (!mark[G.point[j]]) {
                edge.pb(j);
                G.remove_edge(j);
            }
    for (uint i = 0; i < pl.size(); ++i) mark[pl[i]] = 0;
    divide(pl, ql);
    for (int j = edge.size() - 1; j >= 0; --j) G.restore_edge(edge[j]);
    edge.clear();
    //right
    for (uint i = 0; i < pr.size(); ++i) mark[pr[i]] = 1;
    for (uint i = 0; i < pr.size(); ++i)
        for (int j = G.r[pr[i]]; j != pr[i]; j = G.r[j])
            if (!mark[G.point[j]]) {
                edge.pb(j);
                G.remove_edge(j);
            }
    for (uint i = 0; i < pr.size(); ++i) mark[pr[i]] = 0;
    divide(pr, qr);
    for (int j = edge.size() - 1; j >= 0; --j) G.restore_edge(edge[j]);
    edge.clear();
}
 
int main() {
    input();
    vector <int> p, q;
    for (int i = 1; i <= n; ++i) p.pb(i);
    for (int i = 1; i <= m; ++i) q.pb(i);
    divide(p, q);
    for (int i = 1; i <= m; ++i) 
        if (qx[i] == qy[i]) ans[i] = 0;
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}
