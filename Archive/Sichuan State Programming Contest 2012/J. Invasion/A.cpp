/*
 This code has been written by MinakoKojima, fell free to ask me question. Blog: http://www.shuizilong.com/house
 Template Date: 2015.10.05
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
template<class T> inline void CLR(priority_queue<T, vector<T>, less<T> > &Q){while (!Q.empty()) Q.pop();}
template<class T> inline void CLR(priority_queue<T, vector<T>, greater<T> > &Q){while (!Q.empty()) Q.pop();}
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
template<class T, class C> inline T& SRT(T &A, C B){sort(ALL(A), B); return A;}
template<class T> inline T& RVS(T &A){reverse(ALL(A)); return A;}
template<class T> inline T& UNQQ(T &A){A.resize(unique(ALL(A))-A.begin());return A;}
template<class T> inline T& UNQ(T &A){SRT(A);return UNQQ(A);}


//}

/** Constant List .. **/ //{

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fLL;
const DB EPS = 1e-6;
const DB OO = 1e20;
const DB PI = acos(-1.0); //M_PI;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

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
// <<= '1. Bitwise Operation ., //{
namespace BO{
    
    inline bool _1(int x, int i){return bool(x&1<<i);}
    inline bool _1(LL x, int i){return bool(x&1LL<<i);}
    inline LL _1(int i){return 1LL<<i;}
    inline LL _U(int i){return _1(i) - 1;};
    
    inline int reverse_bits(int x){
        x = ((x >> 1) & 0x55555555) | ((x << 1) & 0xaaaaaaaa);
        x = ((x >> 2) & 0x33333333) | ((x << 2) & 0xcccccccc);
        x = ((x >> 4) & 0x0f0f0f0f) | ((x << 4) & 0xf0f0f0f0);
        x = ((x >> 8) & 0x00ff00ff) | ((x << 8) & 0xff00ff00);
        x = ((x >>16) & 0x0000ffff) | ((x <<16) & 0xffff0000);
        return x;
    }
    
    inline LL reverse_bits(LL x){
        x = ((x >> 1) & 0x5555555555555555LL) | ((x << 1) & 0xaaaaaaaaaaaaaaaaLL);
        x = ((x >> 2) & 0x3333333333333333LL) | ((x << 2) & 0xccccccccccccccccLL);
        x = ((x >> 4) & 0x0f0f0f0f0f0f0f0fLL) | ((x << 4) & 0xf0f0f0f0f0f0f0f0LL);
        x = ((x >> 8) & 0x00ff00ff00ff00ffLL) | ((x << 8) & 0xff00ff00ff00ff00LL);
        x = ((x >>16) & 0x0000ffff0000ffffLL) | ((x <<16) & 0xffff0000ffff0000LL);
        x = ((x >>32) & 0x00000000ffffffffLL) | ((x <<32) & 0xffffffff00000000LL);
        return x;
    }
    
    template<class T> inline bool odd(T x){return x&1;}
    template<class T> inline bool even(T x){return !odd(x);}
    template<class T> inline T low_bit(T x) {return x & -x;}
    template<class T> inline T high_bit(T x) {T p = low_bit(x);while (p != x) x -= p, p = low_bit(x);return p;}
    template<class T> inline T cover_bit(T x){T p = 1; while (p < x) p <<= 1;return p;}
    template<class T> inline int cover_idx(T x){int p = 0; while (_1(p) < x ) ++p; return p;}
    
    inline int clz(int x){return __builtin_clz(x);}
    inline int clz(LL x){return __builtin_clzll(x);}
    inline int ctz(int x){return __builtin_ctz(x);}
    inline int ctz(LL x){return __builtin_ctzll(x);}
    inline int lg2(int x){return !x ? -1 : 31 - clz(x);}
    inline int lg2(LL x){return !x ? -1 : 63 - clz(x);}
    inline int low_idx(int x){return !x ? -1 : ctz(x);}
    inline int low_idx(LL x){return !x ? -1 : ctz(x);}
    inline int high_idx(int x){return lg2(x);}
    inline int high_idx(LL x){return lg2(x);}
    inline int parity(int x){return __builtin_parity(x);}
    inline int parity(LL x){return __builtin_parityll(x);}
    inline int count_bits(int x){return __builtin_popcount(x);}
    inline int count_bits(LL x){return __builtin_popcountll(x);}
    
} using namespace BO;//}

