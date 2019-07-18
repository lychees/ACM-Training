/* &*#()&*#)&E*F& */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

#define ALL(A) A.begin(), A.end()
#define CLR(A) A.clear()
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define INS(A, P, B) A.insert(A.begin() + P, B)
#define ERS(A, P) A.erase(A.begin() + P)
#define SRT(A) sort(ALL(A))
#define SZ(A) int(A.size())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define Ts *this
#define rTs return Ts
template<class T> inline T min(T a, T b, T c){return min(min(a, b), c);}
template<class T> inline T max(T a, T b, T c){return max(max(a, b), c);}
template<class T> inline T min(T a, T b, T c, T d){return min(min(a, b), min(c, d));}
template<class T> inline T max(T a, T b, T c, T d){return max(max(a, b), max(c, d));}
template<class T> inline T min(T a, T b, T c, T d, T e){return min(min(min(a,b),min(c,d)),e);}
template<class T> inline T max(T a, T b, T c, T d, T e){return max(max(max(a,b),max(c,d)),e);}
typedef long long LL;
typedef double DB;
const DB OO = 1e20;
const DB EPS = 1e-9;
template<class T> inline T sqr(T a){return a*a;}
inline int sgn(DB x){return x < -EPS ? -1 : x > EPS;}
inline int sgn(DB x, DB y){return sgn(x - y);}
const DB PI = acos(-1.0); //M_PI;

// <<= '9. Comutational Geometry .,//{
namespace CG{

#define cPo const Po&
#define cLine const Line&
#define cSeg const Seg&
inline int sgn(DB x){return x < -EPS ? -1 : x > EPS;}
inline int sgn(DB x, DB y){return sgn(x - y);}
    inline DB dist2(DB x,DB y){return sqr(x)+sqr(y);}

    struct Po{
        DB x,y;Po(DB x=0,DB y=0):x(x),y(y){}

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

class CutCutCut {
public:
	vector <int> findPieces(vector <int> X1, vector <int> Y1, vector <int> X2, vector <int> Y2, int Q) {

		vector <int> res;
		int z = 1;
		REP(i, Q) {
		    ++z;
		    REP(j, i) if (Seg(X1[i], Y1[i], X2[i], Y2[i]).sgn(
                        Seg(X1[j], Y1[j], X2[j], Y2[j])) > 0 ) ++z;
            res.PB(z);
		}

		return res;
	}
};


// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			int X1[]                  = {1, 2, 3};
			int Y1[]                  = {0, 0, 0};
			int X2[]                  = {1, 2, 3};
			int Y2[]                  = {10000, 10000, 10000};
			int Q                     = 3;
			int expected__[]          = {2, 3, 4 };

			clock_t start__           = clock();
			vector <int> received__   = CutCutCut().findPieces(vector <int>(X1, X1 + (sizeof X1 / sizeof X1[0])), vector <int>(Y1, Y1 + (sizeof Y1 / sizeof Y1[0])), vector <int>(X2, X2 + (sizeof X2 / sizeof X2[0])), vector <int>(Y2, Y2 + (sizeof Y2 / sizeof Y2[0])), Q);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int X1[]                  = {0, 5000};
			int Y1[]                  = {5000, 10000};
			int X2[]                  = {10000, 5000};
			int Y2[]                  = {5000, 0};
			int Q                     = 2;
			int expected__[]          = {2, 4 };

			clock_t start__           = clock();
			vector <int> received__   = CutCutCut().findPieces(vector <int>(X1, X1 + (sizeof X1 / sizeof X1[0])), vector <int>(Y1, Y1 + (sizeof Y1 / sizeof Y1[0])), vector <int>(X2, X2 + (sizeof X2 / sizeof X2[0])), vector <int>(Y2, Y2 + (sizeof Y2 / sizeof Y2[0])), Q);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int X1[]                  = {1,0,3,9997};
			int Y1[]                  = {0,1,0,10000};
			int X2[]                  = {1,10000,0,10000};
			int Y2[]                  = {10000,1,3,9997};
			int Q                     = 4;
			int expected__[]          = {2, 4, 7, 8 };

			clock_t start__           = clock();
			vector <int> received__   = CutCutCut().findPieces(vector <int>(X1, X1 + (sizeof X1 / sizeof X1[0])), vector <int>(Y1, Y1 + (sizeof Y1 / sizeof Y1[0])), vector <int>(X2, X2 + (sizeof X2 / sizeof X2[0])), vector <int>(Y2, Y2 + (sizeof Y2 / sizeof Y2[0])), Q);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int X1[]                  = ;
			int Y1[]                  = ;
			int X2[]                  = ;
			int Y2[]                  = ;
			int Q                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = CutCutCut().findPieces(vector <int>(X1, X1 + (sizeof X1 / sizeof X1[0])), vector <int>(Y1, Y1 + (sizeof Y1 / sizeof Y1[0])), vector <int>(X2, X2 + (sizeof X2 / sizeof X2[0])), vector <int>(Y2, Y2 + (sizeof Y2 / sizeof Y2[0])), Q);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 4: {
			int X1[]                  = ;
			int Y1[]                  = ;
			int X2[]                  = ;
			int Y2[]                  = ;
			int Q                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = CutCutCut().findPieces(vector <int>(X1, X1 + (sizeof X1 / sizeof X1[0])), vector <int>(Y1, Y1 + (sizeof Y1 / sizeof Y1[0])), vector <int>(X2, X2 + (sizeof X2 / sizeof X2[0])), vector <int>(Y2, Y2 + (sizeof Y2 / sizeof Y2[0])), Q);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int X1[]                  = ;
			int Y1[]                  = ;
			int X2[]                  = ;
			int Y2[]                  = ;
			int Q                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = CutCutCut().findPieces(vector <int>(X1, X1 + (sizeof X1 / sizeof X1[0])), vector <int>(Y1, Y1 + (sizeof Y1 / sizeof Y1[0])), vector <int>(X2, X2 + (sizeof X2 / sizeof X2[0])), vector <int>(Y2, Y2 + (sizeof Y2 / sizeof Y2[0])), Q);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
