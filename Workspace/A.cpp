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


        // 求所在象限，大部分情况下只区分两个足够。
        inline int q()const{
            return (y > 0 || y == 0 && x >= 0) ? 0 : 1;
            /*if (x > 0 && y >= 0) return 0;
             if (x <= 0 && y > 0) return 1;
             if (x < 0 && y <= 0) return 2;
             return 3;*/
        }
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

        Line&push(DB r){ // 正数右手螺旋向里
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

    // -1不相交 0相交（不规范） 1相交（规范）

    //inline int Seg::sgn(cPo p)const{return -dott(p,a,b);}

    inline int Seg::sgn(cPo p)const{
        if (dett(p, a, b)) return -1; // 有时会有精度误差。。
        if (a == p || b == p) return 0;
        return -dott(p,a,b);
    }


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
    //printf("Case #%d: ", ++Case);
    //printf("%lld\n", x);
    //printf("%I64d\n", x);
    //printf("%.9f\n", x);
    //printf("%d\n", x);
    cout << x << endl;
    //last_ans = x;
}


//}/* .................................................................................................................................. */

const int N = int(2e5) + 9;

namespace DSU{ // Disjoint Set Union
    int P[N], R[N], C[N], n;
    inline void Make(int x){
        P[x] = x, R[x] = 0, C[x] = 1;
    }
    inline int Find(int x){
        return P[x] == x ? x : P[x] = Find(P[x]);
    }
    inline void Unionn(int x, int y){
        if (R[x] == R[y]) ++R[x];
        else if (R[x] < R[y]) swap(x, y);
        C[x] += C[y];
        P[y] = x;
    }
    inline void Union(int x, int y){
        x = Find(x), y = Find(y);
        if (x != y) Unionn(x, y);
    }
    inline void Init(){
        REP_1(i, n) Make(i);
    }
} using namespace DSU;

char s[109];
VI adj[N]; int col[N];

bool dfs(int u, int& a, int& b) {



    if (col[u] == 1) a += C[u]; else b += C[u];

    //cout << u << " " << C[u] << " " << a << " " << b <<endl;
#define v Find(_v)
    for (auto _v: adj[u]) if (!col[v]) {
        col[v] = -col[u];
        if (!dfs(v,a,b)) return 0;
    } else if (col[v] == col[u]) {
        return 0;
    }
#undef v
    return 1;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif

    Rush {
        int m; RD(n, m); Init();
        REP_1(i, n) adj[i].clear(), col[i] = 0;
        DO(m) {
            int a, b; RD(a, b); RS(s);
            if (s[0] == 'i') {
                adj[a].PB(b);
                adj[b].PB(a);
            } else {
                Union(a, b);
            }
        }

        REP_1(_i, n) {
            int i = Find(_i);
            if (i != _i) {
                for (auto v: adj[_i]) adj[i].PB(v);
            }
        }

        int z = 0;
        REP_1(_i, n) {
            int i = Find(_i); if (!col[i]) {
                int a = 0, b = 0;
                col[i] = 1;
                if (!dfs(i,a,b)) {
                    z = -1;
                    break;
                }
                //cout <<z <<" " << a << " " <<b <<endl;
                z += max(a, b);
            }
        }
        cout << z <<endl;
    }


}