// <<= '9. Comutational Geometry .,//{
namespace CG{
    
#define cPo const Po&
#define cLine const Line&
#define cSeg const Seg&
    
    inline DB dist2(DB x,DB y){return sqr(x)+sqr(y);}
    
    struct Po{
        DB x,y;Po(DB x=0,DB y=0):x(x),y(y){}
        
        void in(){RF(x,y);}void out(){printf("(%.2f,%.2f)",x,y);}
        inline friend istream&operator>>(istream&i,Po&p){return i>>p.x>>p.y;}
        inline friend ostream&operator<<(ostream&o,Po p){return o<<"("<<p.x<<", "<<p.y<< ")";}
        
        Po operator-()const{return Po(-x,-y);}
        Po&operator+=(cPo p){x+=p.x,y+=p.y;rTs;}Po&operator-=(cPo p){x-=p.x,y-=p.y;rTs;}
        Po&operator*=(DB k){x*=k,y*=k;rTs;}Po&operator/=(DB k){x/=k,y/=k;rTs;}
        Po&operator*=(cPo p){rTs=Ts*p;}Po&operator/=(cPo p){rTs=Ts/p;}
        Po operator+(cPo p)const{return Po(x+p.x,y+p.y);}Po operator-(cPo p)const{return Po(x-p.x,y-p.y);}
        Po operator*(DB k)const{return Po(x*k,y*k);}Po operator/(DB k)const{return Po(x/k,y/k);}
        Po operator*(cPo p)const{return Po(x*p.x-y*p.y,y*p.x+x*p.y);}Po operator/(cPo p)const{return Po(x*p.x+y*p.y,y*p.x-x*p.y)/p.len2();}
        
        bool operator==(cPo p)const{return!sgn(x,p.x)&&!sgn(y,p.y);};bool operator!=(cPo p)const{return sgn(x,p.x)||sgn(y,p.y);}
        bool operator<(cPo p)const{return sgn(x,p.x)<0||!sgn(x,p.x)&&sgn(y,p.y)<0;}bool operator<=(cPo p)const{return sgn(x,p.x)<0||!sgn(x,p.x)&&sgn(y,p.y)<=0;}
        bool operator>(cPo p)const{return!(Ts<=p);}bool operator >=(cPo p)const{return!(Ts<p);}
        
        DB len2()const{return dist2(x,y);}DB len()const{return sqrt(len2());}DB arg()const{return atan2(y,x);}
        Po&_1(){rTs/=len();}Po&conj(){y=-y;rTs;}Po&lt(){swap(x,y),x=-x;rTs;}Po&rt(){swap(x,y),y=-y;rTs;}
        Po&rot(DB a,cPo o=Po()){Ts-=o;Ts*=Po(cos(a),sin(a));rTs+=o;}
    };
    
