/*
    This code has been written by MinakoKojima, feel free to ask me question. Blog: http://www.shuizilong.com/house
    Template Date: 2015.10.12
    Note: ...
*/

#pragma comment(linker, "/STACK:36777216")
//#pragma GCC optimize ("O2")
#define LOCAL
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

//#include <tr1/unordered_set>
//#include <tr1/unordered_map>
//#include <array>

using namespace std;

#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)
#define REP_1(i, n) for (int i=1;i<=n;++i)
#define FOR_1(i, a, b) for (int i=a;i<=b;++i)
#define DWN_1(i, b, a) for (int i=b;i>=a;--i)
#define REP_C(i, n) for (int n____=n,i=0;i<n____;++i)
#define FOR_C(i, a, b) for (int b____=b,i=a;i<b____;++i)
#define DWN_C(i, b, a) for (int a____=a,i=b-1;i>=a____;--i)
#define REP_N(i, n) for (i=0;i<n;++i)
#define FOR_N(i, a, b) for (i=a;i<b;++i)
#define DWN_N(i, b, a) for (i=b-1;i>=a;--i)
#define REP_1_C(i, n) for (int n____=n,i=1;i<=n____;++i)
#define FOR_1_C(i, a, b) for (int b____=b,i=a;i<=b____;++i)
#define DWN_1_C(i, b, a) for (int a____=a,i=b;i>=a____;--i)
#define REP_1_N(i, n) for (i=1;i<=n;++i)
#define FOR_1_N(i, a, b) for (i=a;i<=b;++i)
#define DWN_1_N(i, b, a) for (i=b;i>=a;--i)
#define REP_C_N(i, n) for (int n____=(i=0,n);i<n____;++i)
#define FOR_C_N(i, a, b) for (int b____=(i=0,b);i<b____;++i)
#define DWN_C_N(i, b, a) for (int a____=(i=b-1,a);i>=a____;--i)
#define REP_1_C_N(i, n) for (int n____=(i=1,n);i<=n____;++i)
#define FOR_1_C_N(i, a, b) for (int b____=(i=a,b);i<=b____;++i)
#define DWN_1_C_N(i, b, a) for (int a____=(i=b,a);i>=a____;--i)

#define ECH(it, A) for (__typeof((A).begin()) it=(A).begin(); it != (A).end(); ++it)
#define rECH(it, A) for (__typeof((A).rbegin()) it=(A).rbegin(); it != (A).rend(); ++it)
#define REP_S(i, str) for (char*i=str;*i;++i)
#define REP_L(i, hd, suc) for (int i=hd;i;i=suc[i])
#define REP_G(i, u) REP_L(i,hd[u],suc)
#define REP_SS(x, s) for (int x=s;x;x=(x-1)&s)
#define DO(n) for ( int ____n = n; ____n-->0; )
#define REP_2(i, j, n, m) REP(i, n) REP(j, m)
#define REP_2_1(i, j, n, m) REP_1(i, n) REP_1(j, m)
#define REP_3(i, j, k, n, m, l) REP(i, n) REP(j, m) REP(k, l)
#define REP_3_1(i, j, k, n, m, l) REP_1(i, n) REP_1(j, m) REP_1(k, l)
#define REP_4(i, j, k, ii, n, m, l, nn) REP(i, n) REP(j, m) REP(k, l) REP(ii, nn)
#define REP_4_1(i, j, k, ii, n, m, l, nn) REP_1(i, n) REP_1(j, m) REP_1(k, l) REP_1(ii, nn)

#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define INS(A, P, B) A.insert(A.begin() + P, B)
#define ERS(A, P) A.erase(A.begin() + P)
#define LBD(A, x) (lower_bound(ALL(A), x) - A.begin())
#define UBD(A, x) (upper_bound(ALL(A), x) - A.begin())
#define CTN(T, x) (T.find(x) != T.end())
#define SZ(A) int((A).size())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define PTT pair<T, T>
#define Ts *this
#define rTs return Ts
#define fi first
#define se second
#define re real()
#define im imag()

