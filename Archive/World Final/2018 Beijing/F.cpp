#include <lastweapon/io>
using namespace lastweapon;

const int N = int(2e5) + 9, L = 81;
int c[N]; char s[N];
int n, t;

int f(int x) {
    map<int, int> dp[2]; int p = 0, q = 1, z = 0, l = 1, s = -1; REP(i, n) {
        if (s + c[i] + 1 > x) {
            ++l; s = c[i];
            swap(p, q); dp[p].clear();
        } else {
            if (s>=0) checkMax(z, dp[p][s] = max(dp[q][s-1], dp[q][s], dp[q][s+1]) + 1);
            s += c[i] + 1;
        }
    }
    return z;
}
int m(int x) {
    int l = 1, s = -1; REP(i, n) {
        s += c[i] + 1; if (s > x) {
            ++l; s = c[i];
        }
    }
    return l;
}
int d(int x) {
    int z = INF, s = -1; REP(i, n) {
        s += c[i] + 1; if (s > x) {
            checkMin(z, s - x);
            s = c[i];
        }
    }
    return z;
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    RD(n); REP(i, n) c[i] = strlen(RS(s));

    int l = *max_element(c, c+n), fl = f(l);

    for (int i=l+1;m(i)>fl;i+=d(i)) {
        int fi = f(i); if (fi > fl) {
            l = i; fl = fi;
        }
    }
    cout << l << " " << fl << endl;
}
