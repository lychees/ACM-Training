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
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

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

const int N = 109;

vector<int> adj[N]; int dfn[N], low[N]; int bel[N], sta[N], top;
bool inD[N], used[N];
int n, nn; int p, q; DB z;

#define v (*it)
void dfs(int u){
    dfn[u] = low[u] = nn++;
    sta[top++] = u;
    ECH(it, adj[u]){
        if (dfn[v] < dfn[u]){
            if (!~dfn[v]) dfs(v);
            checkMin(low[u], low[v]);
        }
    }
    if (low[u] == dfn[u]){
        do{
            bel[sta[--top]] = u;
            dfn[sta[top]] = INF;
        } while(sta[top] != u);
    }
}

class AntarcticaPolice {
public:
	double minAverageCost(vector <int> costs, vector <string> roads) {

        n = costs.size(); REP(i, n) adj[i].clear();
        REP(i, n) REP(j, n) if (roads[i][j] == 'Y') adj[i].PB(j);

        nn = 0; FLC(dfn, -1); REP(i, n) if (!~dfn[i]) dfs(i);

        RST(inD); REP(u, n){
            ECH(it, adj[u]) if (bel[v] != bel[u]) inD[bel[v]] = true;
        }

        z = 0, p = 0, q = 0; FLC(low, 0x3f);
        REP(i, n) if (costs[i] < low[bel[i]]){
            low[bel[i]] = costs[i];
            dfn[bel[i]] = i;
        }

        RST(used); REP(i, n) if (low[i] != INF && !inD[i]){
            p += low[i], ++q;
            used[dfn[i]] = true;
        }

        z = (DB) p / q;
        vector<int> C; REP(i, n) if (!used[i]) C.PB(costs[i]);
        sort(C.begin(), C.end());

        REP(i, C.size()){
            p += C[i]; ++q;
            DB zz = (DB)p/q;
            if (zz >= z) break;
            z = zz;
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

	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }

	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) {
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
			/*int costs[]               = {1,2,3,4};
			string roads[]            = {"NYNN","NNYN","NNNY","YNNN"};
			double expected__         = 1.0;*/
            int costs[]               = {5,6,7,8};
			string roads[]            = {"NYNN","YNNN","NNNY", "NNYN"};
			double expected__         = 6.0;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int costs[]               = {1,2,3,4};
			string roads[]            = {"NYNN","NNYN","NNNY","NYNN"};
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int costs[]               = {5,6,7,8};
			string roads[]            = {"NYNN","YNNN","NNNY", "NNYN"};
			double expected__         = 6.0;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int costs[]               = {10,5};
			string roads[]            = {"NY","NN"};
			double expected__         = 7.5;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int costs[]               = {34,22,25,43,12};
			string roads[]            = {"NYNNY","YNNYN","NNNYY","NNNNN","NNNNN"};
			double expected__         = 19.666666666666668;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int costs[]               = ;
			string roads[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int costs[]               = ;
			string roads[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int costs[]               = ;
			string roads[]            = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = AntarcticaPolice().minAverageCost(vector <int>(costs, costs + (sizeof costs / sizeof costs[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
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
