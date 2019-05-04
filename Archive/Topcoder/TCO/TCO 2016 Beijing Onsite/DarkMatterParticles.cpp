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

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

template<class T> inline void checkMin(T &a, T b){if (b<a) a=b;}
template<class T> inline void checkMax(T &a, T b){if (b>a) a=b;}

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

const int N = 1009;


namespace DSU{ // Disjoint Set Union
    int P[N], R[N], n;
    inline void Make(int x){
        P[x] = x, R[x] = 1;
    }
    inline int Find(int x){
        return P[x] == x ? x : P[x] = Find(P[x]);
    }
    inline void Unionn(int x, int y){
        R[x] += R[y];
        P[y] = x;
    }
    inline void Union(int x, int y){
        x = Find(x), y = Find(y);
        if (x != y) Unionn(x, y);
    }
    inline void Init(){
        REP(i, n) Make(i);
    }
} using namespace DSU;


bool dp[N];

class DarkMatterParticles {
public:
    string SplitParticles(int n, int k, vector <int> x, vector <int> y) {
        
        int m = x.size(); ::n = n;
        
        RST(dp); Init(); REP(i, m) Union(x[i], y[i]);
        
        dp[0] = 1;
        REP(i, n) if (P[i] == i){
            DWN(j, k+1,  R[i]) if (dp[j-R[i]]) dp[j] = 1;
        }
        
        return dp[k] ? "Possible" : "Impossible";
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
    
    int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
            cerr << "    Expected: \"" << expected << "\"" << endl;
            cerr << "    Received: \"" << received << "\"" << endl;
        }
        
        return verdict == "PASSED";
    }
    
    int run_test_case(int casenum) {
        switch (casenum) {
            case 0: {
                int n                     = 4;
                int k                     = 2;
                int x[]                   = {0,1,2,3};
                int y[]                   = {1,2,3,0};
                string expected__         = "Impossible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int n                     = 4;
                int k                     = 4;
                int x[]                   = {0,1,2,3};
                int y[]                   = {1,2,3,0};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int n                     = 4;
                int k                     = 2;
                int x[]                   = {0,1,2,3};
                int y[]                   = {2,3,0,1};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int n                     = 4;
                int k                     = 3;
                int x[]                   = {0,1,2,3};
                int y[]                   = {2,3,0,1};
                string expected__         = "Impossible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int n                     = 3;
                int k                     = 3;
                int x[]                   = {0,1,2};
                int y[]                   = {1,2,0};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 5: {
                int n                     = 3;
                int k                     = 2;
                int x[]                   = {0,1,2};
                int y[]                   = {1,2,0};
                string expected__         = "Impossible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 6: {
                int n                     = 6;
                int k                     = 1;
                int x[]                   = {0,1,4};
                int y[]                   = {1,2,5};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 7: {
                int n                     = 6;
                int k                     = 2;
                int x[]                   = {0,1,4};
                int y[]                   = {1,2,5};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 8: {
                int n                     = 6;
                int k                     = 3;
                int x[]                   = {0,1,4};
                int y[]                   = {1,2,5};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 9: {
                int n                     = 6;
                int k                     = 6;
                int x[]                   = {0,1,4};
                int y[]                   = {1,2,5};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 10: {
                 int n                     = ;
                 int k                     = ;
                 int x[]                   = ;
                 int y[]                   = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 11: {
                 int n                     = ;
                 int k                     = ;
                 int x[]                   = ;
                 int y[]                   = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 12: {
                 int n                     = ;
                 int k                     = ;
                 int x[]                   = ;
                 int y[]                   = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = DarkMatterParticles().SplitParticles(n, k, vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
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
