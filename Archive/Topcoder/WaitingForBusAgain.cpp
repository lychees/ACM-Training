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


class WaitingForBusAgain {
public:
	double expectedBus(vector <int> f) {	
		

		



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
			int f[]                   = {8,8,8,8};
			double expected__         = 1.5;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int f[]                   = {1,2,3};
			double expected__         = 0.5;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int f[]                   = {3,2,1};
			double expected__         = 1.5000000000000002;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int f[]                   = {3,1,4,1,5,9,2,6,5,3,5};
			double expected__         = 3.7044469870664325;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int f[]                   = {26, 19548, 19299, 19431, 39568, 19476, 19726, 19530, 19613, 19529, 19679, 19552, 19706, 19505, 19666, 19349, 19755, 19424, 19486, 19596, 19439, 19500, 19639, 19520, 19472, 19675, 19602, 19552, 19933, 19424, 19316, 19497, 19582, 19531, 19679, 19742, 19896, 19365, 20083, 19542, 19827, 19583, 19592, 19593, 19661, 19340, 19403, 19664, 19690, 19655, 19727, 19661, 19528, 19836, 19819, 19414, 19770, 19500, 19653, 19613, 19579, 19794, 19668, 19729, 19428, 19477, 19733, 19641, 19680, 19594, 19667, 19878, 19571, 19627, 19576, 19422, 19521, 19512, 19481, 19620, 19364, 19487, 19740, 19627, 19795, 19353, 19251, 19865, 19710, 19597, 19610, 19710, 19491, 19598, 19650, 19828, 19726, 19810, 19766, 19692} ;
			double expected__         = 3.1415926535671885;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int f[]                   = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int f[]                   = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int f[]                   = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = WaitingForBusAgain().expectedBus(vector <int>(f, f + (sizeof f / sizeof f[0])));
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
