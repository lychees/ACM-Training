#include<lastweapon/io>
using namespace lastweapon;

const int PMAX = int(6e6) + 9;
VI P; bitset<PMAX> isC;

map<string, VI> H;

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

int a[10], c[10];
int x, n;

void dfs(int k, int c, int t, string x, int p) {

    if (k == -1) {
        H[x].PB(p);
        if (SZ(H[x]) >= 8) {
            SRT(H[x]);
            for (auto t: H[x]) cout << t << " "; cout << endl;
            exit(0);
        }
    } else {
        if (a[k] != t){
            x += '0' + a[k];
            dfs(k-1, c, t, x, p);
        } else {
            if (c > 2) {
                x += '0' + a[k];
                dfs(k-1, c-1, t, x, p);
                x.pop_back();
            }
            x += '$';
            dfs(k-1, c, t, x, p);
        }
    }

}


int main() {
    sieve();
    for (auto p: P) {
        RST(c); x = p, n = 0; while (x) {
            c[a[n++] = x % 10]++;
            x /= 10;
        }

        REP(t, 10) if (c[t] >= 2) {

            string x; dfs(n-1, c[t], t, x, p);
        }
    }
}
