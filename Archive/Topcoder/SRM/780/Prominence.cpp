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
#define REP_1(i, n) for (int i=1;i<=n;++i)
#define FOR_1(i, a, b) for (int i=a;i<=b;++i)
#define DWN_1(i, b, a) for (int i=b;i>=a;--i)


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
inline int clz(int x){return __builtin_clz(x);}
inline int lg2(int x){return !x ? -1 : 31 - clz(x);}

const int N = int(1e6)+9, LV = 21;
int h[N], l[N], r[N], sta[N], top;
int n;

int ST[LV][N];

int rmq(int l, int r){
    int lv = lg2(r-l);
    return min(ST[lv][l], ST[lv][r-(1<<lv)]);
}

class Prominence {
public:
	long long sumOfProminences(int n, vector <int> coef, vector <int> idx, vector <int> val) {
        h[0] = h[n+3] = INF; h[1] = h[n+2] = 0; REP(i, n) {
            int p = i&1; LL a = coef[3*p], b = coef[3*p+1], c = coef[3*p+2];
            h[i+2] = (((a*i+b)%MOD)*i+c)%MOD;
        }
        REP(i, SZ(idx)) h[idx[i]+2] = val[i]; n += 2;

        sta[top = 0] = 0; REP_1(i, n) {
            while (h[sta[top]] <= h[i]) --top;
            l[i] = sta[top]; sta[++top] = i;
        }
        sta[top = 0] = n+1; DWN_1(i, n, 1) {
            while (h[sta[top]] <= h[i]) --top;
            r[i] = sta[top]; sta[++top] = i;
        }

        REP_1(i, n) ST[0][i] = h[i];
        for ( int lv = 1 ; (1 << lv) <= n ; lv ++ ){
            for ( int i = 1; i + (1 << lv)  <= n + 1 ; i ++ ){
                ST[lv][i] = min(ST[lv-1][i], ST[lv-1][i + (1<<(lv-1))]);
            }
        }

		long long z = 0;
		REP_1(i, n) if (h[i-1] < h[i] && h[i] > h[i+1]) {
		    z += h[i] - max(rmq(l[i]+1, i), rmq(i+1, r[i]));
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

	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) {
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
			int N                     = 7;
			int coef[]                = {0, 0, 47, 0, 0, 47};
			int idx[]                 = {};
			int val[]                 = {};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 8;
			int coef[]                = {0, 0, 47, 0, 0, 42};
			int idx[]                 = {};
			int val[]                 = {};
			long long expected__      = 188;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 10;
			int coef[]                = {0, 0, 0, 0, 0, 0};
			int idx[]                 = {0, 1, 2, 3, 4, 5, 6, 7, 9, 8};
			int val[]                 = {500, 300, 400, 200, 400, 700, 100, 300, 300, 100};
			long long expected__      = 1500;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 16;
			int coef[]                = {123456789, 234567890, 345678901, 456789012, 567890123, 678901234};
			int idx[]                 = {7};
			int val[]                 = {890123456};
			long long expected__      = 4543586810LL;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			int coef[]                = ;
			int idx[]                 = ;
			int val[]                 = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int coef[]                = ;
			int idx[]                 = ;
			int val[]                 = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int coef[]                = ;
			int idx[]                 = ;
			int val[]                 = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Prominence().sumOfProminences(N, vector <int>(coef, coef + (sizeof coef / sizeof coef[0])), vector <int>(idx, idx + (sizeof idx / sizeof idx[0])), vector <int>(val, val + (sizeof val / sizeof val[0])));
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