    inline DB dot(DB x1,DB y1,DB x2,DB y2){return x1*x2+y1*y2;}
    inline DB dot(cPo a,cPo b){return dot(a.x,a.y,b.x,b.y);}
    inline DB dot(cPo p0,cPo p1,cPo p2){return dot(p1-p0,p2-p0);}
    inline DB det(DB x1,DB y1,DB x2,DB y2){return x1*y2-x2*y1;}
    inline DB det(cPo a,cPo b){return det(a.x,a.y,b.x,b.y);}
    inline DB det(cPo p0,cPo p1,cPo p2){return det(p1-p0,p2-p0);}
    inline DB ang(cPo p0,cPo p1){return acos(dot(p0,p1)/p0.len()/p1.len());}
    inline DB ang(cPo p0,cPo p1,cPo p2){return ang(p1-p0,p2-p0);}
    inline DB ang(cPo p0,cPo p1,cPo p2,cPo p3){return ang(p1-p0,p3-p2);}
    inline DB dist2(const Po &a, const Po &b){return dist2(a.x-b.x, a.y-b.y);}
    template<class T1, class T2> inline int dett(const T1 &x, const T2 &y){return sgn(det(x, y));}
    template<class T1, class T2, class T3> inline int dett(const T1 &x, const T2 &y, const T3 &z){return sgn(det(x, y, z));}
    template<class T1, class T2, class T3, class T4> inline int dett(const T1 &x, const T2 &y, const T3 &z, const T4 &w){return sgn(det(x, y, z, w));}
    template<class T1, class T2> inline int dott(const T1 &x, const T2 &y){return sgn(dot(x, y));}
    template<class T1, class T2, class T3> inline int dott(const T1 &x, const T2 &y, const T3 &z){return sgn(dot(x, y, z));}
    template<class T1, class T2, class T3, class T4> inline int dott(const T1 &x, const T2 &y, const T3 &z, const T4 &w){return sgn(dot(x, y, z, w));}
    template<class T1, class T2> inline DB arg(const T1 &x, const T2 &y){DB a=ang(x,y);return~dett(x,y)?a:2*PI-a;}
    template<class T1, class T2, class T3> inline DB arg(const T1 &x, const T2 &y, const T3 &z){DB a=ang(x,y,z);return~dett(x,y,z)?a:2*PI-a;}
    template<class T1, class T2, class T3, class T4> inline DB arg(const T1 &x, const T2 &y, const T3 &z, const T4 &w){DB a=ang(x,y,z,w);return~dett(x,y,z,w)?a:2*PI-a;}
    template<class T1, class T2> inline DB dist(const T1 &x, const T2 &y){return sqrt(dist2(x, y));}
    template<class T1, class T2, class T3> inline DB dist(const T1 &x, const T2 &y, const T3 &z){return sqrt(dist2(x, y, z));}
    inline Po _1(Po p){return p._1();}inline Po conj(Po p){return p.conj();}
    inline Po lt(Po p){return p.lt();}inline Po rt(Po p){return p.rt();}
    inline Po rot(Po p,DB a,cPo o=Po()){return p.rot(a,o);}
    inline Po operator *(DB k,cPo p){return p*k;}
    inline Po operator /(DB k,cPo p){return conj(p)*k/p.len2();}
    
    typedef vector<Po> VP;
    
    struct Line{
        Po a,b;Line(cPo a=Po(),cPo b=Po()):a(a),b(b){}
        Line(DB x0,DB y0,DB x1,DB y1):a(Po(x0,y0)),b(Po(x1,y1)){}
        Line(cLine l):a(l.a),b(l.b){}
        
        //Ax+By+C=0
        Line(DB A,DB B,DB C){
            C=-C;if(!::sgn(A))a=Po(0,C/B),b=Po(1,C/B);
            else if(!::sgn(B))a=Po(C/A,0),b=Po(C/A,1);
            else a=Po(0,C/B),b=Po(1,(C-A)/B);
        }
        
        void in(){a.in(),b.in();}
        inline friend istream&operator>>(istream&i,Line& p){return i>>p.a>>p.b;}
        inline friend ostream&operator<<(ostream&o,Line p){return o<<p.a<<"-"<< p.b;}
        
        Line operator+(cPo x)const{return Line(a+x,b+x);}
        Line operator-(cPo x)const{return Line(a-x,b-x);}
        Line operator*(DB k)const{return Line(a*k,b*k);}
        Line operator/(DB k)const{return Line(a/k,b/k);}
        
        Po operator*(cLine)const;
        Po d()const{return b-a;}DB len2()const{return d().len2();}DB len()const{return d().len();}DB arg()const{return d().arg();}
        
        int sgn(cPo p)const{return dett(a, b, p);}
        int sgn(cLine)const;
        
        bool sameSgn(cPo  p1,cPo  p2)const{return sgn(p1)==sgn(p2);}
        void getEquation(DB&K,DB&B)const{
            K = ::sgn(a.x, b.x) ? (b.y-a.y)/(b.x-a.x) : OO;
            B = a.y - K*a.x;
        }
        void getEquation(DB&A,DB&B,DB&C)const{A=a.y-b.y,B=b.x-a.x,C=det(a, b);}
        
        Line&push(DB r){ // ’˝ ˝”“ ÷¬›–˝œÚ¿Ô
            Po v=d()._1().lt()*r;a+=v,b+=v; rTs;
        }
    };
    
    inline DB dot(cLine l1,cLine l2){return dot(l1.d(),l2.d());}
    inline DB dot(cLine l,cPo p){return dot(l.a,l.b,p);}
    inline DB dot(cPo p,cLine l){return dot(p,l.a,l.b);}
    inline DB det(cLine l1,cLine l2){return det(l1.d(),l2.d());}
    inline DB det(cLine l,cPo p){return det(l.a,l.b,p);}
    inline DB det(cPo p,cLine l){return det(p,l.a,l.b);}
    inline DB ang(cLine l0,cLine l1){return ang(l0.d(),l1.d());}
    inline DB ang(cLine l,cPo p){return ang(l.a,l.b,p);}
    inline DB ang(cPo p,cLine l){return ang(p,l.a,l.b);}
    
