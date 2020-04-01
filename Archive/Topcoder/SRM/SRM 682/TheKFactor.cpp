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
const int INF = 0x7fffffff;

const int N = 50;


class TheKFactor {
public:
	double expectedScore(vector <int> values) {	
		

		



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
			int values[]              = {1, 2, 3, 4, 5};
			double expected__         = 3.0;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int values[]              = {5, 9, 0, 34};
			double expected__         = 8.777778;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int values[]              = {10000, 0, 100};
			double expected__         = 10000.0;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int values[]              = {4374, 5909, 7194, 8367, 1328, 9373, 6067, 7097, 7631, 4841, 2584, 6877, 9775, 2831, 1916, 3253, 8670, 736, 9016, 825, 5002, 8739, 3735, 3262, 5050, 2146, 9273, 5163, 4015, 3174, 1424, 7716, 4162, 9960, 1880, 4320, 7047, 3253, 8702};
			double expected__         = 8352.585573;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int values[]              = {4814, 4710, 5035, 4513, 5046, 4381, 5402, 4372, 6113, 4354, 6205, 4271, 6517, 3989, 6804, 3533, 6811, 3032, 7138, 2848, 7277, 2574, 7278, 2456, 7345, 2239, 7417, 2035, 7519, 1977, 7802, 1920, 8449, 1336, 8612, 1233, 9264, 902, 9284, 690, 9558, 408, 9608, 208, 9661, 139, 9797, 127, 9910, 99};
			double expected__         = 6077.793513;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 5: {
			int values[]              = {0};
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int values[]              = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int values[]              = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int values[]              = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheKFactor().expectedScore(vector <int>(values, values + (sizeof values / sizeof values[0])));
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
