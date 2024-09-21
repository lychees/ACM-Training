#include <lastweapon/io>
#include <lastweapon/geometry>

using namespace lastweapon;
using namespace CG;

const int N = int(1e3) + 9;
Po p[N]; int n; bool dp[N], vis[N];

int dfs(int u, DB x) {
    int z = 1; vis[u] = 1;
    REP(v, 2*n) if (!vis[v] && dist(p[u], p[v]) < x) z += dfs(v, x);
    return z;
}

bool ok(DB x) {
    RST(vis, dp); dp[0] = 1; REP(u, 2*n) if (!vis[u]) {
        int s = dfs(u, x); if (s > n) return 0;
        DWN_1(i, n, s) dp[i] |= dp[i-s];
        if (dp[n]) return 1;
    }
    return 0;
}

VI cpn[N];
int dfs2(int u, DB x, VI& c) {
    int z = 1; vis[u] = 1; c.PB(u);
    REP(v, 2*n) if (!vis[v] && dist(p[u], p[v]) < x) z += dfs2(v, x, c);
    return z;
}

void gao(DB x) {
    printf("%.9f\n", x);
    RST(vis, dp); dp[0] = 1; REP(u, 2*n) if (!vis[u]) {
        VI c; int s = dfs2(u, x, c);
        DWN_1(i, n, s) if (!dp[i] && dp[i-s]) {
            dp[i] = 1; cpn[i] = c;
        }

        if (dp[n]) {
            for (int x=n;x;x-=SZ(cpn[x])) {
                for (auto u: cpn[x]) printf("%d\n", u+1);
            }
            return;
        }
    }

}

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    RD(n); REP(i, 2*n) p[i].in();
    DB l = 0, r = 3e9; DO(233) {
        DB m = (l + r) / 2;
        if (ok(m)) l = m; else r = m;
    }
    gao(l);
}
