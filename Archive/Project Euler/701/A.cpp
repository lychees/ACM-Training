#include <lastweapon/bitwise>
using namespace lastweapon;

const int N = 7;

int grid[N]; bool vis[N][N];
int n; LL z;

int dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || vis[x][y]) {
        return 0;
    }
    vis[x][y] = 1;
    if (!_1(grid[x], y)) return 0;
    int z = 1;
    REP(d, 4) {
        int xx = x + dx[d], yy = y + dy[d];
        z += dfs(xx, yy);
    }
    return z;
}

void gen(int k = 0) {
    if (k == n) {
        REP(i, n) RST(vis[i]);
        int zz = 0;
        REP(i, n) REP(j, n) if (!vis[i][j]) {
            checkMax(zz, dfs(i, j));
        }
        z += zz;
    } else {
        REP(i, _1(n)) {
            grid[k] = i;
            gen(k+1);
        }
    }
}

int main() {
    //cin >> n;
    REP_1(i, 5) {
        z = 0; n = i; gen();
        printf("%.8lf", (DB)z/_1(n*n));
    }
}