    inline int Line::sgn(cLine l)const{return dett(Ts, l);}
    inline Po Line::operator*(cLine l)const{return a+d()*det(a,l)/det(Ts,l);}
    inline Po operator&(cPo p,cLine l){return l*Line(p,p+l.d().lt());}
    inline Po operator%(cPo p,cLine l){return p&l*2-p;}
    inline Line push(Line l, DB r){return l.push(r);}
    
    
    struct Seg: public Line{
        Seg(cPo a=Po(),cPo b=Po()):Line(a,b){}
        Seg(DB x0,DB y0,DB x1,DB y1):Line(x0,y0,x1,y1){}
        Seg(cLine l):Line(l){}
        Seg(const Po &a,DB alpha):Line(a,alpha){}
        Seg(DB A,DB B,DB C):Line(A,B,C){}
        
        inline int sgn(cPo p)const;
        inline int sgn(cLine l)const;
        inline bool qrt(cSeg l)const;
        inline int sgn(cSeg l)const;
    };
    
    // -1≤ªœ‡Ωª 0œ‡Ωª£®≤ªπÊ∑∂£© 1œ‡Ωª£®πÊ∑∂£©
    
    inline int Seg::sgn(cPo p)const{return -dott(p,a,b);}
    inline int Seg::sgn(cLine l)const{return sgn(Ts*l);}
    
    // quick_rejection_test
    inline bool Seg::qrt(cSeg l)const{
        return min(a.x,b.x)<=max(l.a.x,l.b.x)&&min(l.a.x,l.b.x)<=max(a.x,b.x)&&
        min(a.y,b.y)<=max(l.a.y,l.b.y)&&min(l.a.y,l.b.y)<=max(a.y,b.y);
    }
    
    
    inline int Seg::sgn(cSeg l)const{
        if (!qrt(l)) return -1;
        
        /*return
         (dett(a,b,l.a)*dett(a,b,l.b)<=0 &&
         dett(l.a,l.b,a)*dett(l.a,l.b,b)<=0)?1:-1;*/
        
        int d1=dett(a,b,l.a),d2=dett(a,b,l.b),d3=dett(l.a,l.b,a),d4=dett(l.a,l.b,b);
        if ((d1^d2)==-2&&(d3^d4)==-2)return 1;
        return ((!d1&&dott(l.a-a,l.a-b)<=0)||(!d2&&dott(l.b-a,l.b-b)<=0)||
                (!d3&&dott(a-l.a,a-l.b)<=0)||(!d4&&dott(b-l.a,b-l.b)<=0))?0:-1;
    }
    
    //inline DB dist2(cLine l,cPo p){return sqr(fabs(dot(lt(l.d()), p-l.a)))/l.len2();}
    inline DB dist2(cLine l,cPo p){return sqr(fabs(det(l.d(), p-l.a)))/l.len2();}
    
    inline DB dist2(cLine l1,cLine l2){return dett(l1,l2)?0:dist2(l1,l2.a);}
    
    inline DB dist2(cSeg l,cPo p){
        Po pa = p - l.a, pb = p - l.b;
        if (dott(l.d(), pa) <= 0) return pa.len2();
        if (dott(l.d(), pb) >= 0) return pb.len2();
        return dist2(Line(l), p);
    }
    
    
    inline DB dist2(cSeg s,cLine l){
        Po v1=s.a-l.a,v2=s.b-l.a;DB d1=det(l.d(),v1),d2=det(l.d(),v2);
        return sgn(d1)!=sgn(d2) ? 0 : sqr(min(fabs(d1), fabs(d2)))/l.len2();
    }
    inline DB dist2(cSeg l1,cSeg l2){
        if (~l1.sgn(l2)) return 0;
        else return min(dist2(l2,l1.a), dist2(l2,l1.b), dist2(l1,l2.a), dist2(l1,l2.b));
    }
    template<class T1, class T2> inline DB dist2(const T1& a, const T2& b){
        return dist2(b, a);
    }
    
