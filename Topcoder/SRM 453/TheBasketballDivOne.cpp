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
#define REP_1(i, n) for (int i=1;i<=n;++i)
#define ECH(it, A) for (__typeof((A).begin()) it=(A).begin(); it != (A).end(); ++it)
#define REP_L(i, hd, suc) for (int i=hd;i;i=suc[i])
#define REP_G(i, u) REP_L(i,hd[u],suc)

typedef long long LL;
typedef double DB;

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;

template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

// --------

const int N = 5009, M = 2 * 30009;


int w[N], sum;
int n;

struct Network_Flow{

int D[N], hd[N], suc[M], to[M], cap[M];
int n, m, s, t;

inline void ae(int x, int y, int c){
    suc[m] = hd[x], hd[x] = m, to[m] = y, cap[m++] = c,
    suc[m] = hd[y], hd[y] = m, to[m] = x, cap[m++] = 0;
}

inline void aee(int x, int y, int c){
    suc[m] = hd[x], hd[x] = m, to[m] = y, cap[m++] = c,
    suc[m] = hd[y], hd[y] = m, to[m] = x, cap[m++] = c;
}

#define v to[i]
#define c cap[i]
#define f cap[i^1]

LL sap(){
    LL z=0; static int cnt[N],cur[N],pre[N];
    fill(D,D+n,n),fill(cnt,cnt+n,0);cnt[n]=n;
    int u=s;cur[s]=hd[s];while (D[s]){
#define i cur[u]
        if (u==t){
            int d=INF;for(u=s;u!=t;u=v)checkMin(d,c);
            z+=d;for(u=s;u!=t;u=v)f+=d,c-=d;u=s;
        }
#undef i
        int i;for(i=cur[u];i;i=suc[i]){
            if(D[u]+1==D[v]&&c){cur[u]=i,cur[v]=hd[v],pre[v]=u,u=v;break;}
        }
        if (!i){
            if (!--cnt[D[u]])break;
            D[u]=1;REP_G(i,u)if(c)checkMax(D[u],D[v]);--D[u];
            ++cnt[D[u]];if(u==s)cur[u]=hd[u];else u=pre[u];
        }
    }

    return z;
}

void init(){
    m = 2; n = 2+::n*::n, s = 0, t = n-1;
    fill(hd, hd+n, 0);
}


bool ck(int ss){
    int n = ::n; if (ss != n*(n-1)) return false;

    init(); int m = n*(n-1)/2;
    int a = 1, b = 2;
    REP_1(i, m){
        ae(s, i, 2); ae(i, m+a, 2); ae(i, m+b, 2); //cout << a << " "<< b << endl;
        ++b; if (a == b) ++b; if (b > n) ++a, b = a+1;
    }

    REP_1(i, n) ae(m+i, t, w[i-1]);
    return sap() == n*(n-1);
}

#undef f
#undef c
#undef v
} G;



int dfs(int k = 1, int s = w[0]){
    if (k == n) return G.ck(s);
    int z = 0; REP(i, min(w[k-1], (n-1)*2)+1){
        w[k] = i; z += dfs(k+1, s+i);
    }
    return z;
}

class TheBasketballDivOne {
public:
	int find(int n, int m){
	    if (m > 2*(n-1)) return 0;
	    ::n = n; w[0] = m;
		return dfs();
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
			int n                     = 2;
			int m                     = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int m                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int m                     = 3;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 4;
			int m                     = 6;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int n                     = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int n                     = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBasketballDivOne().find(n, m);
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
