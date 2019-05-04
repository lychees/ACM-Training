#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <queue>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

#define ALL(A) A.begin(), A.end()
#define PB push_back
#define MP(A, B) make_pair(A, B)

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

template<class T> inline void checkMin(T &a, T b){if (b<a) a=b;}
template<class T> inline void checkMax(T &a, T b){if (b>a) a=b;}

const int MOD = 1000000007;
const int INF = 0x7fffffff;

const int N = 2509;

int dp[N][N];
int S[2][N];
int n, m;

int t(char c){
    if (c == '(') return 1;
    return -1;
}

inline int sum(int a, int b){a += b; if (a >= MOD) a -= MOD; return a;}


class InterleavingParenthesis {
public:
    int countWays(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        
        S[0][0] = t(s1[0]);
        S[1][0] = t(s2[0]);
        FOR(i, 1, n) S[0][i] = S[0][i-1] + t(s1[i]);
        FOR(i, 1, m) S[1][i] = S[1][i-1] + t(s2[i]);
        
        if (S[0][n-1] + S[1][m-1] != 0){
            return 0;
        }
        
        RST(dp); dp[0][0] = 1;
        
        FOR(i, 0, n+1) FOR(j, 0, m+1) if ( (i || j) && (S[0][i-1] + S[1][j-1]) >= 0 ){
            dp[i][j] = sum( (i ? dp[i-1][j] : 0), (j ? dp[i][j-1] : 0));
        }
        
        return dp[n][m];
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
                string s1                 = "(";
                string s2                 = "(";
                int expected__            = 19;
                
                clock_t start__           = clock();
                int received__            = InterleavingParenthesis().countWays(s1, s2);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                string s1                 = ")";
                string s2                 = "(";
                int expected__            = 1;
                
                clock_t start__           = clock();
                int received__            = InterleavingParenthesis().countWays(s1, s2);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                string s1                 = "(((((";
                string s2                 = ")))))";
                int expected__            = 42;
                
                clock_t start__           = clock();
                int received__            = InterleavingParenthesis().countWays(s1, s2);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                string s1                 = "()(()";
                string s2                 = "))((())";
                int expected__            = 10;
                
                clock_t start__           = clock();
                int received__            = InterleavingParenthesis().countWays(s1, s2);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                string s1                 = "()()()()()()()()()()()()()()()()()()()()";
                string s2                 = "()()()()()()()()()()()()()()()()()";
                int expected__            = 487340184;
                
                clock_t start__           = clock();
                int received__            = InterleavingParenthesis().countWays(s1, s2);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 5: {
                string s1                 = "(())())))";
                string s2                 = "(())()";
                int expected__            = 0;
                
                clock_t start__           = clock();
                int received__            = InterleavingParenthesis().countWays(s1, s2);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 6: {
                 string s1                 = ;
                 string s2                 = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = InterleavingParenthesis().countWays(s1, s2);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 string s1                 = ;
                 string s2                 = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = InterleavingParenthesis().countWays(s1, s2);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 8: {
                 string s1                 = ;
                 string s2                 = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = InterleavingParenthesis().countWays(s1, s2);
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
