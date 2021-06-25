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


class InsidePoints {
public:
	vector <int> construct(vector <int> x, vector <int> y) {	
		

		



		vector <int> res = 0;

		
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
			int x[]                   = {4};
			int y[]                   = {7};
			int expected__[]          = {3, 7, 4, 8, 5, 6 };

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {4, 6};
			int y[]                   = {7, 7};
			int expected__[]          = {3, 6, 7, 6, 7, 8, 5, 7, 3, 8 };

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {1, 1, 2, 2};
			int y[]                   = {1, 2, 1, 2};
			int expected__[]          = {0, 0, 3, 0, 3, 3, 0, 3 };

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {1, 2, 3, 3, 3, 3, 5, 4};
			int y[]                   = {3, 3, 1, 5, 2, 4, 3, 3};
			int expected__[]          = {0, 2, 2, 2, 2, 0, 4, 0, 4, 2, 6, 2, 6, 4, 4, 4, 4, 6, 2, 6, 2, 4, 3, 3, 1, 4, 0, 4 };

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = InsidePoints().construct(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
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
