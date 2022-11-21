#include <lastweapon/io>
#include <lastweapon/dsu>
#include <unordered_map>
using namespace lastweapon;

const int N = int(1e6) + 9;

DB f[N];

map<LL, VI> adj;

struct edge {
    int a, b; LL s, t; DB p, fa, fb;
    void in(int i) {
        RD(a, b, s, t); RF(p);
        adj[-t].PB(i);
        adj[-s].PB(i);
    }
    void get_fb() {
        fb = f[b];
    }
    void get_fa() {
        fa = p * fb + (1 - p) * f[a];
    }
    void upd_fa() {
        checkMax(f[a], fa);
    }
} E[N];


int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    int m; LL _; RD(m, _, _); REP(i, m) {
        E[i].in(i);
    }

    f[1] = 1.0; for (auto [t, a]: adj) {
        for (auto i: a) if (E[i].s + t) E[i].get_fb();
        for (auto i: a) if (E[i].t + t) E[i].get_fa();
        for (auto i: a) if (E[i].t + t) E[i].upd_fa();
    }

    printf("%.9f\n",f[0]);
}
