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
#define SRT(A) sort(ALL(A))
#define SZ(A) int(A.size())
#define PB push_back

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}

const int N = 20;
DB dp[1<<N];

inline bool _1(int x, int i){return bool(x&1<<i);}
inline bool _1(LL x, int i){return bool(x&1LL<<i);}
inline LL _1(int i){return 1LL<<i;}
inline LL _U(int i){return _1(i) - 1;};

DB gao(vector<int> a) {
    int n = SZ(a);
    RST(dp); REP(s, _1(n)) {
        int choose = 0; bool bad = 0; REP(i, n) {
            if (a[i] == 0 && !_1(s, i)) {
                bad = 1;
                break;
            }
            choose += a[i] - (_1(s, i) ? 0 : 1);
        }
        if (bad) continue;
        
        DB stop = 0; REP(i, n) if (!_1(s, i)) stop += i;
        if (choose == 0) {
            dp[s] = stop;
            continue;
        }
        DB draw = 0; REP(i, n) {
            if (_1(s, i)) {
                draw += dp[s^_1(i)] * a[i];
            }
        }
        draw /= choose;
        dp[s] = max(stop, draw);
    }
    return dp[_U(n)];
}


class CardDrawPoints {
public:
    double expectedScore(vector <int> count) {
        
        return gao(count);
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
    
    static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
    double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
    
    int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) {
        cerr << "Example " << casenum << "... ";
        
        string verdict;
        vector<string> info;
        char buf[100];
        
        if (elapsed > CLOCKS_PER_SEC / 200) {
            sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
            info.push_back(buf);
        }
        
        if (topcoder_fequ(expected, received)) {
            verdict = "PASSED";
            double rerr = moj_relative_error(expected, received);
            if (rerr > 0) {
                sprintf(buf, "relative error %.3e", rerr);
                info.push_back(buf);
            }
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
                int count[]               = {0, 0};
                double expected__         = 0.0;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int count[]               = {1, 1};
                double expected__         = 1.0;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int count[]               = { 1, 1, 1 };
                double expected__         = 3.0;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int count[]               = { 1, 3 };
                double expected__         = 1.0;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int count[]               = {0, 4, 0, 0, 0, 1};
                double expected__         = 2.4000000000000004;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 5: {
                int count[]               = {0, 7, 0, 0, 0, 1};
                double expected__         = 1.625;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 6: {
                int count[]               = {0, 0, 0, 100000, 100000};
                double expected__         = 2.857142857142857;
                
                clock_t start__           = clock();
                double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 7: {
                 int count[]               = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 8: {
                 int count[]               = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 9: {
                 int count[]               = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = CardDrawPoints().expectedScore(vector <int>(count, count + (sizeof count / sizeof count[0])));
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
