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


class MedianFaking {
public:
	vector <int> minimize(int F, int M, vector <int> data, int goal) {

        int x = 0, y = 0;
        int a = 0, b = 0;
        vector<int> aa;
        vector<int> bb;
        REP(i, F) {
            aa.PB(0);
            bb.PB(0);
        }

        REP(i, F) {
            REP(j, M) {
                int d = data[i*M+j];
                if (d < goal) ++a, aa[i]++;
                if (d > goal) ++b, bb[i]++;
            }
        }
        int m = (F*M-1) / 2, l = F*M-m-1;
        int n1 = 0, n2 = 0;
        if (a > m) n1 = a - m, y += n1;
        if (b > l) n2 = b - l, y += n2;

        vector< vector<int> > dp;

        REP(i, n1+1) {
            vector<int> t; REP(j, n2+1) t.PB(INF);
            dp.PB(t);
        }
        dp[0][0] = 0;

        REP(ii, F) {
            if (aa[ii] || bb[ii]) {
                DWN(i, n1+1, 0) {
                    DWN(j, n2+1, 0) {
                        int u = dp[i][j];

                        checkMin(dp[ min(n1, i+aa[ii] ) ][ min(n2, j+bb[ii])],
                                 u + 1);
                        //cout << u << " " << dp[ min(n1, i+aa[ii] ) ][ min(n2, j+bb[ii])] << endl;
                    }
                }
            }
        }

        x = dp[n1][n2];

		vector <int> z;
        z.PB(x); z.PB(y);
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
			int F                     = 5;
			int M                     = 5;
			int data[]                = {1,2,3,4,5, 10,9,8,7,6, 25,24,23,22,21, 18,16,17,19,20, 11,13,12,14,15};
			int goal                  = 8;
			int expected__[]          = {1, 5 };

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int F                     = 5;
			int M                     = 5;
			int data[]                = {1,2,25,24,23, 3,4,22,21,20, 5,6,19,18,17, 7,16,15,14,13, 8,12,11,10,9};
			int goal                  = 8;
			int expected__[]          = {2, 5 };

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int F                     = 1;
			int M                     = 4;
			int data[]                = {10, 40, 30, 20};
			int goal                  = 20;
			int expected__[]          = {0, 0 };

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int F                     = 4;
			int M                     = 3;
			int data[]                = {3,8,12, 3,8,12, 3,8,12, 8,12,17};
			int goal                  = 12;
			int expected__[]          = {1, 2 };

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int F                     = 5;
			int M                     = 1;
			int data[]                = {10, 20, 30, 40, 50};
			int goal                  = 23;
			int expected__[]          = {1, 1 };

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int F                     = ;
			int M                     = ;
			int data[]                = ;
			int goal                  = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int F                     = ;
			int M                     = ;
			int data[]                = ;
			int goal                  = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int F                     = ;
			int M                     = ;
			int data[]                = ;
			int goal                  = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = MedianFaking().minimize(F, M, vector <int>(data, data + (sizeof data / sizeof data[0])), goal);
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
