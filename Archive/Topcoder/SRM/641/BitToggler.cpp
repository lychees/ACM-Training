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
#include <cassert>

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

const int MOD = 1000000007;
const int INF = 0x7fffffff;
const DB EPS = 1e-9;

inline int sgn(DB x){return x < -EPS ? -1 : x > EPS;}
inline int sgn(DB x, DB y){return sgn(x - y);}

/* -&$&#*( &#*@)^$@&*)*/

const int N = 109, M = N;
DB A[N][M], B[N];
int n;

void Gauss() {
    REP(i, n) {

        int ii = i;
        FOR(j, i+1, n) {
            if (fabs(A[j][i]) > fabs(A[ii][i])) {
                ii = j;
            }
        }
        if (ii != i) {
            REP(j, n) swap(A[i][j], A[ii][j]);
            swap(B[i], B[ii]);
        }

        DB &r = A[i][i]; assert(sgn(r));
        FOR(j, i+1, n) A[i][j] /= r;
        B[i] /= r; r = 1;

        REP(j, n) {
            if (i == j) continue;
            DB &r = A[j][i]; if (!sgn(r)) continue;
            FOR(k, i+1, n) A[j][k] -= A[i][k] * r;
            B[j] -= B[i] * r; r = 0;
        }
    }
}

int nn, cn;

// xi: The expectation times of pass in the end.
// c: How many outside points need to be toggle
// a: is b[i] != b[j]
// b: is current at i?

inline int g(int c,int a,int b) {
    return 2*(2*c + a)+ b;
}

DB gao(string b, int p) {
    DB z = 0; REP(i, nn) REP(j, nn) if (i != j) {
        int ci = 0;
        REP(k, nn) if (k != i && k != j) {
            if (b[i]^b[k]) ++ci;
        }
        z += B[g(ci,b[i]!=b[j],p==i)]*abs(i-j);
    }
    return z;
}

class BitToggler {
public:
	vector <double> expectation(int nn, vector <string> bits, vector <int> pos) {
	    ::nn = nn; cn = nn-2; n = g(cn, 1, 1)+1;
        RST(A); RST(B);

	    REP(c, cn+1) REP(a, 2) REP(b, 2) {
            int u = g(c,a,b); A[u][u] = nn;
            if (c || a) {
                if (b) B[u] = 1;
                if (c) A[u][g(c-1,a,0)] = -c;
                if (cn-c) A[u][g(c+1,a,0)] = -(cn-c);
                A[u][g(c,a^1,0)] = -1; // ->j
                A[u][g(cn-c,a^1,1)] = -1; // ->i
            }
	    }

	    /*REP(i, n) {
	        REP(j, n) cout << A[i][j] << " ";
	        cout << " = ";
	        cout << B[i] << endl;
	    }*/

	    if (cn >= 0) Gauss();
		vector <double> res; REP(i, SZ(pos)) res.PB(gao(bits[i], pos[i]));
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
	static bool topcoder_fequ(const vector<double> &a, const vector<double> &b) { if (a.size() != b.size()) return false; for (size_t i=0; i<a.size(); ++i) if (!topcoder_fequ(a[i], b[i])) return false; return true; }
	double moj_relative_error(const vector<double> &expected, const vector<double> &result) { double ret = 0.0; for (size_t i=0; i<expected.size(); ++i) { ret = max(ret, moj_relative_error(expected[i], result[i])); } return ret; }

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <double> &expected, const vector <double> &received, clock_t elapsed) {
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
			int n                     = 1;
			string bits[]             = {"0","1"};
			int pos[]                 = {0,0};
			double expected__[]       = {0.0, 0.0 };

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			string bits[]             = {"01"};
			int pos[]                 = {0};
			double expected__[]       = {0.5 };

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int n                     = 4;
			string bits[]             = {"1000","0010","0011","1010"};
			int pos[]                 = {0,1,2,3};
			double expected__[]       = {8.9375, 8.5625, 9.75, 10.25 };

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int n                     = 20;
			string bits[]             = {"01101111001001001111","01011100001001010111","00000000000000010000","10111111101111111011"
,"11101111111011010100","11111010110000000001","11000000100001100110","11111001010011101100"
,"11111111111111110111","01000011100010001000","01101111110111011111","11110111111111111110"
,"11111111111010110111","00100010000010000010","01000000000010000000","01110011111011000010"
,"11111101110001110111","11010010000000100000","10010101100000101000"};
			int pos[]                 = {7,6,1,1,7,9,0,8,16,16,14,4,9,8,11,3,12,15,11};
			double expected__[]       = {3695311.183337145, 3695341.038888902, 3486510.5078947134, 3690384.721723784, 3695146.5166465323, 3695333.788886834, 3695264.399989025, 3695310.983335239, 3486508.9763158862, 3695148.3166833473, 3693970.9054913437, 3670001.842105858, 3690381.122961273, 3693970.005510611, 3670000.4482457424, 3695335.888887129, 3694859.0889757653, 3694860.2888290025, 3695260.0000010678 };

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int n                     = ;
			string bits[]             = ;
			int pos[]                 = ;
			double expected__[]       = ;

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int n                     = ;
			string bits[]             = ;
			int pos[]                 = ;
			double expected__[]       = ;

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			string bits[]             = ;
			int pos[]                 = ;
			double expected__[]       = ;

			clock_t start__           = clock();
			vector <double> received__ = BitToggler().expectation(n, vector <string>(bits, bits + (sizeof bits / sizeof bits[0])), vector <int>(pos, pos + (sizeof pos / sizeof pos[0])));
			return verify_case(casenum, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
