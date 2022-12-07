#include<lastweapon/io>
using namespace lastweapon;

const int PMAX = int(1e8) + 9;
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

int a[5];

LL f(int a, int b) {
    return stoll(to_string(a) + to_string(b));
}

bool is_prime(LL n) {
    if (n < PMAX) return !isC[n];
    for (auto p: P) {
        if (p*p > n) break;
        if (n % p == 0) return 0;
    }
    return 1;
}

bool ok(int k, int p) {
    REP(i, k) if (!is_prime(f(a[i], p)) || !is_prime(f(p, a[i]))) return 0;
    return 1;
}

void dfs(int k = 0, int s = 0, int ii = 1) {
    //cout << k << " " << P[s] << " " <<SZ(P) << endl;
    if (k == 5) {
        int zz = 0;
        REP(i, 5) {
            cout << a[i] << " ";
            zz += a[i];
        }
        checkMin(z, zz);
        cout << endl;
        cout << zz << endl;
    } else {
        for (int i=ii;s+P[i]*(5-k)<=z;++i) {
            if (ok(k, P[i])) {
                a[k] = P[i];
                dfs(k+1, s+P[i], i+1);
            }
        }
    }
}


int main() {
    z = 26033;
    sieve();
    dfs();
}
