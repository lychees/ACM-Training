#include <cstdio>
#include <cctype>
#include <algorithm>
#include <iostream>

using namespace std;

#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)
#define REP_1(i, n) for (int i=1;i<=n;++i)
#define FOR_1(i, a, b) for (int i=a;i<=b;++i)
#define DWN_1(i, b, a) for (int i=b;i>=a;--i)

#define Ts *this
#define rTs return Ts

template<class T> inline T& RD(T &);
inline char& RC(char &c){scanf(" %c", &c); return c;}
inline char RC(){char c; return RC(c);}
//}

/** Constant List .. **/ //{

const int MOD = 998244353;
typedef long long LL;

// <<= '2. Number Theory .,//{
namespace NT{
#define gcd __gcd
inline LL lcm(LL a, LL b){return a*b/gcd(a,b);}

inline void INC(int &a, int b){a += b; if (a >= MOD) a -= MOD;}
inline int sum(int a, int b){a += b; if (a >= MOD) a -= MOD; return a;}

/* 模数两倍刚好超 int 时。
inline int sum(uint a, int b){a += b; a %= MOD;if (a < 0) a += MOD; return a;}
inline void INC(int &a, int b){a = sum(a, b);}
*/

inline void DEC(int &a, int b){a -= b; if (a < 0) a += MOD;}
inline int dff(int a, int b){a -= b; if (a < 0) a  += MOD; return a;}
inline void MUL(int &a, int b){a = (LL)a * b % MOD;}
inline int pdt(int a, int b){return (LL)a * b % MOD;}

inline int gcd(int m, int n, int &x, int &y){

    x = 1, y = 0; int xx = 0, yy = 1, q;

    while (1){
        q = m / n, m %= n;
        if (!m){x = xx, y = yy; return n;}
        DEC(x, pdt(q, xx)), DEC(y, pdt(q, yy));
        q = n / m, n %= m;
        if (!n) return m;
        DEC(xx, pdt(q, x)), DEC(yy, pdt(q, y));
    }
}

inline int sum(int a, int b, int c){return sum(a, sum(b, c));}
inline int sum(int a, int b, int c, int d){return sum(sum(a, b), sum(c, d));}
inline int pdt(int a, int b, int c){return pdt(a, pdt(b, c));}
inline int pdt(int a, int b, int c, int d){return pdt(pdt(a, b), pdt(c, d));}

inline int pow(int a, LL b){
    int c(1); while (b){
        if (b&1) MUL(c, a);
        MUL(a, a), b >>= 1;
    }
    return c;
}

template<class T> inline T pow(T a, LL b){
    T c(1); while (b){
        if (b&1) c *= a;
        a *= a, b >>= 1;
    }
    return c;
}

template<class T> inline T pow(T a, int b){
    return pow(a, (LL)b);
}

inline int _I(int b){
    int a = MOD, x1 = 0, x2 = 1, q; while (1){
        q = a / b, a %= b;
        if (!a) return x2;
        DEC(x1, pdt(q, x2));

        q = b / a, b %= a;
        if (!b) return x1;
        DEC(x2, pdt(q, x1));
    }
}

inline void DIV(int &a, int b){MUL(a, _I(b));}
inline int qtt(int a, int b){return pdt(a, _I(b));}

struct Int{
    int val;

    operator int() const{return val;}

    Int(int _val = 0):val(_val){
        val %= MOD; if (val < 0) val += MOD;
    }
    Int(LL _val):val(_val){
        _val %= MOD; if (_val < 0) _val += MOD;
        val = _val;
    }

    Int& operator +=(const int& rhs){INC(val, rhs);rTs;}
    Int operator +(const int& rhs) const{return sum(val, rhs);}
    Int& operator -=(const int& rhs){DEC(val, rhs);rTs;}
    Int operator -(const int& rhs) const{return dff(val, rhs);}
    Int& operator *=(const int& rhs){MUL(val, rhs);rTs;}
    Int operator *(const int& rhs) const{return pdt(val, rhs);}
    Int& operator /=(const int& rhs){DIV(val, rhs);rTs;}
    Int operator /(const int& rhs) const{return qtt(val, rhs);}
    Int operator-()const{return MOD-*this;}
};

} using namespace NT;//}


//}



/** I/O Accelerator Interface .. **/ //{
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
inline char* RS(char *s){
    //gets(s);
    scanf("%s", s);
    return s;
}

LL last_ans; int Case; template<class T> inline void OT(const T &x){
    //printf("Case #%d: ", ++Case);
    //printf("%lld\n", x);
    //printf("%I64d\n", x);
    //printf("%.9f\n", x);
    //printf("%d\n", x);
    cout << x << endl;
    //last_ans = x;
}