#define Rush for(int ____T=RD(); ____T--;)
#define Display(A, n, m) {                      \
  REP(i, n){		                            \
        REP(j, m-1) cout << A[i][j] << " ";     \
        cout << A[i][m-1] << endl;		        \
	}						                    \
}
#define Display_1(A, n, m) {                    \
	REP_1(i, n){		                        \
        REP_1(j, m-1) cout << A[i][j] << " ";   \
        cout << A[i][m] << endl;		        \
	}						                    \
}

typedef long long LL;
//typedef long double DB;
typedef double DB;
typedef unsigned uint;
typedef unsigned long long uLL;

typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<string> VS;
typedef vector<LL> VL;
typedef vector<DB> VF;
typedef set<int> SI;
typedef set<string> SS;
typedef map<int, int> MII;
typedef map<string, int> MSI;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef vector<VII> VVII;

template<class T> inline T& RD(T &);
template<class T> inline void OT(const T &);
//inline int RD(){int x; return RD(x);}
inline LL RD(){LL x; return RD(x);}
inline DB& RF(DB &);
inline DB RF(){DB x; return RF(x);}
inline char* RS(char *s);
inline char& RC(char &c);
inline char RC();
inline char& RC(char &c){scanf(" %c", &c); return c;}
inline char RC(){char c; return RC(c);}
//inline char& RC(char &c){c = getchar(); return c;}
//inline char RC(){return getchar();}

template<class T> inline T& RDD(T &);
inline LL RDD(){LL x; return RDD(x);}

template<class T0, class T1> inline T0& RD(T0 &x0, T1 &x1){RD(x0), RD(x1); return x0;}
template<class T0, class T1, class T2> inline T0& RD(T0 &x0, T1 &x1, T2 &x2){RD(x0), RD(x1), RD(x2); return x0;}
template<class T0, class T1, class T2, class T3> inline T0& RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3){RD(x0), RD(x1), RD(x2), RD(x3); return x0;}
template<class T0, class T1, class T2, class T3, class T4> inline T0& RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3, T4 &x4){RD(x0), RD(x1), RD(x2), RD(x3), RD(x4); return x0;}
template<class T0, class T1, class T2, class T3, class T4, class T5> inline T0& RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3, T4 &x4, T5 &x5){RD(x0), RD(x1), RD(x2), RD(x3), RD(x4), RD(x5); return x0;}
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6> inline T0& RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3, T4 &x4, T5 &x5, T6 &x6){RD(x0), RD(x1), RD(x2), RD(x3), RD(x4), RD(x5), RD(x6); return x0;}
template<class T0, class T1> inline void OT(const T0 &x0, const T1 &x1){OT(x0), OT(x1);}
template<class T0, class T1, class T2> inline void OT(const T0 &x0, const T1 &x1, const T2 &x2){OT(x0), OT(x1), OT(x2);}
template<class T0, class T1, class T2, class T3> inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3){OT(x0), OT(x1), OT(x2), OT(x3);}
template<class T0, class T1, class T2, class T3, class T4> inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4){OT(x0), OT(x1), OT(x2), OT(x3), OT(x4);}
template<class T0, class T1, class T2, class T3, class T4, class T5> inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5){OT(x0), OT(x1), OT(x2), OT(x3), OT(x4), OT(x5);}
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6> inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6){OT(x0), OT(x1), OT(x2), OT(x3), OT(x4), OT(x5), OT(x6);}
inline char& RC(char &a, char &b){RC(a), RC(b); return a;}
inline char& RC(char &a, char &b, char &c){RC(a), RC(b), RC(c); return a;}
inline char& RC(char &a, char &b, char &c, char &d){RC(a), RC(b), RC(c), RC(d); return a;}
inline char& RC(char &a, char &b, char &c, char &d, char &e){RC(a), RC(b), RC(c), RC(d), RC(e); return a;}
inline char& RC(char &a, char &b, char &c, char &d, char &e, char &f){RC(a), RC(b), RC(c), RC(d), RC(e), RC(f); return a;}
inline char& RC(char &a, char &b, char &c, char &d, char &e, char &f, char &g){RC(a), RC(b), RC(c), RC(d), RC(e), RC(f), RC(g); return a;}
inline DB& RF(DB &a, DB &b){RF(a), RF(b); return a;}
inline DB& RF(DB &a, DB &b, DB &c){RF(a), RF(b), RF(c); return a;}
inline DB& RF(DB &a, DB &b, DB &c, DB &d){RF(a), RF(b), RF(c), RF(d); return a;}
inline DB& RF(DB &a, DB &b, DB &c, DB &d, DB &e){RF(a), RF(b), RF(c), RF(d), RF(e); return a;}
inline DB& RF(DB &a, DB &b, DB &c, DB &d, DB &e, DB &f){RF(a), RF(b), RF(c), RF(d), RF(e), RF(f); return a;}
inline DB& RF(DB &a, DB &b, DB &c, DB &d, DB &e, DB &f, DB &g){RF(a), RF(b), RF(c), RF(d), RF(e), RF(f), RF(g); return a;}
inline void RS(char *s1, char *s2){RS(s1), RS(s2);}
inline void RS(char *s1, char *s2, char *s3){RS(s1), RS(s2), RS(s3);}
template<class T0,class T1>inline T0& RDD(T0&a, T1&b){RDD(a),RDD(b); return a;}
template<class T0,class T1,class T2>inline T1& RDD(T0&a, T1&b, T2&c){RDD(a),RDD(b),RDD(c); return a;}

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}
template<class T> inline void CLR(T &A){A.clear();}

