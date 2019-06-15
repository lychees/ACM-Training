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

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

template<class T> inline void checkMin(T &a, T b){if (b<a) a=b;}
template<class T> inline void checkMax(T &a, T b){if (b>a) a=b;}

/* -&$&#*( &#*@)^$@&*)*/

const int MOD = 1000000007;
const int INF = 0x7fffffff;
#define Ts *this
#define rTs return Ts

// <<= '2. Number Theory .,//{
namespace NT{
    
    inline void INC(int &a, int b){a += b; if (a >= MOD) a -= MOD;}
    inline int sum(int a, int b){a += b; if (a >= MOD) a -= MOD; return a;}
    
    /* 模数两倍刚好超 int 时。
     inline int sum(uint a, int b){a += b; a %= MOD;if (a < 0) a += MOD; return a;}
     inline void INC(int &a, int b){a = sum(a, b);}
     */
    
    inline void DEC(int &a, int b){a -= b; if (a < 0) a += MOD;}
    inline int dff(int a, int b){a -= b; if (a < 0) a  += MOD; return a;}
    inline void MUL(int &a, int b){a = (LL)a * b % MOD;}
    //inline int pdt(int a, int b){return (LL)a * b % MOD;}
    inline int pdt(int x,int y) {
        int ret; __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
        return ret;
    }
    
    
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

const int N = int(2e5) + 9;
LL A[N];



class TheUnexpectedSwap {
public:
    int findExpectedResult(int digits, string prefN, int seed) {
        string N;
        A[0] = seed;
        FOR(i, 1, digits) {
            A[i] = (A[i-1] * 1009  + 10009) % 100019;
        }
        N = prefN;
        FOR(i, prefN.size(), digits) {
            N += N[A[i]  % i];
        }
        
        //  cout << N << endl;
        
        Int s = 0, b = 1;
        REP(i, digits) {
            s += N[i]-'0';
        }
        
        
        Int n = digits;
        // n  * (n-1)
        // (n-1) * (n-2)
        // (n-1) + (n-1)
        
        Int z = 0, bb = 1;
        
        
        DWN(i, digits, 0) {
            Int ss = s; ss -= N[i]-'0';
            z += (Int)(N[i]-'0') * bb * (n-1) * (n-2); // 没选到
            z += ss * bb  * 2; // 选到
            // //           cout << ss << " " << bb << endl;
            
            
            // cout << z << " " << ss << " " << bb << endl;
            bb *= 10;
            
        }
        
        return int(z);
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
    
    int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
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
                int digits                = 2;
                string prefN              = "32";
                int seed                  = 0;
                int expected__            = 46;
                
                clock_t start__           = clock();
                int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int digits                = 2;
                string prefN              = "60";
                int seed                  = 0;
                int expected__            = 12;
                
                clock_t start__           = clock();
                int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int digits                = 10;
                string prefN              = "1";
                int seed                  = 0;
                int expected__            = 999999297;
                
                clock_t start__           = clock();
                int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int digits                = 6;
                string prefN              = "123";
                int seed                  = 47;
                int expected__            = 5331084;
                
                clock_t start__           = clock();
                int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 4: {
                 int digits                = ;
                 string prefN              = ;
                 int seed                  = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 5: {
                 int digits                = ;
                 string prefN              = ;
                 int seed                  = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 6: {
                 int digits                = ;
                 string prefN              = ;
                 int seed                  = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = TheUnexpectedSwap().findExpectedResult(digits, prefN, seed);
                 return verify_case(casenum, expected__, received__, clock()-start__);
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
