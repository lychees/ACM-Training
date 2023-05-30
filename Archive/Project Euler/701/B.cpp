#include <lastweapon/bitwise>
using namespace lastweapon;

const int N = 7;
int n;

map<pair<VI, VI>, LL> H[2];
VI s, p; int src, des;
int sn, pn;

void upd(LL d) {

    map<int, int> pp, ss; int n = 0;
    REP(i, pn) if (p[i]) {
        if (!CTN(pp, p[i])) pp[p[i]] = ++n, ss[n] = s[p[i]];
        p[i] = pp[p[i]];
    }
    FOR(i, 1, sn) s[i] = ss[i], checkMax(s[0], s[i]);
    H[des][{s, p}] += d;
}

void trans(int op, int x, int y, const pair<pair<VI, VI>, LL> u){

    REP(i, sn) s[i] = u.fi.fi[i];
    REP(i, pn) p[i] = u.fi.se[i];
    int lt = y ? p[y-1] : 0, up = p[y];

    if (!op) {
        if (up) {
            int c = 0; REP(i, pn) if (p[i] == up) ++c;
            if (c == 1) s[up] = 0;
            p[y] = 0;
        }
    } else {
        if (lt && up) {
            if (lt != up) {
                REP(i, n+1) if (p[i] == up) p[i] = lt;
                s[lt] += s[up];
            }
            s[p[y] = lt]++;
        } else if (lt || up) {
            s[p[y] = lt | up]++;
        } else {
            FOR(i, 1, sn) if (!s[i]) {
                s[p[y] = i] = 1;
                break;
            }
        }
    }
    upd(u.se);
}


LL solve(){
    src = 0; des = 1; H[des].clear();
    sn =  n/2+2; pn = n; s.assign(sn, 0); p.assign(pn, 0);
    H[des][{s, p}] = 1ll;

    REP(i, n) {
        REP(j, n) {
            swap(src, des); H[des].clear();
            for (auto u: H[src]){
                trans(0, i, j, u);
                trans(1, i, j, u);
            }
        }
    }

    LL z = 0; for (auto u: H[des]) {
        z += u.se * u.fi.fi[0];
    }
    return z;
}

int main() {
    //cin >> n;
    FOR_1(i, 7, 7) {
        n = i;
        printf("%.8f\n", (DB)solve()/_1(n*n));
    }
}
