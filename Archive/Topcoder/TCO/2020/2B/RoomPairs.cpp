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
const int INF = 0x7fffffff;


const int N = 50;
bool col[N][N];

int f(int n, int m, int a, int b) {
    int z = 0;
    
    if (a != n-1 && !col[a+1][b] ||
        b != m-1 && !col[a][b+1] ||
        a != 0 && !col[a-1][b] ||
        b != 0 && !col[a][b-1]) {
        z = 1;
    }
    
    if (a != n-1 && col[a+1][b]) ++z;
    if (b != m-1 && col[a][b+1]) ++z;
    if (a != 0 && col[a-1][b]) ++z;
    if (b != 0 && col[a][b-1]) ++z;
    return z;
}


vector<string> gen(int n, int m, int c) {
    vector<string> z;
    
    memset(col, 0, sizeof(col));
    
    REP(d, n+m+2) {
        REP(i, n) {
            int j  = d - i;
            if (j >= 0 && j < m) {
                if (f(n,m,i,j) <= c) {
                    c -= f(n,m,i,j);
                    //   cout << c << " " << i << " " << j << endl;
                    col[i][j] = true;
                }
            }
        }
    }
    
    REP(i, n) {
        if (i == 0) {
            string s; s += '+';
            for (int j=0;j<m;++j) {
                s += '-';
                s += '+';
            }
            z.PB(s);
        }
        
        string t; t += '|';
        for (int j=0;j<m;++j) {
            t += ' ';
            if ( col[i][j+1] || col[i][j] || j == m-1) {
                t += '|';
            } else {
                t += ' ';
            }
        }
        z.PB(t);
        
        string s; s += '+';
        for (int j=0;j<m;++j) {
            if (col[i][j] || col[i+1][j] || i == n-1) {
                s += '-';
            } else {
                s += ' ';
            }
            s += '+';
        }
        z.PB(s);
    }
    
    REP(i, z.size()) {
        cout << z[i] << endl;
    }
    
    return z;
}



class RoomPairs {
public:
	vector <string> construct(int R, int C, int N) {	
    
		
		return gen(R,C,N);
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
	template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) { 
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
			int R                     = 2;
			int C                     = 4;
			int N                     = 1;
			string expected__[]       = {"+-+-+-+-+", "| |   | |", "+ + +-+ +", "|   |   |", "+-+-+-+-+" };

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int R                     = 3;
			int C                     = 3;
			int N                     = 4;
			string expected__[]       = {"+-+-+-+", "| | | |", "+-+ +-+", "|     |", "+-+ +-+", "| | | |", "+-+-+-+" };

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int R                     = 3;
			int C                     = 4;
			int N                     = 3;
			string expected__[]       = {"+-+-+-+-+", "|       |", "+ +-+-+ +", "| | | | |", "+ +-+-+ +", "|       |", "+-+-+-+-+" };

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int R                     = 4;
			int C                     = 5;
			int N                     = 31;
			string expected__[]       = {"+-+-+-+-+-+", "| | | | | |", "+-+-+-+-+-+", "| | | | | |", "+-+-+-+-+-+", "| | | | | |", "+-+-+-+-+-+", "| | | | | |", "+-+-+-+-+-+" };

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int R                     = ;
			int C                     = ;
			int N                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			int R                     = ;
			int C                     = ;
			int N                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int R                     = ;
			int C                     = ;
			int N                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = RoomPairs().construct(R, C, N);
			return verify_case(casenum, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