    struct Triangle; struct Circle;
    typedef const Triangle&cTriangle; typedef const Circle&cCircle;
    
    const int Disjoint = -2, Exscribe = -1, Cross = 0, Inscribe = 1, Contain = 2;
    
    Po getX3(cPo a, cPo b, cPo c){ // Õ‚Ω”‘≤‘≤–ƒ
        Po v0=b-a,v1=c-a;DB l0=v0.len2(),l1=v1.len2(),d=2*det(a,b,c);
        return Po(l0*v1.y-l1*v0.y,l1*v0.x-l0*v1.x)/d+a;
        //Po v0 = b-a, v1 = c-a, m0 = (a+b)/2, m1 = (a+c)/2;
        //return Line(m0,m0+v0.lt())*Line(m1,m1+v1.lt());
    }
    
    
    
    
    Po getX4(cPo a, cPo b, cPo c){ // ¥π–ƒ // orthocenter
        return Line(a,a&Line(b,c))*Line(b,b&Line(a,c));
    }
    
    
    
    struct Circle{
        Po o; DB r; Circle(cPo o=Po(),DB r=0):o(o),r(r){}
        Circle(cPo a,cPo b):o((a+b)/2),r(dist(a,b)/2){}
        Circle(cLine l):Circle(l.a, l.b){}
        Circle(cPo a,cPo b,cPo c):o(getX3(a,b,c)),r(dist(o,a)){}
        
        void in(){o.in(),RF(r);}
        void out(){printf("%.2f %.2f %.2f\n", o.x, o.y, r);}
        
        bool operator <(cCircle c)const{return r<c.r;}
        //-1œ‡¿Î 0‘≤…œ 1∞¸∫¨
        inline int sgn(cPo p)const{return ::sgn(r*r, dist2(o, p));}
        //-1œ‡¿Î 0œ‡«– 1œ‡Ωª
        inline int sgn(cLine l)const{return ::sgn(r*r, dist2(l, o));}
        // -2Õ‚¿Î -1Õ‚«– 0œ‡Ωª 1ƒ⁄«– 2∞¸∫¨
        inline int sgn(cCircle c)const{
            DB d=dist2(o,c.o);
            if (::sgn(sqr(r+c.r),d)<0) return Disjoint;
            if (!::sgn(sqr(r+c.r), d)) return Exscribe;
            if (!::sgn(sqr(r-c.r), d)) return Inscribe;
            if (::sgn(sqr(r-c.r), d)>0) return Contain;
            return Cross;
        }
        
        inline DB getArea(){return PI*r*r;}
        inline DB getPeri(){return 2*PI*r;}
        
        inline void getIntersect(cLine l,Po&p0,Po&p1)const{
            Po m = o&l, d = (l.b-l.a)._1() * sqrt(sqr(r)-dist2(l, o));
            p0 = m + d, p1 = m - d;
        }
        inline void getIntersect(cCircle c,Po&p0,Po&p1)const{
            Po v=(c.o-o)._1()*r;DB a=acos(cos(r,dist(o,c.o),c.r));
            p0=o+rot(v,a),p1=o+rot(v,-a);
        }
        
        inline void getTangency(cPo p,Po&p0,Po&p1)const{
            DB d=dist(o,p),a=acos(r/d);Po v=(p-o)._1()*r;
            p0=o+rot(v,a),p1=o+rot(v,-a);
        }
        
        inline VP operator*(cLine l)const{
            VP P; int t = sgn(l); if (t==-1) return P;
            Po p0, p1; getIntersect(l, p0, p1); P.PB(p0); if (t == 1) P.PB(p1);
            return P;
        }
        
        inline VP operator*(cSeg s)const{
            VP _P = Ts*Line(s), P; ECH(p, _P) if (~s.sgn(*p)) P.PB((*p));
            return P;
        }
        
        inline Po operator^(cCircle c)const{return Po(det(Po(o.x,r),Po(c.o.x,c.r)),det(Po(o.y,r),Po(c.o.y,c.r)))/(c.r-r);}
        
        inline VP operator*(cCircle c)const{
            VP P; int t = abs(sgn(c)); if (t == 2) return P;
            Po p0, p1; getIntersect(c, p0, p1); P.PB(p0); if (!t) P.PB(p1);
            return P;
        }
    };
    
    Po getPo(){Po p;p.in();return p;}
    Line getLine(){Line l;l.in();return l;}
    
