#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define Rush for(int ____T=RD(); ____T--;)
#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)
#define PB push_back
#define SZ(A) int(A.size())
#define ALL(A) A.begin(), A.end()
template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline T& RD(T &);
inline LL RD(){LL x; return RD(x);}
#define g (c=getchar())
#define d isdigit(g)
#define p x=x*10+c-'0'
#define n x=x*10+'0'-c
#define pp l/=10,p
#define nn l/=10,n
template<class T> inline T& RD(T &x){
    char c;while(!d);x=c-'0';while(d)p;
    return x;
}
#undef nn
#undef pp
#undef n
#undef p
#undef d
#undef g

const int N = int(5e4) + 9;
vector<int> a, b; int pre[N], lst;
int inLIS[N], inDEL[N];
int n;

int LISS(){
    int n = a.size();
    vector<int> b; b.PB(0); pre[0] = -1; FOR(i, 1, n){
        if (a[b.back()] < a[i]) pre[i] = b.back(), b.PB(i);
        else {
            int l = 0, r = SZ(b); while (l < r){
                int m = l + r >> 1;
                if (a[b[m]] < a[i]) l = m + 1;
                else r = m;
            }
            pre[i] = !r ? -1 : b[r-1];
            b[r] = i;
        }
    }
    lst = b.back();
    return SZ(b);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/users/xiaodao/desktop/Exercise/out.txt", "w", stdout);
#endif
    Rush {
        RD(n);
        a.clear(), b.clear(); RST(inLIS); RST(inDEL);
        REP(i, n) a.PB(RD()-1);
        REP(i, n) b.PB(a[RD()-1]);

        int i = n-1;
        while (i >= 0) {
            int z = LISS();
            while (lst >= 0) inLIS[a[lst]] = i, lst = pre[lst];

            do {
                inDEL[b[i]] = i;
                if (inLIS[b[i]] >= i) break; // дк LIS жа
                b[i--] = z;
            } while (i >= 0);
            b[i--] = z; vector<int> t = a; a.clear();
            REP(j, t.size()) if (inDEL[a[j]] < i) a.PB(t[j]);
        }
        REP(i, n-1) printf("%d ", b[i]);
        printf("%d\n", b[n-1]);

    }
}
