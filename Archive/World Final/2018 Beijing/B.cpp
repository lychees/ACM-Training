#include <lastweapon/io>
#include <lastweapon/dsu>
#include <unordered_map>
using namespace lastweapon;

const int N = int(2e6) + 9;

string s[N]; unordered_map<string, int> ID;
int n, nn;

int id(const string s) {
    if (!CTN(ID, s)) return ID[s] = ++nn;
    return ID[s];
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    dsu d(N); int x, xx; char t, tt; while (cin >> s[n]) {
        t = s[n].back(); if (t == ',' || t == '.') s[n].pop_back(); x = id(s[n]);
        if (t == ',') d.merge(0, x*2);
        if (tt == ',') d.merge(0, x*2+1);
        if (n && tt != '.') d.merge(xx*2, x*2+1);
        if (t == '.') s[n] += '.';
        tt = t; xx = x; ++n;
    }

    REP(i, n) {
        if (i) cout << " "; cout << s[i];
        int x = id(s[i]); if (d.same(0, x*2)) cout << ",";
    }
}
