#include <lastweapon/io>

const int PMAX = int(1e6) + 9;
VI P; bitset<PMAX> isC;
int z;

#define ii (i*P[j])
void sieve(){
    FOR(i, 2, PMAX){
        if (!isC[i]) P.PB(i);
        for (int j=0;j<SZ(P)&&ii<PMAX;++j){
            isC[ii]=1; if (!(i%P[j])) break;
        }
    }
}
#undef ii

bool ok(int n) {
    int t = 0;
    for (auto p: P) {
        if (p*p > n) break;
        if (n % p == 0) {
            ++t;
            if (t > 4) return 0;
            do {n /= p;} while (n % p == 0);
        }
    }
    if (n) ++t;
    return t == 4;
}

int main() {

    sieve();

    int c = 0;

    FOR_1(i, 642, 1000000) {
        if (ok(i)) {
            ++c;
            if (c == 4) {
                cout << i - 3 << endl;
            }
        } else {
            c = 0;
        }
    }


}


