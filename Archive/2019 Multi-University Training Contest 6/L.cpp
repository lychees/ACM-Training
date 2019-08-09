#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define Rush for(int ____T=RD(); ____T--;)
#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)
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

const int N = int(1e6) + 9;
int h[N];
int n;

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/users/xiaodao/desktop/Exercise/out.txt", "w", stdout);
#endif
    Rush {
        RD(n); REP(i, n) RD(h[i]);
        sort(h, h+n);
        LL a = 0, b = 0;
        DWN(i, n, 0) {
            a += h[i--];
            b += h[i];
        }
        cout << a << " " << b << endl;
    }
}