template<class T0, class T1> inline void RST(T0 &A0, T1 &A1){RST(A0), RST(A1);}
template<class T0, class T1, class T2> inline void RST(T0 &A0, T1 &A1, T2 &A2){RST(A0), RST(A1), RST(A2);}
template<class T0, class T1, class T2, class T3> inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3){RST(A0), RST(A1), RST(A2), RST(A3);}
template<class T0, class T1, class T2, class T3, class T4> inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4){RST(A0), RST(A1), RST(A2), RST(A3), RST(A4);}
template<class T0, class T1, class T2, class T3, class T4, class T5> inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5){RST(A0), RST(A1), RST(A2), RST(A3), RST(A4), RST(A5);}
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6> inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, T6 &A6){RST(A0), RST(A1), RST(A2), RST(A3), RST(A4), RST(A5), RST(A6);}
template<class T0, class T1> inline void FLC(T0 &A0, T1 &A1, int x){FLC(A0, x), FLC(A1, x);}
template<class T0, class T1, class T2> inline void FLC(T0 &A0, T1 &A1, T2 &A2, int x){FLC(A0, x), FLC(A1, x), FLC(A2, x);}
template<class T0, class T1, class T2, class T3> inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, int x){FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x);}
template<class T0, class T1, class T2, class T3, class T4> inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, int x){FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x), FLC(A4, x);}
template<class T0, class T1, class T2, class T3, class T4, class T5> inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, int x){FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x), FLC(A4, x), FLC(A5, x);}
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6> inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, T6 &A6, int x){FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x), FLC(A4, x), FLC(A5, x), FLC(A6, x);}
template<class T> inline void CLR(priority_queue<T> &Q){while (!Q.empty()) Q.pop();}
template<class T> inline void CLR(stack<T> &S){while (!S.empty()) S.pop();}
template<class T> inline void CLR(queue<T> &Q){while (!Q.empty()) Q.pop();}

template<class T0, class T1> inline void CLR(T0 &A0, T1 &A1){CLR(A0), CLR(A1);}
template<class T0, class T1, class T2> inline void CLR(T0 &A0, T1 &A1, T2 &A2){CLR(A0), CLR(A1), CLR(A2);}
template<class T0, class T1, class T2, class T3> inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3){CLR(A0), CLR(A1), CLR(A2), CLR(A3);}
template<class T0, class T1, class T2, class T3, class T4> inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4){CLR(A0), CLR(A1), CLR(A2), CLR(A3), CLR(A4);}
template<class T0, class T1, class T2, class T3, class T4, class T5> inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5){CLR(A0), CLR(A1), CLR(A2), CLR(A3), CLR(A4), CLR(A5);}
template<class T0, class T1, class T2, class T3, class T4, class T5, class T6> inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, T6 &A6){CLR(A0), CLR(A1), CLR(A2), CLR(A3), CLR(A4), CLR(A5), CLR(A6);}
template<class T> inline void CLR(T &A, int n){REP(i, n) CLR(A[i]);}

