#include <lastweapon/string>

VI T; int n, m;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    RD(n, m); T.resize(n+m);
    REP(i, n) RD(T[m+i]); REP(i, m) RD(T[i]);
    REP(i, m-1) T[i] = T[i+1] - T[i]; T[m-1] = INF;
    REP(i, n-1) T[m+i] = T[m+i+1] - T[m+i]; T.pop_back();

    auto pi = lastweapon::kmp(T);

    int z = 0; FOR(i, m, SZ(pi)) if (pi[i] == m-2) ++z;
    cout << z << endl;
}
