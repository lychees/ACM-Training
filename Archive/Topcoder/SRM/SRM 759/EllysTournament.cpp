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
const int INF = 0x3f3f3f3f;

const int N = 50;


class EllysTournament {
public:
	double getChance(int N, int K, vector <int> ratings) {	
		

		



		double res = 0;

		
		return res;
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
			int N                     = 4;
			int K                     = 2;
			int ratings[]             = {2103, 2019, 1911, 2331};
			double expected__         = 0.17753927527829697;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 12;
			int K                     = 6;
			int ratings[]             = {42, 88, 13, 11, 71, 55, 32, 13, 72, 53, 37, 50};
			double expected__         = 0.06697114679670368;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 20;
			int K                     = 13;
			int ratings[]             = {1543, 1230, 421, 1415, 1271, 1962, 2677, 2373, 2951, 114, 1379, 2015, 2211, 955, 2066, 2573, 2982, 296, 1730, 1591};
			double expected__         = 0.05017297846158086;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 100;
			int K                     = 42;
			int ratings[]             = {2750, 2877, 2224, 186, 1398, 1084, 1542, 2770, 2288, 1078, 373, 2417, 476, 2968, 564, 1565, 1740, 1377, 2633, 287, 111, 823, 578, 520, 1708, 174, 144, 1295, 694, 678, 227, 2588, 371, 2740, 211, 1798, 82, 2385, 2979, 389, 2031, 1667, 2541, 2561, 1471, 2562, 974, 577, 286, 2836, 120, 2290, 185, 554, 2549, 1410, 1814, 1508, 2559, 1806, 2215, 1606, 2637, 1394, 1583, 1491, 2908, 529, 2556, 1034, 2770, 750, 2866, 2590, 1156, 2646, 2536, 958, 2862, 2565, 1027, 2744, 1160, 276, 2080, 322, 92, 790, 2452, 1859, 602, 2935, 2392, 1076, 2991, 1158, 2721, 868, 112, 29};
			double expected__         = 0.003026484586204139;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int K                     = ;
			int ratings[]             = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int K                     = ;
			int ratings[]             = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int K                     = ;
			int ratings[]             = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = EllysTournament().getChance(N, K, vector <int>(ratings, ratings + (sizeof ratings / sizeof ratings[0])));
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
