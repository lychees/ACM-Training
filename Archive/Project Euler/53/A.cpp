#include <lastweapon/io>

const int N = int(1e2) + 9;
DB Fact[N];


int main() {
    Fact[0] = log(1); FOR(i, 1, N) Fact[i] = Fact[i-1] + log(i);
    int z = 0;
    REP_1(i, 100) {
        REP(j, i) if (Fact[i] - Fact[j] - Fact[i-j] > log(1e6)) {
            ++z;
        }
    }
    cout << z << endl;
}


