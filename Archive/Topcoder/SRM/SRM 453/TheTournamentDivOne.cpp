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

typedef long long LL;
typedef double DB;

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;

template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

// --------

const int N = int(50) + 9;
int d0[N];
int n;

class TheTournamentDivOne {
public:
	int find(vector <int> p, int w, int d) {
	    int wsum = 0, dsum = 0, lcm = w * d / __gcd(w, d); n = p.size(); REP(i, n){
            int ww = 0; while (p[i]-ww*w>=0 && (p[i]-ww*w)%d)++ww; if (p[i]-ww*w<0) return -1;
            d0[i] = (p[i]-ww*w) / d;
            wsum += ww; dsum += d0[i];
	    }

	    d = lcm / d; w = lcm / w;

	    //REP(i, n) cout << d0[i] << " "; cout << endl;

	    int z = INF; while(true){
            int t = 0; FOR(i, 1, n) if (d0[i] > d0[t]) t = i;
            if (!(dsum&1) && 2*d0[t] <= dsum) checkMin(z, wsum + dsum/2);
            d0[t] -= d; dsum -= d; wsum += w; if (d0[t] < 0) break;
	    };

	    if (z == INF) z = -1;
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
			int points[]              = {10, 1, 1};
			int w                     = 2;
			int d                     = 1;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int points[]              = {1, 1, 1};
			int w                     = 2;
			int d                     = 1;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int points[]              = {1, 4, 0, 2};
			int w                     = 3;
			int d                     = 1;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int points[]              = {8, 3, 8, 5, 9, 2, 7, 11};
			int w                     = 3;
			int d                     = 2;
			int expected__            = 15;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int points[]              = ;
			int w                     = ;
			int d                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int points[]              = ;
			int w                     = ;
			int d                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int points[]              = ;
			int w                     = ;
			int d                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTournamentDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])), w, d);
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
