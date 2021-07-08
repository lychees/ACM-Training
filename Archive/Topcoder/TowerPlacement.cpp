#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)

class TowerPlacement {
	public:
	int solve(int R, int C, int seed, int X) {
		
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
			int R                     = 1;
			int C                     = 1;
			int seed                  = 47;
			int X                     = 5;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int R                     = 3;
			int C                     = 3;
			int seed                  = 47;
			int X                     = 4;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int R                     = 10000;
			int C                     = 14700;
			int seed                  = 12345;
			int X                     = 1;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int R                     = 10;
			int C                     = 12;
			int seed                  = 123456789;
			int X                     = 3;
			int expected__            = 19;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int R                     = ;
			int C                     = ;
			int seed                  = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int R                     = ;
			int C                     = ;
			int seed                  = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int R                     = ;
			int C                     = ;
			int seed                  = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int R                     = ;
			int C                     = ;
			int seed                  = ;
			int X                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TowerPlacement().solve(R, C, seed, X);
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
