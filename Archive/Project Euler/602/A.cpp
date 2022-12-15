#include <lastweapon/number>
using namespace lastweapon;

const int N = int(1e7) + 9;
Int Fact[N];
int n, m;

Int Binom(int n, int m) {
    if (m > n) return 0;
    return Fact[n] / (Fact[m] * Fact[n-m]);
}

int main() {

#ifndef ONLINE_JUDGE
     //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    // int n = 100, m = 40;
    int n = 10000000, m = 4000000;
    Fact[0] = 1; REP_1(i, n+1) Fact[i] = Fact[i-1] * i;

    Int z = 0; REP(i, m) {
        Int t = Binom(n+1, i) * pow(Int(m-i), n);
        if (i&1) {
            z -= t;
        } else {
            z += t;
        }
    }
    cout << z << endl;
}
