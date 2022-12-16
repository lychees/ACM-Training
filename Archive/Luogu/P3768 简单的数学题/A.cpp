#include <lastweapon/number>
using namespace lastweapon;

const int PMAX = int(1e7) + 9;
VI P; bitset<PMAX> isP; LL phi[PMAX]; Int _S[PMAX];
LL n;

void sieve() {
    phi[1] = 1;
    FOR(i, 2, PMAX){
        if (!isP[i]) P.PB(i), phi[i] = i-1;
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            int ii = i*P[j];
            isP[ii]=1; if (i%P[j]){
                phi[ii] = phi[i] * (P[j] - 1);
            } else{
                phi[ii] = phi[i] * P[j];
                break;
            }
        }
    }

    FOR(i, 1, PMAX) _S[i] = _S[i-1] + (Int)phi[i]*i*i;
}

Int S1(Int n) {
    return n*(n+1)/2;
}
Int S2(Int n) {
    return n*(n+1)*(2*n+1)/6;
}
Int S3(Int n) {
    return sqr(S1(n));
}

map<LL, Int> s;
Int S(LL n) {
    if (n < PMAX) return _S[n];
    if (!CTN(s, n)) {
        Int &z = s[n]; z = S3(n);
        for (LL i = 2, j; i <= n; i = j+1) {
            j = n / (n/i);
            z -= S(n/i) * (S2(j) - S2(i-1));
        }
    }
    return s[n];
}


int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif

    RD(MOD, n);
    sieve();

    Int z = 0;
    for (LL i = 1, j; i <= n; i = j+1) {
        j = n / (n/i);
        z += S3(n/i) * (S(j) - S(i-1));
    }

    cout << z <<endl;
}




