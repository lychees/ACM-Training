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

const int N = int(51), M = 5;

int F[N][4*N+1][M];
vector<int> P; int n, P0;

int f(int k = 0, int win = 4, int draw = 0){ //

    //cout << k << " " << win << " " << draw << endl;

    int& z = F[k][win+N][draw];

    if (z == -1){
        if (abs(win)+draw > 4*(n-k)) return z = INF;
        if (k == n) z = 0;
        else{
            z = INF; REP(w, 4+1) REP(d1, min(4-w, draw)+1) REP(d2, 4-w-d1+1){
                int d = d1+d2, l = 4-w-d;
                checkMin(z, (P[k]+3*w+d>P0) + f(k+1, win+w-l, (draw-d1+d2)%5));
            }
        }
    }
    return z;
}

class TheSoccerDivOne {
public:
	int find(vector <int> points) {
	    FLC(F, -1); P = points; P0 = P[0] + 3*4; P.erase(P.begin()); n = P.size();
		return 1 + f();
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
			int points[]              =
			{371241, 711629, 902119, 662373, 993265, 69513, 405770, 190751, 936619, 860997, 134189, 474073, 804541, 979506, 615219, 370429, 391025, 85236, 727579, 982251, 869479, 524737, 987917, 315149, 152311, 859640, 474687, 534711, 703685, 430121, 304961, 807552, 683399, 133376, 968733, 381357, 218042, 474297, 15466, 129476, 205865, 807493, 205601, 403321, 220263, 255901, 245756};

			//{5, 17};
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int points[]              = {5, 18, 21, 19};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int points[]              = {4, 1, 5};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int points[]              = {4, 16, 4, 16, 16};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int points[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int points[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int points[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheSoccerDivOne().find(vector <int>(points, points + (sizeof points / sizeof points[0])));
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
