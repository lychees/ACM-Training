#include <lastweapon/number>
using namespace lastweapon;

const int N = int(2e5) + 9;
map<int, int> F; VII E;
int n;

int l(int x) {
    auto it = F.lower_bound(x); int z = 0;
    if (it == F.begin()) z += n, it = F.end(); --it;
    z += it->se + (x - it->fi);
    return z;
}

int r(int x) {
    auto it = F.upper_bound(x); int z = 0;
    if (it == F.end()) z += n, it = F.begin();
    z += it->se + (it->fi - x);
    return z;
}

int f(int x) {
    if (!CTN(F, x)) return F[x] = min(l(x), r(x));
    return F[x];
}

void upd(int x, int v) {
    if (f(x) <= v) return;
    F[x] = v;
    while (1) {
        auto it = F.upper_bound(x); if (it == F.end()) it = F.begin();
        // cout << "upd: " << x << " "<< v << " " << it->fi << " " << l(it->fi) << " " << it->se << endl;
        if (l(it->fi) <= it->se) F.erase(it);
        else break;
    }
    while (1) {
        auto it = F.lower_bound(x); if (it == F.begin()) it = F.end(); --it;
        if (r(it->fi) <= it->se) F.erase(it);
        else break;
    }
}

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    int m, s; RD(n, m, s); F[--s] = 0; DO(m) {
        int t, x; RD(t, x); --x;
        E.PB({-t, x});
    }

    SRT(E); for (auto [_, x]: E) {
        int y = x + 1; if (y == n) y = 0;
        int fx = f(x), fy = f(y);

        //cout << " E: " << x << " "<< y << " " << fx << " " << fy << " " << n << endl;
        if (fx == fy) continue;
        int a = x - 1; if (a < 0) a = n-1; f(a);
        int b = y + 1; if (b == n) b = 0; f(b);

        if (fx < fy) {
            F.erase(F.find(x));
            upd(y, fx);
        } else {
            F.erase(F.find(y));
            upd(x, fy);
        }
    }

    REP(i, n) printf("%d\n", f(i));
}
