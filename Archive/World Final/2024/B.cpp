#include <lastweapon/io>
using namespace lastweapon;

const int N = int(1e2) + 9;
int n, k; MII last; VI A; int c[N];

int main() {

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    RD(n, k); REP(i, n) DO(k) {
        int a; RD(a); A.PB(a);
        last[a] = i;
    }
    for (auto a: A) ++c[last[a]];
    DB t = 1.0 / (n*k);
    REP(i, n) printf("%.9f\n", t*c[i]);
}

