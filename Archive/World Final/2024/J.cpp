#include <lastweapon/io>
#include <lastweapon/segtree>
using namespace lastweapon;

const int N = int(2e5) + 9;
const int M = 5;

using rec = array<array<LL, M>, M>;
// left
// right
// left then right
// right then left

rec e() {
    rec z; REP(i, M) REP(j, M) z[i][j] = i == j ? 0 : -INFF;
    return z;
}

rec op(rec a, rec b) {
    rec z; REP(i, M) REP(j, M) {
        z[i][j] = -INFF;
        REP(k, M) checkMax(z[i][j], a[i][k] + b[k][j]);
    }
    return z;
}

VI X; struct Event {
    int t, x, c;
    void in() {
        RD(t, x); if (t == 2) RD(c);
        X.PB(x);
    }

    void go(segtree<rec, op, e>& T) {
        x = LBD(X, x);
        rec z = e(); if (t == 1) {
            z[0][2] = z[0][4] = 0;
            z[1][0] = z[3][0] = 0;
            z[3][2] = z[1][4] = 0;
        } else {
            FOR(i, 1, M) z[i][i] = c;
            z[0][1] = z[0][3] = c;
            z[2][0] = z[4][0] = c;
        }
        T.set(x*2, z);
        printf("%lld\n", T.all_prod()[0][0]);
    }
} E[N]; int n;

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(n); REP(i, n) E[i].in(); UNQ(X);

    vector<rec> A; REP(i, SZ(X)-1) {
        A.PB(e()); rec z = e(); int len = X[i+1] - X[i];
        z[1][1] = z[2][2] = -len;
        z[3][3] = z[4][4] = -2*len;
        A.PB(z);
    }
    A.PB(e()); segtree<rec, op, e> T(A);
    REP(i, n) E[i].go(T);
}
