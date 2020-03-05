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
#include<set>

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

const int N = 50;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b,a%b);
}


class NonSimilarTriangles {
public:
    int count(vector <int> L) {
        
        SRT(L);
        //        L.erase(unique(ALL(L)), L.end());
        set< pair<int, pair<int, int > > > H;
        
        
        int n = L.size();
        REP(i, n) FOR(j,i+1,n) FOR(k,j+1,n) {
            int a = L[i], b=L[j],c=L[k];
            if (a + b <= c) continue;
            int d=gcd(gcd(a,b),c);
            a /=d, b/=d,c/=d;
            H.insert(MP(a, MP(b,c)));
        }
        
        return SZ(H);
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
                int L[]                   = {3,4,5};
                int expected__            = 1;
                
                clock_t start__           = clock();
                int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int L[]                   = {1,1,1,1,1,1};
                int expected__            = 1;
                
                clock_t start__           = clock();
                int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int L[]                   = {2,2,2,3,3,3};
                int expected__            = 3;
                
                clock_t start__           = clock();
                int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int L[]                   = {1,2,4,8,16,24};
                int expected__            = 0;
                
                clock_t start__           = clock();
                int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int L[]                   = {10,3,10,4,10,5,10,6,10,7,10,8,10,9};
                int expected__            = 50;
                
                clock_t start__           = clock();
                int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 5: {
                int L[]                   = {5, 5, 10};
                int expected__            = 0;
                
                clock_t start__           = clock();
                int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 6: {
                 int L[]                   = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int L[]                   = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 8: {
                 int L[]                   = ;
                 int expected__            = ;
                 
                 clock_t start__           = clock();
                 int received__            = NonSimilarTriangles().count(vector <int>(L, L + (sizeof L / sizeof L[0])));
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
