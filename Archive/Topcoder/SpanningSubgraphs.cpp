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


class SpanningSubgraphs {
public:
	vector <int> count(int n, vector <int> a, vector <int> b) {	
		

		



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
			int n                     = 3;
			int a[]                   = {0,1,2};
			int b[]                   = {1,2,0};
			int expected__[]          = {3, 1 };

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int n                     = 5;
			int a[]                   = {0,1,4,3};
			int b[]                   = {0,1,4,3};
			int expected__[]          = {0 };

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int n                     = 6;
			int a[]                   = {0,1,1,2,2,2,3,3,4};
			int b[]                   = {1,2,3,3,4,5,4,5,5};
			int expected__[]          = {40, 48, 27, 8, 1 };

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int n                     = 15;
			int a[]                   = {7,3,8,2,5,8,5,11,8,3,10,8,6,6,8,8,3,9,4,6,4,6,1,1,5,4, 0,9,4,7,6,0,6,2,2,6,11,4,6,10,9,2,6,0,4,7,6,8,1,3,11,3, 4,8,1,0,12,9,5,14,0,13,7,14,7,9,6,7,8,8,8,4,14,1,13,5, 1,6,13,14,0,4,8,5,13,7,2,10,10,11,8,2,4,13,12,10,5,13, 5,9,6,4,1,11,4,13,6,4,8,8,11,1,14,10,3,1,2,0,10,5,9,5, 10,8,4,2,5,12,7,2,3,2,4,6,9,3,7,9,2,14,14,0,14,3,12,12, 0,11,7,8,6,6,0,10,7,2,0,7,8,10,3,11,11,7,0,0,11,8,6,11, 13,4,11,11,8,5,13,11,9,14,10,1,12,12,3,3,0,13,13,6,2,9, 1,4,2,7,14,5};
			int b[]                   = {12,8,1,11,1,6,12,3,7,5,1,1,11,11,9,0,7,9,12,8,13,13,11, 0,2,14,12,12,13,10,13,12,2,14,11,13,14,3,12,14,11,5,3,0, 9,0,1,10,5,11,6,6,1,4,0,12,13,1,4,10,9,8,3,4,13,3,10,7, 3,2,13,0,1,13,7,3,3,9,9,10,9,9,0,13,12,3,14,4,1,7,5,0,0, 11,13,0,0,14,13,5,5,0,10,0,3,8,13,4,6,7,4,0,6,7,8,10,7, 4,6,13,0,6,3,2,11,8,7,12,0,14,12,6,10,8,6,9,2,4,14,9,4, 6,3,11,12,8,7,12,14,0,10,11,9,7,4,6,12,13,7,4,13,9,7,13, 2,4,7,6,2,0,10,7,8,13,1,14,13,3,12,14,2,4,6,7,10,11,8,4, 10,13,14,9,0,5,3,0,7,11};
			int expected__[]          = {165676111, 472152904, 401323420, 92841577, 361806106, 251066093, 860026758, 204774808, 800204699, 78217142, 290847617, 377659363, 799299488, 639266686, 463155556, 542289798, 505455263, 931966095, 332452321, 157494446, 701362585, 4372546, 189983818, 137009880, 456907012, 699388046, 492757156, 402334178, 262521060, 683669243, 218329042, 912344074, 469164876, 951780423, 845657616, 358560958, 877409160, 936645440, 506542339, 711561307, 182417811, 411559656, 609363889, 410499565, 523968597, 808436626, 796861282, 799905851, 332114660, 28142829, 832046308, 515892527, 461122988, 459763203, 639481498, 760842951, 53778152, 531539556, 499281391, 756160187, 408189379, 536177501, 236162240, 932086574, 249801471, 691291871, 305954956, 944526707, 689056121, 509929491, 860012851, 270237338, 530915439, 636690481, 284974622, 213167754, 791793494, 581854637, 515718421, 142304792, 170068497, 175763828, 669814256, 87330307, 657451539, 902803718, 994244944, 710593682, 158314930, 728217704, 428356628, 680806591, 426349961, 578797504, 448716917, 937968991, 727251530, 565010419, 762565871, 373908747, 569188731, 954967822, 83820159, 869337563, 549355611, 927598978, 992408503, 670497964, 348959921, 892858049, 328944072, 946559373, 830835081, 805632932, 389521576, 995252131, 717245242, 882920285, 127735960, 774020953, 299323686, 248711270, 707972648, 824068405, 929290955, 262377161, 603969848, 20319782, 655428762, 772441022, 315946694, 773490199, 63054183, 280718941, 320481045, 714052434, 119312921, 334810041, 844617606, 239955633, 647743078, 159621066, 358764917, 571545322, 29056136, 300270686, 822798951, 841318305, 809733973, 849084831, 542304340, 360014205, 268267900, 461637720, 441483501, 500466014, 722102413, 274028790, 889071123, 456597703, 989359978, 781914152, 339994675, 176509460, 71482668, 940949411, 727100238, 343026545, 279293690, 51741525, 759652847, 198027784, 293410546, 430593193, 339024072, 605239373, 602353448, 433606430, 526225238, 410141720, 62117055, 1274196, 19503, 198, 1 };

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int n                     = ;
			int a[]                   = ;
			int b[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int n                     = ;
			int a[]                   = ;
			int b[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int a[]                   = ;
			int b[]                   = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = SpanningSubgraphs().count(n, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
