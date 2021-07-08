#include <bits/stdc++.h>
using namespace std;
const int N = 51;
int s[N], a[N];
int n;

string f(int a1) {
    string z; a[1] = a1;
    for (int i=2;i<=n;++i) {
        a[i] = s[i-1]-a[i-1]-a[i-2];
        if (a[i] < 0) return "NONE";
    }
    if (a[n]+a[n-1]!=s[n]) return "NONE";
    for (int i=1;i<=n;++i) z += '0'+a[i];
    return z;
}

using namespace std;
class BinaryCode {
	public:
	vector <string> decode(string message) {
	    n = message.size(); for (int i=1;i<=n;++i) s[i] = message[i-1]-'0';
        vector<string> z;
        z.push_back(f(0));
        z.push_back(f(1));
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
	template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) {
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
			string message            = "123210122";
			string expected__[]       = { "011100011",  "NONE" };

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string message            = "11";
			string expected__[]       = { "01",  "10" };

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string message            = "22111";
			string expected__[]       = { "NONE",  "11001" };

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string message            = "123210120";
			string expected__[]       = { "NONE",  "NONE" };

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string message            = "3";
			string expected__[]       = { "NONE",  "NONE" };

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			string message            = "12221112222221112221111111112221111";
			string expected__[]       = { "01101001101101001101001001001101001",  "10110010110110010110010010010110010" };

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string message            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string message            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			string message            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 9: {
			string message            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = BinaryCode().decode(message);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
