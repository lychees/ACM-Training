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

#define DO(n) for ( int ____n = n; ____n-->0; )
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

const int N = 5009;
int D[N];


class CircleCity {
public:
    int findMin(vector <int> dist, int k) {
        int n = dist.size();
        int l = 0, r = INF;
        while (l < r){
            int m = (l + r) / 2;
            bool ok = 0;
            REP(o, n){
                int i = o, c = 1, s = 0;
                DO(n-1){
                    s += dist[i];
                    if (s > m){
                        s = 0, ++c;
                        if (k < c) break;
                    }
                    ++i; if (i == n) i = 0;
                }
                if (c <= k){
                    ok = 1;
                    break;
                }
            }
            if (ok) r = m;
            else l = m + 1;
        }
        return l;
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
                int dist[]                = {3,5,4};
                int k                     = 2;
                int expected__            = 3;
                
                clock_t start__           = clock();
                int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int dist[]                = {3,5,4};
                int k                     = 3;
                int expected__            = 0;
                
                clock_t start__           = clock();
                int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int dist[]                = {1,2,3,4,5,6,5,4,3,2,1};
                int k                     = 5;
                int expected__            = 5;
                
                clock_t start__           = clock();
                int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int dist[]                = {1, 100, 1,1,1, 100, 1, 100, 1,1,1, 100, 1};
                int k                     = 4;
                int expected__            = 3;
                
                clock_t start__           = clock();
                int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int dist[]                = {3,1,4,1,5,9,2,6,5,3,5,8,9,7};
                int k                     = 6;
                int expected__            = 8;
                
                clock_t start__           = clock();
                int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 5: {
                int dist[]                = { 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000 };
                int k                     = 7;
                int expected__            = 9000000;
                
                clock_t start__           = clock();
                int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 6: {
                 int dist[]                = ;
                 int k                     = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int dist[]                = ;
                 int k                     = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 8: {
                 int dist[]                = ;
                 int k                     = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = CircleCity().findMin(vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), k);
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
