#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

int p[10] = {2,3,5,7,11};
vector<int> z;

void dfs(int k, int t, int d) {
    if (k == 5 && !t) {
        z.push_back(47);
        z.push_back(d);
    }
    if (k < 5) {
        dfs(k+1, t, d);
        if (t) dfs(k+1, t-1, d*p[k]);
    }
}

void dfs2(int k, int t, int d) {
    if (k == 5 && !t) {
        z.push_back(1);
        z.push_back(d);
    }
    if (k < 5) {
        dfs2(k+1, t, d);
        if (t) dfs2(k+1, t-1, d*p[k]);
    }
}

class IOIWeirdModel2 {
	public:
	vector <int> program(int L) {
        z.clear();
      //  dfs(0,5,1);
    //    dfs(0,4,1);
  //      dfs(0,3,1);
//        dfs2(0,1,1);

        z = {625, 252, 25, 84, 25, 126, 5, 42, 1, 2, 1, 3, 1, 7 };

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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) {
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
			int L                     = 2;
			int expected__[]          = {625, 252, 25, 84, 25, 126, 5, 42, 1, 2, 1, 3, 1, 7 };

			clock_t start__           = clock();
			vector <int> received__   = IOIWeirdModel2().program(L);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 1: {
			int L                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIWeirdModel2().program(L);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 2: {
			int L                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIWeirdModel2().program(L);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 3: {
			int L                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIWeirdModel2().program(L);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 4: {
			int L                     = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIWeirdModel2().program(L);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
