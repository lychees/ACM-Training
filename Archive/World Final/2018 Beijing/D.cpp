#include <lastweapon/io>
using namespace lastweapon;

const int N = int(1e3) + 9;
DB F[N][N], G[N][N], C[N][N];
int n, m, r;

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(n,m,r);

    REP(i, n+m) {
        C[i][0] = 1;
        REP(j, i) C[i][j+1] = C[i-1][j] + C[i-1][j+1];
    }

    G[0][n] = 1;

#define gu G[i][j]
#define fu F[i][j]
#define c C[j][d]

    REP(i, m) {
        REP(j, n+1) if (sgn(gu)) {
            REP_1(d, min(j, m-i)) {
                G[i+d][d] += gu * c;
                F[i+d][d] += (fu + gu * min(d,r)) * c;
            }
        }
    }

    printf("%.7f\n", accumulate(F[m], F[m]+n+1, .0)/C[n-1+m][m] + r);
}
