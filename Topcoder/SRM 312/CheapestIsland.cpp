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
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it != A.end(); ++it)
#define REP_N(i, n) for (i=0;i<n;++i)

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
inline LL _U(int i){return (1ll<<i) - 1;};

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

/* -&$&#*( &#*@)^$@&*)*/

const int N = 12, M = 1 << 18, _M = 3;

int n, m;
int b[N+1], bb[N+1];
void decode(LL s){
    REP(i, m+1){
        b[i] = s & _U(_M); s >>= _M;
    }
}
LL encode(){
    FLC(bb, -1); int n = 1; bb[0] = 0; LL s = 0;
    DWN(i, m+1, 0){
        if (!~bb[b[i]]) bb[b[i]] = n++;
        s <<= _M; s |= bb[b[i]];
    }
    return s;
}
const int Prime = 9979;
int A[N+1][N+1];
int i, j; LL d; int op; struct hashMap{
    LL state[M]; LL key[M]; int sz;
    int hd[Prime]; int nxt[M];
    void clear(){
        sz = 0;
        FLC(hd, -1);
    }
    void push(){
        LL s = encode();
        int x = s % Prime;
        LL d = ::d; if(op) d += A[i][j];
        for (int i=hd[x];~i;i=nxt[i]){
            if (state[i] == s){
                checkMin(key[i], d);
                return;
            }
        }
        state[sz] = s; key[sz] = d;
        nxt[sz] = hd[x]; hd[x] = sz;
        ++sz;
        assert(sz < M);
    }
    void roll(){
        LL U = _U(_M*(m+1));
        REP(ii, sz){
            state[ii] <<= _M;
            state[ii] &= U;
        }
    }
    void display(int ii){
        decode(state[ii]);
        cout << key[ii] << ": " << endl;
        REP(i, m+1) cout << b[i] << " "; cout << endl;
        puts("");
    }
} H[2]; int src, des;

LL z; int ii; void trans(){
    decode(H[src].state[ii]); d = H[src].key[ii];
    int lt = j ? b[j-1] : 0, lu = b[j], up = b[j+1];

    if (!op){
        b[j] = 0;
        if (up){
            int c1 = 0, c2 = 0; REP(i, m+1){
                if (b[i]) ++c1;
                if (b[i] == up) ++c2;
            }
            if (c2 == 1){
                if (c1 == 1) checkMin(z, d);
                return;
            }
        }
        H[des].push();
    }
    else{
        if (lt && up){
            if (lt != up){
                REP(i, m+1) if (b[i] == up) b[i] = lt;
            }
            b[j] = lt;
            H[des].push();
        }
        else if (lt || up){
            int t = lt | up;
            b[j] = t;
            H[des].push();
        }
        else{
            b[j] = m;
            H[des].push();
        }
    }
}

int solve(){
    src = 0; des = 1; H[des].clear(); RST(b); d = 0; op = 0; H[des].push();
    z = 0; REP_N(i, n+1){
        REP_N(j, m){
            swap(src, des); H[des].clear();
            //cout << i << " " << j << ": " << H[src].sz << endl;
            REP_N(ii, H[src].sz){
                //H[src].display(ii);
                op = 0; trans();
                op = 1; trans();
            }
        }
        H[des].roll();
    }

    return int(z);
}

class CheapestIsland {
public:
	int minCost(vector <string> cells) {

		RST(A); n = int(cells.size()); REP(i, n){
		    m = 0; istringstream iss(cells[i]);
		    while (iss >> A[i][m]) ++m;
		}
		return solve();
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
			string cells[]            =
			    {"-1 -1 -1 -1 -1",
			     "-1 -1 -1 -1 -1"};
			int expected__            = -10;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string cells[]            = {"1 2 3",
"4 5 6",
"7 8 9"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string cells[]            = {"-5 100 -5",
"-5 100 -5"};
			int expected__            = -10;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string cells[]            = {"-1 -1 1 -1 -1",
"-1 -1 1 -1 -1",
"-1 -1 1 -1 -1",
"99 99 99 99 99",
"-1 -1 -1 -1 -1",
"-1 -1 -1 -1 -1"}
;
			int expected__            = -11;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string cells[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string cells[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string cells[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CheapestIsland().minCost(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
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