template<class T> inline bool EPT(T &a){return a.empty();}
template<class T> inline T& SRT(T &A){sort(ALL(A)); return A;}
template<class T, class C> inline T& SRT(T &A, C cmp){sort(ALL(A), cmp); return A;}
template<class T> inline T& RVS(T &A){reverse(ALL(A)); return A;}
template<class T> inline T& UNQQ(T &A){A.resize(unique(ALL(A))-A.begin());return A;}
template<class T> inline T& UNQ(T &A){SRT(A);return UNQQ(A);}
template<class T, class C> inline T& UNQ(T &A, C cmp){SRT(A, cmp);return UNQQ(A);}


//}

/** Constant List .. **/ //{

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fLL;
const DB EPS = 1e-9;
const DB OO = 1e20;
const DB PI = acos(-1.0); //M_PI;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};

//}

/** Add On .. **/ //{
// <<= '0. Nichi Joo ., //{

template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}
template <class T, class C> inline bool checkUpd(T& a, const T b, C c){return c(b,a) ? a = b, 1 : 0;}
template<class T> inline T min(T a, T b, T c){return min(min(a, b), c);}
template<class T> inline T max(T a, T b, T c){return max(max(a, b), c);}
template<class T> inline T min(T a, T b, T c, T d){return min(min(a, b), min(c, d));}
template<class T> inline T max(T a, T b, T c, T d){return max(max(a, b), max(c, d));}
template<class T> inline T min(T a, T b, T c, T d, T e){return min(min(min(a,b),min(c,d)),e);}
template<class T> inline T max(T a, T b, T c, T d, T e){return max(max(max(a,b),max(c,d)),e);}
template<class T> inline T sqr(T a){return a*a;}
template<class T> inline T cub(T a){return a*a*a;}
template<class T> inline T ceil(T x, T y){return (x - 1) / y + 1;}
template<class T> T abs(T x){return x>0?x:-x;}
inline int sgn(DB x){return x < -EPS ? -1 : x > EPS;}
inline int sgn(DB x, DB y){return sgn(x - y);}

inline DB cos(DB a, DB b, DB c){return (sqr(a)+sqr(b)-sqr(c))/(2*a*b);}
inline DB cot(DB x){return 1./tan(x);};
inline DB sec(DB x){return 1./cos(x);};
inline DB csc(DB x){return 1./sin(x);};

//}

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
template<class T> inline T& RDD(T &x){
    char c;while(g,c!='-'&&!isdigit(c));
    if (c=='-'){x='0'-g;while(d)n;}
    else{x=c-'0';while(d)p;}
    return x;
}
inline DB& RF(DB &x){
    //scanf("%lf", &x);
    char c;while(g,c!='-'&&c!='.'&&!isdigit(c));
    if(c=='-')if(g=='.'){x=0;DB l=1;while(d)nn;x*=l;}
        else{x='0'-c;while(d)n;if(c=='.'){DB l=1;while(d)nn;x*=l;}}
    else if(c=='.'){x=0;DB l=1;while(d)pp;x*=l;}
        else{x=c-'0';while(d)p;if(c=='.'){DB l=1;while(d)pp;x*=l;}}
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
    printf("%d\n", x);
    //cout << x << endl;
    //last_ans = x;
}


//}/* .................................................................................................................................. */

const int N = int(2e5) + 9;
int n,Q;
int fa[N],id[N];
vector<pair<int,int> > q[N];


namespace SAM{
    const int Z = 26;
    int trans[N][Z], par[N], len[N], cnt[N], tot, tail;

#define v trans[u][c]
#define p par[u]
#define pp par[uu]

    inline int new_node(){
        RST(trans[tot]); //cnt[tot] = 0;
        return tot++;
    }

    inline int new_node(int u){
        CPY(trans[tot], trans[u]); par[tot] = par[u]; //cnt[tot] = cnt[u];
        return tot++;
    }

