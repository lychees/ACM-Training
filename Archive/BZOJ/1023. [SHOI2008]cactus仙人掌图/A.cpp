#include <bits/stdc++.h>

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
const int INF = 0x3f3f3f3f;

const int N = 50;


class WaterTank {
public:
    double minOutputRate(vector <int> t, vector <int> x, int C) {
        
        int l = 0, r = C;
        while (l < r){
            int m = l + r >> 1;
            
            bool ok = true;
            int cur = 0;
            REP(i, t.size()){
                cur += (x[i]-m) * t[i];
                if (cur < 0) cur = 0;
                if (cur > C) ok = false;
            }
            
            if (ok) r = m;
            else l = m + 1;
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
                int t[]                   = {3,3};
                int x[]                   = {1,2};
                int C                     = 3;
                double expected__         = 0.9999999999999999;
                
                clock_t start__           = clock();
                double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int t[]                   = {1,2,3,4,5};
                int x[]                   = {5,4,3,2,1};
                int C                     = 10;
                double expected__         = 1.9999999999999996;
                
                clock_t start__           = clock();
                double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int t[]                   = {5949,3198,376,3592,4019,3481,5609,3840,6092,4059};
                int x[]                   = {29,38,96,84,10,2,39,27,76,94};
                int C                     = 1000000000;
                double expected__         = 0.0;
                
                clock_t start__           = clock();
                double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int t[]                   = {9,3,4,8,1,2,5,7,6};
                int x[]                   = {123,456,789,1011,1213,1415,1617,1819,2021};
                int C                     = 11;
                double expected__         = 2019.1666666666665;
                
                clock_t start__           = clock();
                double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int t[]                   = {100};
                int x[]                   = {1000};
                int C                     = 12345;
                double expected__         = 876.55;
                
                clock_t start__           = clock();
                double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 5: {
                 int t[]                   = ;
                 int x[]                   = ;
                 int C                     = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 6: {
                 int t[]                   = ;
                 int x[]                   = ;
                 int C                     = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int t[]                   = ;
                 int x[]                   = ;
                 int C                     = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
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
