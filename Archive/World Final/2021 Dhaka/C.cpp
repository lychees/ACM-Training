#include <lastweapon/number>
using namespace lastweapon;

bool ok() {
    LL n, m; RD(n, m); if (n > 100) return 0;

    FOR(q, 2, 4001) {
        FOR(p, 1, q) {
            if (gcd(p, q) != 1) continue;
            if (pow((DB)q, n) - pow((DB)(q-p), n) > (DB)2*m*p) continue;

            __int128 a = 1, b = 1; REP(i, n) {
                a *= q; b *= q-p;
            }
            __int128 t = (a - b) / p;
            if (m % t == 0) {
                cout << p << " " << q << endl;
                return 1;
            }
        }
    }
    return 0;
}

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    if (!ok()) puts("impossible");
}
