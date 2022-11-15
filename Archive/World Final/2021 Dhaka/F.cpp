#include <lastweapon/geometry>
using namespace lastweapon;
using namespace CG;

const int N = int(1e2) + 9;
vector<Po> P[N]; DB a[N];
int n, m;

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(n, m);  REP(i, n) {
        Rush P[i].PB(getPo());
        a[i] = OO;
    }

    REP(i, m) {
        Po p1, p2; int z1, z2; p1.in(); RD(z1); p2.in(); RD(z2);
        Seg s(p1, p2); DB d = (z2 - z1) / dist(p1, p2);
        REP(i, n) {
            DB b=0; for (auto p: P[i]) {
                Po o = p&s; if (dott(o,s) == 1) { // s.sgn(o)
                    b = OO; break;
                }
                DB h = z1 + dist(p1,o) * d;
                checkMax(b, dist(p,o)/h);
            }
            checkMin(a[i], b);
        }
    }

    DB z = 0; REP(i, n) checkMax(z, a[i]);
    if (!sgn(z, OO)) puts("impossible");
    else printf("%.9f\n", atan(z)/PI*180);
}
