#include <lastweapon/io>
using namespace lastweapon;

const int N = int(2e4) + 9;

int deg[N], o[N];
int n, t;

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(n); Rush {
        int a, b; RD(a, b); ++deg[a], ++deg[b];
    }
    REP(i, n) --deg[i];

    iota(o, o+n, 0); sort(o, o+n, [](int a, int b){
        return deg[a] < deg[b];
    });

    int z = 0, m = n-2; REP(i, n) {
        int d = min(m, deg[o[i]]); m -= d;
        if (d < deg[o[i]]) {
            deg[o[i]] = d;
            ++z;
        }
    }

    cout << z << endl;
    cout << n << " " << n-1 << endl;

    sort(o, o+n, [](int a, int b){
        return deg[a] < deg[b];
    });

    set<PII> Q; DWN(i, n, 0) {
        PII u = {deg[o[i]], o[i]};
        if (!Q.empty()) {
            PII v = *Q.rbegin(); Q.erase(--Q.end());
            cout << u.se << " " << v.se << endl;
            u.fi -= 1; v.fi -= 1;
            if (~v.fi) Q.insert(v);
        }
        if (~u.fi) Q.insert(u);
    }
}