    DB getArea(const VP& P){DB z=0;FOR(i,1,SZ(P))z+=det(P[i-1],P[i]);return z;}
    DB getPeri(const VP& P){DB z=0;FOR(i,1,SZ(P))z+=dist(P[i-1],P[i]);return z;}
    
} using namespace CG;//}

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
    printf("Case #%d: ", ++Case);
    //printf("%lld\n", x);
    //printf("%.9f\n", x);
    printf("%d\n", x);
    //cout << x << endl;
    //last_ans = x;
}


//}/* .................................................................................................................................. */


const int N = int(5e2) + 9;


const double eps = 1e-6 , pi = acos(-1);
int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y;
    Point (double _x = 0 , double _y = 0) {
        x = _x;
        y = _y;
    }
    Point operator + (const Point &R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point &R) const {
        return Point(x - R.x , y - R.y);
    }
    double operator ^ (const Point &R) const {
        return x * R.y - y * R.x;
    }
    double operator % (const Point &R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
    Point operator * (const double& R) const{
        return Point(x * R , y * R);
    }
    void input() {
        scanf("%lf%lf" , &x , &y);
    }
};


struct Circle2 {
    Point O;
    double R;
    Circle2 (Point _O = Point() , double _R = 0) {
        O = _O;
        R = _R;
    }
    bool in(Point P) {
        return dcmp((P - O).len() - R) <= 0;
    }
};


double L;
int n , m , K , ca;
Point P[N][N] , Q;
int s[N];
Circle2 C[N];


double getLineCircleIntersection(Point p , Point v , Circle2 C) {
    double a = v.x , b = p.x - C.O.x , c = v.y , d = p.y - C.O.y;
    double e = a * a + c * c , f = 2 * (a * b + c * d) , g = b * b + d * d - C.R * C.R;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) <= 0) return 0;
    double t1 = (-f - sqrt(delta)) / (e + e);
    double t2 = (-f + sqrt(delta)) / (e + e);
    vector<double> V; V.push_back(t1); V.push_back(t2);
    V.push_back(0);  V.push_back(1);
    sort(V.begin() , V.end()); double res = 0;
    for (int i = 0 ; i + 1 < V.size() ; ++ i) {
        double w = (V[i] + V[i + 1]) * 0.5;
        if (dcmp(w) >= 0 && dcmp(w - 1) <= 0 && C.in(p + v * w))
            res += (v * (V[i + 1] - V[i])).len();
    }
    return res;
}
double Angle(Point V) {
    return atan2(V.y , V.x);
}
double getCircleCircleIntersection(Circle2 C1 , Circle2 C2) {
    double d = (C1.O - C2.O).len();
    if (dcmp(d) == 0) {
        if (dcmp(C1.R - C2.R) >= 0)
            return 2 * pi * C2.R;
        return 0;
    }
    if (dcmp(C1.R - C2.R) >= 0 && dcmp(C1.R - C2.R - d) >= 0) return 2 * pi * C2.R;
    if (dcmp(C1.R + C2.R - d) < 0) return 0;
    if (dcmp(fabs(C1.R - C2.R) - d) > 0) return 0;
    double a = Angle(C1.O - C2.O); // acos 内可能越界
    double w = (C2.R * C2.R + d * d - C1.R * C1.R) / (2 * C2.R * d);
    double da = acos(max(-1.0 , min(1.0 , w)));
    return C2.R * da * 2;
}
double cal(double R) {
    Circle2 A(Q , R);
    double res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        res += getCircleCircleIntersection(A , C[i]);
    }
    for (int i = 0 ; i < m ; ++ i) {
        for (int j = 0 ; j < s[i] ; ++ j) {
            Point p = P[i][j] , v = P[i][(j + 1) % s[i]];
            res += getLineCircleIntersection(p , v - p , A);
            //cout << getLineCircleIntersection(p , v - p , A) << endl;
        }
    }
    return res;
}

long double cal1(double R) {
    Circle2 A(Q , R);
    long double res = 0;
    for (int i = 0 ; i < n ; ++ i) {
        res += getCircleCircleIntersection(A , C[i]);
    }
    return res;
}

