#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

const int N= int (1e3);

int D[N][N], A[N][N];
int n;

bool ok(int x) {
    for (int i=0;i<n;++i) {
         if (D[x][i] < D[i][x] ) return false;
    }
    return 1;
}

class IOIVoting {
	public:
	vector <int> winners(int N, vector <int> votes) {
	    n = N;
        vector<int> z;

        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j) {
                D[i][j] = votes[i*n+j] - votes[j*n+i];
                if (D[i][j] <= 0) D[i][j] = 0x3f3f3f3f;
            }

                    for (int i=0;i<n;++i){
                for (int j=0;j<n;++j) {
                if (D[i][j]==0x3f3f3f3f) D[i][j] = 0;
                 //   cout << D[i][j] << " ";
                }
                //cout << endl;
                         }


        for (int k=0;k<n;++k)
            for (int i=0;i<n;++i) {
                for (int j=0;j<n;++j) {
                    if (max(D[i][k], D[k][j]) != 0x3f3f3f3f)
                        D[i][j] = max(D[i][j], min(D[i][k], D[k][j]));
                }
            }


                for (int i=0;i<n;++i){
                for (int j=0;j<n;++j) {
                if (D[i][j]==0x3f3f3f3f) D[i][j] = 0;
                 //   cout << D[i][j] << " ";
                }
                cout << endl;
                         }

        for (int i=0;i<n;++i) {
            if (ok(i)) z.push_back(i);
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
			int N                     = 5;
			int votes[]               = { 0, 20, 26, 30, 22, 25, 0, 16, 33, 18, 19, 29, 0, 17, 24, 15, 12, 28, 0, 14, 23, 27, 21, 31, 0 };
			int expected__[]          = {4 };

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int votes[]               = {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0};
			int expected__[]          = {0, 1, 2, 3 };

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int N                     = 1;
			int votes[]               = {0};
			int expected__[]          = {0 };

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int N                     = 4;
			int votes[]               = { 0, 10, 11, 12, 13, 0, 14, 15, 97, 98, 0, 99, 16, 17, 18, 0};
			int expected__[]          = {2 };

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int N                     = 5;
			int votes[]               = { 0, 0, 0, 0, 0, 3, 0, 3, 99, 3, 0, 0, 0, 0, 0, 4, 99, 5, 0, 6, 0, 0, 0, 0, 0};
			int expected__[]          = {1, 3 };

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int N                     = 3;
			int votes[]               = {0, 1, 0, 0, 0, 1, 1, 0, 0};
			int expected__[]          = {0, 1, 2 };

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int votes[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int votes[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int votes[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 9: {
			int N                     = ;
			int votes[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = IOIVoting().winners(N, vector <int>(votes, votes + (sizeof votes / sizeof votes[0])));
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
