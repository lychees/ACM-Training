#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)

class TellBagsApart {
	public:
	string whichBagIsSmaller(vector <int> records) {
		
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum) {
		switch (casenum) {
		case 0: {
			int records[]             = {262, 371, 340, 277, 303, 304, 333, 310, 296, 326, 370, 275, 312, 329, 284, 308, 265, 402, 372, 279, 279, 317, 307, 279, 112, 160, 121, 102, 497, 497, 505, 506};
			string expected__         = "1111";

			clock_t start__           = clock();
			string received__         = TellBagsApart().whichBagIsSmaller(vector <int>(records, records + (sizeof records / sizeof records[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int records[]             = {401, 405, 345, 358, 203, 295, 284, 209, 348, 380, 396, 361, 221, 274, 307, 213, 361, 347, 410, 347, 246, 287, 298, 204, 301, 389, 412, 304, 253, 289, 280, 272, 303, 450, 388, 290, 270, 286, 246, 267, 328, 354, 326, 362, 254, 305, 309, 262, 290, 362, 391, 296, 285, 282, 313, 281, 338, 335, 345, 335, 220, 338, 335, 254, 309, 356, 348, 323, 239, 344, 343, 238, 264, 368, 365, 258, 301, 312, 328, 304, 256, 368, 343, 295, 296, 323, 319, 300, 275, 318, 383, 258, 320, 340, 306, 300, 275, 301, 323, 309, 273, 372, 366, 281, 263, 331, 290, 309, 277, 358, 395, 277, 261, 310, 291, 259, 301, 407, 379, 292, 256, 318, 297, 257, 325, 358, 366, 323, 284, 287, 274, 286, 294, 406, 358, 311, 266, 271, 282, 256, 282, 395, 429, 319, 270, 274, 278, 268, 308, 396, 404, 302, 203, 283, 299, 229, 368, 401, 377, 340};
			string expected__         = "22211212211122212221";

			clock_t start__           = clock();
			string received__         = TellBagsApart().whichBagIsSmaller(vector <int>(records, records + (sizeof records / sizeof records[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 2: {
			int records[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TellBagsApart().whichBagIsSmaller(vector <int>(records, records + (sizeof records / sizeof records[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 3: {
			int records[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TellBagsApart().whichBagIsSmaller(vector <int>(records, records + (sizeof records / sizeof records[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int records[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TellBagsApart().whichBagIsSmaller(vector <int>(records, records + (sizeof records / sizeof records[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int records[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TellBagsApart().whichBagIsSmaller(vector <int>(records, records + (sizeof records / sizeof records[0])));
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
