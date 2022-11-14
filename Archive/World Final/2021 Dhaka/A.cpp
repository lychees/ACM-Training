#include <lastweapon/io>
using namespace lastweapon;

const int N = int(1e3) + 9, WN = 10;

char A[N][N]; bool vis[N][N];
int n, m, wn;

bool inGrid(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

void dfs(int,int,char);

struct Wind {
    int wx, wy; set<PII> b;
    void in() {
        RD(wy, wx);
        Rush {
             int x, y; RD(y, x); --x; --y;
             b.insert({x, y});
        }
    }

    void gao(char t) {
        if (t == '#') {
            for (auto [x, y]: b) {
                dfs(x, y, '#');
            }
        } else {
            for (auto [x, y]: b) {
                x -= wx; y -= wy;
                dfs(x, y, '.');
            }
            REP(x, n) REP(y, m) if (A[x][y] == '#' && !CTN(b, MP(x, y)) && !inGrid(x - wx, y - wy)){
                dfs(x, y, '.');
            }
        }
    }

} W[WN];

void dfs(int x, int y, char t) {
    if (!inGrid(x, y) || vis[x][y]) return;
    vis[x][y] = 1; A[x][y] = t;

    if (t == '#') {
        REP(i, wn) if (!CTN(W[i].b, MP(x, y))) {
            dfs(x-W[i].wx, y-W[i].wy, '#');
        }
    } else {
        REP(i, wn) if (!CTN(W[i].b, MP(x+W[i].wx, y+W[i].wy))) {
            dfs(x+W[i].wx, y+W[i].wy, '.');
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(m, n); RD(wn); REP(i, wn) W[i].in();

    REP(i, n) REP(j, m) A[i][j] = '.';
    RST(vis); REP(i, wn) W[i].gao('#');
    REP(i, n) puts(A[i]); puts("");

    REP(i, n) REP(j, m) A[i][j] = '#';
    RST(vis); REP(i, wn) W[i].gao('.');
    REP(i, n) puts(A[i]);
}
