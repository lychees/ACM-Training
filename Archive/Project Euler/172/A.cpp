#include <lastweapon/io>
using namespace lastweapon;
LL Fact[20];

LL Binom(int n, int m) {
    return Fact[n] / Fact[m] / Fact[n-m];
}

int main() {

    Fact[0] = 1; FOR(i, 1, 19) Fact[i] = Fact[i-1] * i;

    LL z = 0; int n = 18;
    REP(i, 10) {
        REP(j, 10) {
            int k = n - i*3 - j*2;
            if (0 <= k && i+j+k <= 10) {
                z += Fact[n] / pow(6ll, i) / pow(2ll, j) * Binom(10, i) * Binom(10-i, j) * Binom(10-i-j, k);
            }
        }
    }
    cout << z << endl;
    cout << z - z / 10 << endl;
}
