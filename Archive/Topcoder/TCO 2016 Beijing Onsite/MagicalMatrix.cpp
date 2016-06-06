#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <set>
#include <map>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

#define ALL(A) A.begin(), A.end()
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define fi first
#define se second

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

template<class T> inline void checkMin(T &a, T b){if (b<a) a=b;}
template<class T> inline void checkMax(T &a, T b){if (b>a) a=b;}

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const int N = 50;
vector< pair<DB, DB> > L;

//(1-x1)y2+y1 < (1-x2)y1+y2
bool cmp(const pair<DB, DB> & a, const pair<DB, DB> & b){
    return (1-a.fi)*b.se+a.se < (1-b.fi)*a.se+b.se;
}

class MagicalMatrix {
public:
    double MagicalInspection(int n, int m, vector <int> prob) {
        
        L.clear();
        
        REP(i, m){
            vector<DB> t; REP(j, n) t.PB(prob[j*m+i]/100.);
            sort(t.begin(), t.end());
            
            DB p = 1, e = 0; REP(k, n){
                e += p*(1-t[k]) * (k+1);
                p *= t[k];
            }
            e += p*n;
            L.PB(MP(p, e));
        }
        
        sort(L.begin(), L.end(), cmp);
        reverse(L.begin(), L.end());
        
        DB z = 0; REP(i, m) z = (1-L[i].fi)*z + L[i].se;
        
        /*
         z1 = (1-x1)*z+y1
         z2 = (1-x2)*z+y2
         
         z12 = (x-x1)z2+y1
         z21 = (x-x2)z1+y2
         
         z12 < z21
         (1-x1)y2+y1 < (1-x2)y1+y2
         */
        
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
                int n                     = 1;
                int m                     = 1;
                int prob[]                = {50};
                double expected__         = 1.0;
                
                clock_t start__           = clock();
                double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int n                     = 1;
                int m                     = 1;
                int prob[]                = {99};
                double expected__         = 1.0;
                
                clock_t start__           = clock();
                double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int n                     = 2;
                int m                     = 2;
                int prob[]                = {50,50,50,50};
                double expected__         = 2.625;
                
                clock_t start__           = clock();
                double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int n                     = 2;
                int m                     = 3;
                int prob[]                = {1,1,1,1,1,1};
                double expected__         = 3.0296970101000005;
                
                clock_t start__           = clock();
                double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int n                     = 2;
                int m                     = 2;
                int prob[]                = {60,70,90,80};
                double expected__         = 2.382;
                
                clock_t start__           = clock();
                double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
            case 5: {
                int n                     = 10;
                int m                     = 10;
                int prob[]                =
                {41,42,43,44,45,51,52,53,54,55,
                    41,42,43,44,45,51,52,53,54,55,
                    41,42,43,44,45,51,52,53,54,55,
                    41,42,43,44,45,51,52,53,54,55,
                    41,42,43,44,45,51,52,53,54,55,
                    41,42,43,44,45,51,52,53,54,55,
                    55,54,53,52,51,41,42,43,44,45,
                    55,54,53,52,51,41,42,43,44,45,
                    55,54,53,52,51,41,42,43,44,45,
                    55,54,53,52,51,41,42,43,44,45};
                double expected__         = 0;
                
                clock_t start__           = clock();
                double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                /*      case 6: {
                 int n                     = ;
                 int m                     = ;
                 int prob[]                = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int n                     = ;
                 int m                     = ;
                 int prob[]                = ;
                 double expected__         = ;
                 
                 clock_t start__           = clock();
                 double received__         = MagicalMatrix().MagicalInspection(n, m, vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
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