    inline int h(int u){
        return len[u] - len[p];
    }

    int Ext(int c){
        int u = tail, uu = new_node(); len[uu] = len[u] + 1;
        while (u && !v) v = uu, u = p; // 向上遍历没有 c-转移 的祖先 ..
        if (!u && !v) v = uu, pp = 0;
        else{
            if (len[v] == len[u] + 1) pp = v;
            else{
                int _v = v, vv = new_node(_v); len[vv] = len[u] + 1; par[_v] = pp = vv;
                while (u && v == _v) v = vv, u = p;
                if (!u && v == _v) v = vv;
            }
        }
        return tail = uu;
    }




#define c (s[i]-'a')


    char s[N]; VI adj[N];
    LL z;

#undef v

    void Init(){
        n = strlen(s); tot = 0; id[0] = tail = new_node();
        REP(i, n) id[i+1] = Ext(c)+1;
        FOR(u, 1, tot) fa[u+1] = p + 1;

        //cout << n << " " << tot << endl;

    }

#undef c
#undef p
#undef pp

}


struct Node{
	Node *fa,*c[2];
	int isr;
	bool getson(){return fa->c[0]!=this;}
	void rotate(){
		Node *y=fa,*z=y->fa;
		if (y->isr!=-1)
			isr=y->isr,y->isr=-1;
		else
			z->c[y->getson()]=this;
		int k=getson();
		fa=z;
		y->c[k]=c[k^1],c[k^1]->fa=y;
		c[k^1]=y,y->fa=this;
	}
	void splay(){
		for (;isr==-1;rotate())
			if (!fa->isr)
				getson()!=fa->getson()?rotate():fa->rotate();
	}
} d[N],*null,*rt;


namespace SGT{
	int tag[N*4],mx[N*4];
	void modify(int st,int en,int c,int k=1,int l=1,int r=n){
		if (c<=tag[k])
			return;
		if (st<=l && r<=en){
			tag[k]=c;
			mx[k]=max(max(mx[k<<1],mx[k<<1|1]),tag[k]-l);
			return;
		}
		int mid=l+r>>1;
		if (st<=mid) modify(st,en,c,k<<1,l,mid);
		if (mid<en) modify(st,en,c,k<<1|1,mid+1,r);
		mx[k]=max(max(mx[k<<1],mx[k<<1|1]),tag[k]-l);
	}
	int query(int st,int en,int k=1,int l=1,int r=n){
		if (st<=l && r<=en)
			return mx[k];
		int mid=l+r>>1,res=tag[k]-max(l,st);
		if (st<=mid) res=max(res,query(st,en,k<<1,l,mid));
		if (mid<en) res=max(res,query(st,en,k<<1|1,mid+1,r));
		return res;
	}
}
void modify(int i){
	Node *x=&d[id[i]],*y=null;

	//cout <<id[i] << endl;

	for (;x!=rt;y=x,x=x->fa){
		x->splay();
		if (x->isr){
			int l=SAM::len[x->fa-d-1]+1,r=SAM::len[x-d-1];

			//cout << i <<" " << l <<" " << r <<endl;

//			printf("%d %d %d\n",x->isr-r+1,x->isr-l+1,x->isr);
			SGT::modify(x->isr-r+1,x->isr-l+1,x->isr+1);
		}
		x->c[1]->isr=x->isr;
		x->c[1]=y;
		y->isr=-1;
		x->isr=i;
	}
}
int ans[N];
int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

	scanf("%d%d",&n,&Q);
	scanf("%s",SAM::s);
	for (int i=1;i<=Q;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		q[r].push_back({l,i});
	}
	SAM::Init();
	null=d;
	*null={null,null,null,-1};
	for (int i=1;i<=SAM::tot;++i) {
		d[i]={&d[fa[i]],null,null,0};
		        //cout << i << " "<< fa[i] << endl;

	}
	rt=&d[1];
	for (int i=1;i<=n;++i){
		modify(i);
		for (int j=0;j<q[i].size();++j){
			int l=q[i][j].fi;
			ans[q[i][j].se]=i-l+1-max(SGT::query(l,i),0);
		}
	}
	for (int i=1;i<=Q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
