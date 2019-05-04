#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (__typeof((A).begin()) it=(A).begin(); it != (A).end(); ++it)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;

template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}
template<class T> inline T ceil(T x, T y){return x ? (x - 1) / y + 1 : 0;}

// --------

const int N = int(51);

int dp[N][N];

int tri(int n){
    return n*(n+1)/2;
}

class BaronsAndCoins {
public:
	int getMaximum(vector <int> x, vector <int> y) {

        vector<pair<int, int> > I;
        int n = x.size(); REP(i, n) I.PB(MP(y[i], x[i])); I.PB(MP(0, 0));
        sort(I.begin(), I.end()); FLC(dp, 0x3f); dp[0][0] = 0;

#define u dp[i][j]
#define v dp[ii][j+1]

        int z = 0; REP(i, n+1) REP(j, i+1) if (u != INF){
            checkMax(z, j); FOR(ii, i+1, n+1){
                int dx = I[ii].se - I[i].se, dy = I[ii].fi - I[i].fi;  if (!dy) continue;
                int ddx = u*dy+tri(dy); if (ddx > dx) continue;
                checkMin(v, u+dy + ceil(dx-ddx, dy));
            }
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
			int x[]                   = {1445, 3071, 1985, 2623, 20, 2897, 2343, 928, 588, 2076, 93, 218, 650, 1660, 2759};
			int y[]                   = {30, 43, 35, 40, 3, 42, 38, 24, 19, 36, 7, 11, 20, 32, 41};
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {10};
			int y[]                   = {10};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {1, 3, 6, 10, 15, 21};
			int y[]                   = {1, 2, 3, 4, 5, 6};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {5, 10, 15, 20, 25, 30, 35, 40, 45};
			int y[]                   = {1, 1, 1, 2, 2, 2, 3, 3, 3};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {1, 3, 6, 10, 22, 35, 50, 66};
			int y[]                   = {1, 2, 3, 1, 2, 3, 4, 5};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BaronsAndCoins().getMaximum(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
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
