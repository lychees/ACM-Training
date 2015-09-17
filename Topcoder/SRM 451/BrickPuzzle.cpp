#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (__typeof((A).begin()) it=(A).begin(); it != (A).end(); ++it)

typedef long long LL;
typedef double DB;

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;

template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

// --------
const int N = 22, M = 1 << 19;

int n, m;
const int Prime = 9979;
int d; struct hashTable{
    int state[M]; int key[M]; int sz;
    int hd[Prime]; int nxt[M];
    void clear(){
        sz = 0;
        FLC(hd, -1);
    }
    void push(int s){
        int x = s % Prime;

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
    int find(int s){
        int x = s % Prime;
        for (int i=hd[x];~i;i=nxt[i]){
            if (state[i] == s){
                return key[i];
            }
        }
        return -1;
    }

} H[5]; int idx[5];
#define src idx[0]

void upd(int t, int s){
    H[idx[t]].push(s>>t);
}

class BrickPuzzle {
public:
	int leastShapes(vector <string> A) {

	    n = A.size(); m = A[0].size();

	    int p0 = 15;
	    int p1 = 3|3<<(m+1);
	    int p2 = 3|3<<m;
        int p3 = 3|3<<(m-1);

	    REP(i, 5) idx[i] = i, H[i].clear();
	    d = 0; H[src].push(0);

		REP(i, n) REP(j, m){

		    //cout << i << " " << j << ": " << H[src].sz << endl;

		    REP(ii, H[src].sz){
                int s = H[src].state[ii]; d = H[src].key[ii];

                if (s&1) upd(2, s);
                else if (A[i][j] == 'X') upd(1, s);
                ++d;

                if (j+4<=m && !(s&p0)) upd(4,s|p0);
                if (j+3<=m && !(s&p1)) upd(2,s|p1);
                if (j+2<=m && !(s&p2)) upd(2,s|p2);
                if (j+2<=m && j && !(s&p3)) upd(2,s|p3);

		    }

		    int t = src; REP(i, 4) idx[i] = idx[i+1]; idx[4] = t; H[t].clear();
		}
		return H[src].find(0);
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
			string board[]            = {"..X....",
 "..XXXXX"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {".X",
 "..",
 "X."};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"..XX....",
 "....X..X",
 "XX..XXXX"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"X..XXXX",
 "X.....X",
 "....XX.",
 "X......"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BrickPuzzle().leastShapes(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
