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
#include <queue>

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

const int N = 1009;

int Q[N], cz, op;
int in[N]; vector<int> adj[N];

class RankingStudents {
public:
    string rankingPossible(int n, vector <int> f, vector <int> a, vector <int> b) {
        
        RST(in);REP(i,n)adj[i].clear();
        REP(i, a.size()) {
            in[b[i]]++;
            adj[ a[i]] .PB(b[i] );
        }
        
        cz = 0, op = 0; REP(i, n)if(!in[i]) Q[op++]=i;
        while (cz < op) {
            int u = Q[cz++];
            for (auto v: adj[u]) if (!--in[v]) Q[op++]=v;
        }
        if (op != n) return "Impossible";
        DWN(i, n, 0) {
            int u = Q[i];
            for (auto v: adj[u]) checkMin(f[u], f[v]-1);
        }
        sort(ALL(f));
        REP(i, n) if (i > f[i]) return "Impossible";
        return "Possible";
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
                int n                     = 3;
                int f[]                   = {0, 1, 2};
                int a[]                   = {0, 1};
                int b[]                   = {2, 2};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int n                     = 3;
                int f[]                   = {2, 2, 2};
                int a[]                   = {0, 1, 2};
                int b[]                   = {1, 2, 0};
                string expected__         = "Impossible";
                
                clock_t start__           = clock();
                string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int n                     = 4;
                int f[]                   = {1, 1, 1, 3};
                int a[]                   = {1};
                int b[]                   = {3};
                string expected__         = "Impossible";
                
                clock_t start__           = clock();
                string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int n                     = 6;
                int f[]                   = {5, 5, 5, 1, 5, 4};
                int a[]                   = {0, 2, 4};
                int b[]                   = {1, 3, 5};
                string expected__         = "Possible";
                
                clock_t start__           = clock();
                string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 4: {
                 int n                     = ;
                 int f[]                   = ;
                 int a[]                   = ;
                 int b[]                   = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 5: {
                 int n                     = ;
                 int f[]                   = ;
                 int a[]                   = ;
                 int b[]                   = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 6: {
                 int n                     = ;
                 int f[]                   = ;
                 int a[]                   = ;
                 int b[]                   = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = RankingStudents().rankingPossible(n, vector <int>(f, f + (sizeof f / sizeof f[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
