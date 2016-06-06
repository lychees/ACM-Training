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
map<int, int> H;

class GroupSRMDiv2 {
public:
    int FindGroups(vector <int> t) {
        H.clear(); ECH(it, t) H[*it]++;
        
        int z = 0; ECH(it, H){
            int a = it->fi, b = it->se;
            if (b % a) return -1;
            z += b / a;
        }
        
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
                int t[]                   = {1,1};
                int expected__            = 2;
                
                clock_t start__           = clock();
                int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int t[]                   = {1,2};
                int expected__            = -1;
                
                clock_t start__           = clock();
                int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int t[]                   = {2,2};
                int expected__            = 1;
                
                clock_t start__           = clock();
                int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int t[]                   = {2,2,3,3,3};
                int expected__            = 2;
                
                clock_t start__           = clock();
                int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int t[]                   = {3,3,2,2,2};
                int expected__            = -1;
                
                clock_t start__           = clock();
                int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 5: {
                int t[]                   = {2,3,2,3,2,3,2,1,1,2,2};
                int expected__            = 6;
                
                clock_t start__           = clock();
                int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 6: {
                 int t[]                   = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int t[]                   = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 8: {
                 int t[]                   = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = GroupSRMDiv2().FindGroups(vector <int>(t, t + (sizeof t / sizeof t[0])));
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
