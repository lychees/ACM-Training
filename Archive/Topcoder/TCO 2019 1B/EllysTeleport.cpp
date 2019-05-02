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

const int N = 10009;

int dp[N]; int depth_in_stack[N], circle_start;
int h[N]; int P, Q, M, n;

int f(int x, int k = 1) {
    int &z = dp[x];
    depth_in_stack[x] = k++;
    if (z == -1) {
        int y = ((LL)h[x] * P + Q) % M;
        y = upper_bound(h, h+n, y) - h - 1;
        if (y == -1 || y == x) {
            z = 1;
        } else if (depth_in_stack[y]) {
            z = k - depth_in_stack[y];
            circle_start = y;
        } else {
            z = f(y, k);
            if (circle_start != -1) {
                if (circle_start == x) circle_start = -1;
            } else {
                ++z;
            }
        }
    }
    depth_in_stack[x] = 0;
    return z;
}

class EllysTeleport {
public:
    int getMax(int n, int H1, int A, int B, int P, int Q, int M) {
        ::M = M, ::P = P, ::Q = Q, ::n = n;
        h[0] = H1; FOR(i, 1, n) h[i] = ((LL)h[i-1] * A + B) % M;
        sort(h, h+n); RST(depth_in_stack); FLC(dp, -1); circle_start = -1;
        int z = 0; REP(i, n) checkMax(z, f(i));
        return z;
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
                int N                     = 11;
                int H1                    = 9;
                int A                     = 17;
                int B                     = 9;
                int P                     = 7;
                int Q                     = 13;
                int M                     = 23;
                int expected__            = 6;
                
                clock_t start__           = clock();
                int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int N                     = 8;
                int H1                    = 17;
                int A                     = 23;
                int B                     = 19;
                int P                     = 15;
                int Q                     = 28;
                int M                     = 43;
                int expected__            = 4;
                
                clock_t start__           = clock();
                int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int N                     = 15;
                int H1                    = 42;
                int A                     = 114;
                int B                     = 52;
                int P                     = 76;
                int Q                     = 1;
                int M                     = 131;
                int expected__            = 5;
                
                clock_t start__           = clock();
                int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int N                     = 10;
                int H1                    = 71;
                int A                     = 54;
                int B                     = 85;
                int P                     = 96;
                int Q                     = 52;
                int M                     = 100;
                int expected__            = 10;
                
                clock_t start__           = clock();
                int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int N                     = 1000;
                int H1                    = 1337;
                int A                     = 706135;
                int B                     = 1085680;
                int P                     = 1153206;
                int Q                     = 345473;
                int M                     = 1234567;
                int expected__            = 42;
                
                clock_t start__           = clock();
                int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                
                
                // custom cases
            case 5: {
                int N                     = 50;
                int H1                    = 24531490;
                int A                     = 180862451;
                int B                     = 30574576;
                int P                     = 182506777;
                int Q                     = 15198492;
                int M                     = 196140734;
                int expected__            = 14;
                
                clock_t start__           = clock();
                int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                /*      case 6: {
                 int N                     = ;
                 int H1                    = ;
                 int A                     = ;
                 int B                     = ;
                 int P                     = ;
                 int Q                     = ;
                 int M                     = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int N                     = ;
                 int H1                    = ;
                 int A                     = ;
                 int B                     = ;
                 int P                     = ;
                 int Q                     = ;
                 int M                     = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = EllysTeleport().getMax(N, H1, A, B, P, Q, M);
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
