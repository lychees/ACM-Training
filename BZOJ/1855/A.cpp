#include <iostream>
#include <cstdio>
using namespace std;
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}
const int INF = 0x3f3f3f3f;
const int N = int(2e3) + 9, M = N;
int f[N][M], q[N], cz, op, n, m, w;

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
#endif

    scanf("%d%d%d", &n, &m, &w); ++w;
    fill(f[0], f[0]+m+1, -INF); f[0][0] = 0;

    int z = 0; for (int i=1;i<=n;++i){
        int AP, BP, AS, BS; scanf("%d%d%d%d", &AP, &BP, &AS, &BS);
        int ii = i-w > 0 ? i-w : 0;

#define u f[i][j]
        cz = 0, op = -1; for(int j=0;j<=m;++j){ // buy
            u = f[i-1][j];
            while (cz <= op && q[cz] < j-AS) ++cz;
            if (cz <= op) checkMax(u, f[ii][q[cz]] + (q[cz]-j)*AP);
            while (cz <= op && f[ii][j]+AP*j >= f[ii][q[op]]+AP*q[op]) --op;
            q[++op] = j;
        }
        cz = 0, op = -1; for(int j=m;j>=0;--j){ // sell
            while (cz <= op && q[cz] > j+BS) ++cz;
            if (cz <= op) checkMax(u, f[ii][q[cz]] + (q[cz]-j)*BP);
            while (cz <= op && f[ii][j]+BP*j >= f[ii][q[op]]+BP*q[op]) --op;
            q[++op] = j;
        }
        checkMax(z, f[i][0]);
    }

    printf("%d\n", z);
}