long double cal2(double R){
    Circle2 A(Q , R);
    long double res = 0;
    for (int i = 0 ; i < m ; ++ i) {
        for (int j = 0 ; j < s[i] ; ++ j) {
            Point p = P[i][j] , v = P[i][(j + 1) % s[i]];
            res += getLineCircleIntersection(p , v - p , A);
            //cout << getLineCircleIntersection(p , v - p , A) << endl;
        }
    }
    return res;
}



DB requiredPeri, totalPeri;

struct wall{
    VP P; Circle C;
    void in(){
        P.clear();
        if (RC() == 'C') C.in(), totalPeri += C.getPeri();
        else{
            Rush P.PB(getPo()); P.PB(P[0]);
            totalPeri += getPeri(P);
        }
    }
} W[N]; Po o;

DB insidePeri(Circle& C, wall& W){
    DB z = 0; if (!W.P.empty()){
        REP(i, W.P.size()-1){
            Seg l(W.P[i], W.P[i+1]); VP p = C*l;
            if (p.size() == 2){
                z += dist(p[0], p[1]);
            }
            else if (p.size() == 1){
                if (C.sgn(l.b) == 1) z += dist(l.b, p[0]);
                if (C.sgn(l.a) == 1) z += dist(l.a, p[0]);
            }
            else{
                if (C.sgn(l.a) == 1) z += dist(l.a, l.b);
            }
        }
    }
    else{
        int t = C.sgn(W.C);
        if (t <= Exscribe) return 0;
        if (t >= Inscribe) return W.C.getPeri();
        
        /*VP p = C*W.C; assert(p.size() == 2);
         p[0] -= W.C.o, p[1] -= W.C.o;
         if (dett(C.o, p[0]) == 1) swap(p[0], p[1]);
         return W.C.r * arg(p[0], p[1]);*/
        
        /*double ang=2*acos((sqr(b.r)+sqr(dist)-sqr(a.r))/(2*b.r*dist));
         return ang*b.r;
         */
        
        DB d = dist(W.C.o, C.o);
        DB ang = 2 * acos((sqr(W.C.r) + sqr(d) - sqr(C.r)) / (2*W.C.r*d));
        return ang * W.C.r;
    }
    return z;
}
DB f1(DB r){
    Circle C(o, r);
    DB z = 0; REP(i, K) if (!W[i].P.size()) z += insidePeri(C, W[i]);
    return z;
}
DB f2(DB r){
    Circle C(o, r);
    DB z = 0; REP(i, K) if (W[i].P.size()) z += insidePeri(C, W[i]);
    return z;
}


DB f(DB r){
        /*Circle C(o, r);
    DB z = 0; REP(i, K) z += insidePeri(C, W[i]);
    return z;*/
    
    assert(!sgn(cal(r), cal2(r)+cal1(r))  );
    
    long double z = cal(r); // cal2(r)+cal1(r) ;
    
    return z; //cal(r); / + cal2(r); //cal(r); // cal2(r) + cal1(r);
}


void work() {
    printf("Case #%d: " , ++ ca);
    scanf("%d" , &K);
    RF(requiredPeri); L = requiredPeri;
    
    totalPeri = 0;
    
    n = m = 0;
    for (int i = 0 ; i < K ; ++ i) {
        
        W[i].in();
        
        if (W[i].P.empty()){
            C[n].O.x = W[i].C.o.x;
            C[n].O.y = W[i].C.o.y;
            C[n].R = W[i].C.r;
            ++n;
        }
        else{
            s[m] = W[i].P.size()-1;
            for (int j = 0 ; j < s[m] ; ++ j){
                P[m][j].x = W[i].P[j].x;
                P[m][j].y = W[i].P[j].y;
            }
            ++ m;
        }
        
    }
    
    o.in();
    Q.x = o.x, Q.y = o.y;
    
    double l = 0 , r = 1e5 , mid;
    
//    cout << totalPeri << endl;
    
    if (!sgn(f(r) - requiredPeri)) {
        puts("inestimable");
        return;
    }
    
    for (int i = 0 ; i < 100 ; ++ i) {
        mid = 0.5 * (l + r);
        if (dcmp(f(mid) - L) <= 0)
            l = mid;
        else
            r = mid;
    }
    mid = l; double W = cal(mid);
    
    
    
    if (fabs(W - L) < 1e-6)
        printf("%.2f\n" , r);
    else {
        puts("impossible");
    }
}

int main() {
    
#ifndef ONLINE_JUDGE
    freopen("/users/xiaodao/desktop/Exercise/in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
