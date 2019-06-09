/* &*#()&*#)&E*F& */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>

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
const DB EPS = 1e-9;
inline int sgn(DB x){return x < -EPS ? -1 : x > EPS;}
inline int sgn(DB x, DB y){return sgn(x - y);}
/* -&$&#*( &#*@)^$@&*)*/

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

const int N = 109, M = N;
DB A[N][M], B[N];
int n;

void Gauss() {
    REP(i, n) {

        int ii = i;
        FOR(j, i+1, n) {
            if (fabs(A[j][i]) > fabs(A[ii][i])) {
                ii = j;
            }
        }
        if (ii != i) {
            REP(j, n) swap(A[i][j], A[ii][j]);
            swap(B[i], B[ii]);
        }

        DB &r = A[i][i]; assert(sgn(r));
        FOR(j, i+1, n) A[i][j] /= r;
        B[i] /= r; r = 1;

        REP(j, n) {
            if (i == j) continue;
            DB &r = A[j][i]; if (!sgn(r)) continue;
            FOR(k, i+1, n) A[j][k] -= A[i][k] * r;
            B[j] -= B[i] * r; r = 0;
        }
    }
}

class SlightlyBigger {
public:
	double getProbability(int maxDiff, int ifNear, int ifFar, int query) {
	    n = maxDiff * 2 + 1; if (query > n) return 0;
        REP(i, n-1) {
            RST(A[i]); B[i] = 0;
            FOR(j, i+1, min(i+maxDiff+1, n)) A[i][j] = ifNear;
            FOR(j, i+maxDiff+1, n) A[i][j] = -ifFar;
            DWN(j, i, max(i-maxDiff, 0)) A[i][j] = -ifNear;
            DWN(j, i-maxDiff, 0) A[i][j] = ifFar;
        }
        REP(i, n) A[n-1][i] = 1; B[n-1] = 1;
        Gauss();
		return B[query-1];
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
			int maxDiff               = 1;
			int ifNear                = 1;
			int ifFar                 = 1;
			int query                 = 1;
			double expected__         = 0.3333333333333334;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int maxDiff               = 1;
			int ifNear                = 1;
			int ifFar                 = 1;
			int query                 = 470;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int maxDiff               = 1;
			int ifNear                = 1;
			int ifFar                 = 2;
			int query                 = 1;
			double expected__         = 0.25;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int maxDiff               = 3;
			int ifNear                = 4;
			int ifFar                 = 7;
			int query                 = 3;
			double expected__         = 0.08005718370264478;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int maxDiff               = ;
			int ifNear                = ;
			int ifFar                 = ;
			int query                 = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int maxDiff               = ;
			int ifNear                = ;
			int ifFar                 = ;
			int query                 = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int maxDiff               = ;
			int ifNear                = ;
			int ifFar                 = ;
			int query                 = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = SlightlyBigger().getProbability(maxDiff, ifNear, ifFar, query);
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
