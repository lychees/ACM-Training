#include <lastweapon/io>
using namespace lastweapon;

const int N = int(2e5) + 9;
int n, s; map<int, VI> ll, lr, rl, rr; set<PII> L, R;
VI T; bool used[N];

struct rec {
    int l, r;

    void in(int id) {
        RD(l, r); l *= 2; r *= 2; l -= s; r -= s; T.PB(abs(l)); T.PB(abs(r));
        if (r<0) {
            ll[-l].PB(id);
            lr[-r].PB(id);
        } else if (l>0) {
            rl[l].PB(id);
            rr[r].PB(id);
        } else {
            if (l<=0) ll[-l].PB(id);
            if (r>=0) rr[r].PB(id);
        }
    }
} I[N];

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(n, s); REP(i, n) I[i].in(i); RVS(UNQ(T));

    VII z; for (auto t: T) {
        for (auto id: ll[t]) L.insert({-I[id].r, id});
        for (auto id: rr[t]) R.insert({I[id].l, id});

        for (auto a: lr[t]) {
            L.erase({-I[a].r, a}); if (used[a]) continue;
            while (!R.empty()) {
                auto r = --R.end(); int b = r->se; R.erase(r);
                if (used[b]) continue;
                z.PB({a, b}); used[a] = 1; used[b] = 1;
                break;
            }
        }
        for (auto a: rl[t]) {
            R.erase({I[a].l, a}); if (used[a]) continue;
            while (!L.empty()) {
                auto l = --L.end(); int b = l->se; L.erase(l);
                if (used[b]) continue;
                z.PB({a, b}); used[a] = 1; used[b] = 1;
                break;
            }
        }
    }

    int l = -1; for (auto t: L) if (!used[t.se]){
        if (l == -1) l = t.se;
        else {
            z.PB({l, t.se});
            l = -1;
        }
    }

    cout << SZ(z) << endl;
    for (auto [a, b]: z) printf("%d %d\n", a+1, b+1);
}
