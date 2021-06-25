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


class TwoLineRegions {
public:
	int count(vector <int> a, vector <int> b, vector <int> c) {	
		

		



		int res = 0;

		
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
			int a[]                   = {1,1};
			int b[]                   = {1,-1};
			int c[]                   = {0,0};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1,1,1};
			int b[]                   = {1,-1,2};
			int c[]                   = {0,0,-1};
			int expected__            = 15;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {1,-4,-3,3,8,2};
			int b[]                   = {5,3,-4,7,-2,-10};
			int c[]                   = {1,-2,-7,1,2,5};
			int expected__            = 190;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {-641,827,-531,-804,967,356,873};
			int b[]                   = {536,897,778,322,-604,-339,253};
			int c[]                   = {591,-938,837,831,-151,461,694};
			int expected__            = 408;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {-4828,-2210,-7007,7070,3467,-1837,6908,5221,7181,2544, -8805,-7864,-4692,9822,5286,-7007,-452,4005,4523,-1363, -3702,-1157,5197,-3627,-3653,645,-2331,-4397,-9409,-240};
			int b[]                   = {-6615,751,-568,9049,-5051,3648,-3729,-941,6227,-1148,848, 853,-19,8846,-3327,-5688,7602,3147,3954,3109,-8913,3595, 6512,6757,3071,600,-9794,-6169,6436,-1560};
			int c[]                   = {-5459,4853,3715,1840,6991,-3878,6522,1821,-1622,1947,-7613, -348,-5993,396,4950,-2304,6235,-9146,5392,-1028,3901,-5660, -6982,-9060,-1945,-4973,-8950,-2569,-1194,7828};
			int expected__            = 412956109;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TwoLineRegions().count(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
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
