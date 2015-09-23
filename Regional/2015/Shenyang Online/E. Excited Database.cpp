#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

#define PB push_back
#define MP make_pair

typedef double DB;
typedef long long LL;

const int N = int(4e5) + 9, NN = 4 * N;

int n; LL d;

struct SGT{
    LL S[NN], Sl[NN], Sr[NN]; int D[NN];
    int a, b, c, w;

#define root 1, 1, 2*n
#define ml ((l + r) >> 1)
#define mr (ml + 1)
#define lx (x << 1)
#define rx (lx | 1)
#define lc lx, l, ml
#define rc rx, mr, r
#define xx x, l, r

void inc(int x, int l, int r, int d){
    LL len = r-l+1;
    S[x] += len * d;
    Sl[x] += (len+1)*(len)/2 * d;
    Sr[x] += (len+1)*(len)/2 * d;
    D[x] += d;
}

void rls(int x, int l, int r){
    if (D[x]){
        inc(lc, D[x]), inc(rc, D[x]);
        D[x] = 0;
    }
}

void upd(int x, int l, int r){
    S[x] = S[lx] + S[rx];
    Sl[x] = Sl[lx] + Sl[rx] + (LL) (mr - l) * S[rx];
    Sr[x] = Sr[lx] + Sr[rx] + (LL) (r - ml) * S[lx];
}

void Build(int x, int l, int r){
    S[x] = Sl[x] = Sr[x] = D[x] = 0;
    if (l < r){
        Build(lc); Build(rc);
    }
}

void Insert(int x, int l, int r){

    if (b < l || r < a) return;
    if (a <= l && r <= b){
        inc(xx, 1);
    }
    else{
        rls(xx);
        Insert(lc), Insert(rc);
        upd(xx);
    }
}

    LL _Query(int x, int l, int r){
        if (b < l || r < a) return 0;
        if (a <= l && r <= b) return S[x];
        rls(xx); return _Query(lc) + _Query(rc);
    }
    LL Query(int l, int r){
        a = l, b = r;
        return _Query(root);
    }

    LL _QueryL(int x, int l, int r){
        if (b < l || r < a) return 0;
        if (a <= l && r <= b){
            LL z = Sl[x] + d * S[x];
            d += r - l + 1;
            return z;
        }
        rls(xx);
        LL z = _QueryL(lc); z += _QueryL(rc);
        return z;
        //return Query(lc) + Query(rc);
    }

    LL QueryL(int l, int r){
        d = 0; a = l; b = r;
        return _QueryL(root);
    }

    LL _QueryR(int x, int l, int r){
        if (b < l || r < a) return 0;
        if (a <= l && r <= b){
            LL z = Sr[x] + (LL)d * S[x];
            d += r - l + 1;
            return z;
        }
        rls(xx);
        LL z = _QueryR(rc); z += _QueryR(lc);
        return z;
    }

    LL QueryR(int l, int r){
        d = 0; a = l; b = r;
        return _QueryR(root);
    }

} T1, T2;


int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
#endif

    int CAS; scanf("%d", &CAS);
    for (int cas = 1; cas <= CAS; cas++){

        printf("Case #%d:\n", cas);

        scanf("%d", &n);
        T1.Build(root);
        T2.Build(root);

        int CMD; scanf("%d", &CMD); while (CMD--){
            int cmd; scanf("%d", &cmd);

            if (cmd == 3){
                int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
                LL z = 0;
                int d1 = min(x2-x1+1 , y2-y1+ 1) - 1 ;
                int d3 = d1 ;
                int d2 = x2 - x1 + 1 + y2 - y1 + 1 - 1 - d1 - d3 ;
                LL ans = 0;
                ans += T1.QueryL(x1+y1, x1+y1+d1-1);
                ans += T1.QueryR(x2+y2-d3+1, x2+y2);
                ans += T1.Query(x1+y1+d1, x1+y1+d1+d2-1) * (d1+1);
                ans += T2.QueryL((x1-y2+n), (x1-y2+n+d1-1));
                ans += T2.QueryR((x2-y1+n-d3+1), (x2-y1+n));
                ans += T2.Query((x1-y2+n+d1), (x1-y2+n+d1+d2-1)) * (d1+1);
                cout << ans << endl;
            }
            else if (cmd == 1){
                int l, r; scanf("%d %d", &l, &r); T1.a = l, T1.b = r;
                T1.Insert(root);
            }
            else{
                int l, r; scanf("%d %d", &l, &r); T2.a = l+n, T2.b = r+n;
                T2.Insert(root);
            }
        }
    }
}
