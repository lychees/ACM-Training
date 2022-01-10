#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <numeric>
#include <bitset>
#include <ctime>
#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)

using namespace std;

const int N = int(1e3) + 9;
vector<int> A, B, C;
int oa[N], ob[N], oc[N];
bool sa[N];
int n,NA,NB,NC;

template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}
template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}

int dfs(int a, int b, int aa, int bb) {

    if (a == NA && b == NB) {
        int z = 0, c = 0;
        if (c < NC) {
            REP(i, n) if (!sa[oc[i]]){
                z += C[oc[i]];
                ++c;
                if (c == NC) break;
            }
        }
        //cout << z << endl;
        return z;
    }

    int z = 0;
    if (a < NA) {
        FOR(i, aa, n) {
            sa[oa[i]] = true;
            checkMax(z, dfs(a+1, b, i+1, b) + A[oa[i]]);
            sa[oa[i]] = false;
        }
    } else if (b < NB) {
        FOR(i, bb, n)  if (!sa[ob[i]]){
            sa[ob[i]] = true;
            checkMax(z, dfs(a, b+1, aa, i+1) + B[ob[i]]);
            sa[ob[i]] = false;
        }
    }


    return z;
}

class SelectFromArrays {
	public:
	int maxSum(vector <int> A, vector <int> B, vector <int> C, int NA, int NB, int NC) {

	    n = A.size();
	    ::A=A;::B=B;::C=C;
	    ::NA = NA;
	    ::NB = NB;
	    ::NC = NC;

	    REP(i, n) oa[i] = ob[i] = oc[i] = i;
	    sort(oa, oa+n, [&](int x, int y){
          return A[x] > A[y];
        });
        sort(ob, ob+n, [&](int x, int y){
          return B[x] > B[y];
        });
        sort(oc, oc+n, [&](int x, int y){
          return C[x] > C[y];
        });

        checkMin(n, NA+NB+NC);

		return dfs(0,0,0,0);
	}
};

// 1 1 1 1 1
//   1   1    1   1 1
//            1     1      1        1 1

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
			int A[]                   = {1, 1, 1, 1, 1, 1, 1, 1};
			int B[]                   = {1, 1, 1, 1, 1, 1, 1, 1};
			int C[]                   = {1, 1, 1, 1, 1, 1, 1, 1};
			int NA                    = 2;
			int NB                    = 1;
			int NC                    = 2;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int A[]                   = {10, 20, 30, 40, 50};
			int B[]                   = {10, 20, 50, 40, 30};
			int C[]                   = {20, 50, 10, 40, 30};
			int NA                    = 1;
			int NB                    = 1;
			int NC                    = 1;
			int expected__            = 150;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int A[]                   = {0, 0, 0, 0, 0, 0, 47, 53};
			int B[]                   = {0, 0, 0, 0, 0, 0, 47, 53};
			int C[]                   = {0, 0, 0, 0, 0, 0, 47, 53};
			int NA                    = 2;
			int NB                    = 3;
			int NC                    = 2;
			int expected__            = 100;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int A[]                   = {10, 11, 12, 13, 15, 15, 16, 17, 18, 19};
			int B[]                   = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
			int C[]                   = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
			int NA                    = 2;
			int NB                    = 2;
			int NC                    = 2;
			int expected__            = 160;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int A[]                   = {10, 20, 30};
			int B[]                   = {60, 50, 40};
			int C[]                   = {70, 90, 80};
			int NA                    = 0;
			int NB                    = 1;
			int NC                    = 0;
			int expected__            = 60;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int A[]                   = ;
			int B[]                   = ;
			int C[]                   = ;
			int NA                    = ;
			int NB                    = ;
			int NC                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int A[]                   = ;
			int B[]                   = ;
			int C[]                   = ;
			int NA                    = ;
			int NB                    = ;
			int NC                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int A[]                   = ;
			int B[]                   = ;
			int C[]                   = ;
			int NA                    = ;
			int NB                    = ;
			int NC                    = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SelectFromArrays().maxSum(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])), NA, NB, NC);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

int main(){
	moj_harness::run_test(-1);
}
// END CUT HERE