//}/* .................................................................................................................................. */
template<class T> inline T min(T a, T b, T c){return min(min(a, b), c);}
template<class T0, class T1, class T2> inline T0& RD(T0 &x0, T1 &x1, T2 &x2){RD(x0), RD(x1), RD(x2); return x0;}
template<class T0, class T1, class T2, class T3> inline T0& RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3){RD(x0), RD(x1), RD(x2), RD(x3); return x0;}
#define fi first
#define se second
const int INF = 0x3f3f3f3f;
const int N = int(1e6)+9, M = 2*N;

struct node{

    static node* NIL; node *c[2], *p;
    pair<int, node*> w1, w0; int sz; bool r0;

#define NIL node::NIL
#define l c[0]
#define r c[1]
#define lx x->l
#define rx x->r
#define px x->p
#define ly y->l
#define ry y->r
#define py y->p

    void reset(int t = INF){
        l = r = p = NIL; sz = t == INF;
        w1 = w0 = {t, this}; r0 = 0;
    }

    inline node(int t = INF){
        reset(t);
    }

    inline void rev(){
        r0 ^= 1, swap(l, r);
    }

    inline void upd(){
        if (this == NIL) return;
        sz = l->sz + (w0.fi == INF) + r->sz;
        w1 = min(l->w1, w0, r->w1);
    }

    inline void rls(){
        //if (this == NIL) return;
        if (r0){
            l->rev(), r->rev();
            r0 = 0;
        }
    }

    // 旋转

    inline int sgn(){return p->l==this?0:p->r==this?1:-1;}
    inline void setc(int d,node*x){c[d]=x,px=this;}

    inline void rot(int d){
        node *y = p, *z = py; if (~y->sgn()) z->setc(y->sgn(), this); else p = z;
        y->setc(!d, c[d]), setc(d, y), y->upd();
    }

    inline void rot(){rot(!sgn());}
    inline void zag(){rot(0);}
    inline void zig(){rot(1);}

    // 伸展

    inline void fix(){if(~sgn()) p->fix(); rls();}

    /*
    inline node* splay(){
        fix(); while (~sgn()) rot(); upd();
        return this;
    }
    /*/
    inline node* splay(){
        fix(); while (sgn() != -1){
            node *y = p, *z = py; if (y->sgn() == -1){ rot(); break;}
            if (z->l == y){
                if (y->l == this) y->zig(), zig();
                else zag(), zig();
            }else{
                if (y->r == this) y->zag(), zag();
                else zig(), zag();
            }
        }
        upd();
        return this;
    } //*/

    inline node* acs(){
        node *x = this, *y = NIL; do{
            x->splay();
            rx = y, x->upd();
            y = x, x = px;
        } while (x != NIL);
        return splay();
    }

    node* rt(){node* x; for (x = acs(); x->rls(), lx != NIL; x = lx); return x->splay();}
    node* ert(){acs()->rev(); return this;}


    void Link(node *x){
        if (rt() == x->rt()){
            puts("-1");
        }
        else {
            ert(), p = x;
        }
    }

    void Cut(){
        acs(); l->p = NIL; l = NIL;
    }

    void Cut(node* x){
        if (this == x || rt() != x->rt()){
            puts("-1");
        }
        else {
            ert(), x->Cut();
        }
    }
#undef l
#undef r
#undef c
} *NIL, *T[N];

int bad[N];
bool ok[N];
int n, m;

struct edge{
    int x, y, l, r;

    bool operator <(const edge& rhs) const {
        return l < rhs.l;
    }
    void in() {
        RD(x, y, l, r);
        --x, --y;
    }
    void link() {
        if (T[x]->rt() == T[y]->rt()) {
            T[x]->ert(); T[y]->acs();
            auto t = T[y]->w1.se; int tr = T[y]->w1.fi;
            int rr = min(tr, r);
            if ((T[y]->sz&1) && (l < rr)) {
                bad[l] += 1;
                bad[rr] -= 1;
            }
            if (rr == r) return;
            t->Cut(); T[y]->ert(); t->Cut();
        }
        T[x]->ert(), T[y]->ert();
        auto t = new node(r);
        t->p = T[x]; T[y]->p = t;
    }
} E[N];

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    NIL = new node();
    int t; RD(n, m, t);

    REP(i, n) T[i] = new node();
    REP(i, m) E[i].in();

    sort(E, E+m); REP(i, m) E[i].link();

    REP(i, t) {
        puts(bad[i] ? "No" : "Yes");
        bad[i+1] += bad[i];
    }
}

