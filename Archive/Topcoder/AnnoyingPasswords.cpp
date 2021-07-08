#include <bits/stdc++.h>

using namespace std;

#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)

#define Ts *this
#define rTs return Ts

typedef long long LL;

//}

/** Constant List .. **/ //{

const int MOD = int(1e9) + 7;

//}

/** Add On .. **/ //{


// <<= '2. Number Theory .,//{
namespace NT{
//#define gcd __gcd
inline LL gcd(LL a, LL b){return b?gcd(b,a%b):a;}
inline LL lcm(LL a, LL b){return a*b/gcd(a,b);}

inline void INC(int &a, int b){a += b; if (a >= MOD) a -= MOD;}
inline int sum(int a, int b){a += b; if (a >= MOD) a -= MOD; return a;}

/* 模数两倍刚好超 int 时。
inline int sum(uint a, int b){a += b; a %= MOD;if (a < 0) a += MOD; return a;}
inline void INC(int &a, int b){a = sum(a, b);}
*/

inline void DEC(int &a, int b){a -= b; if (a < 0) a += MOD;}
inline int dff(int a, int b){a -= b; if (a < 0) a  += MOD; return a;}
inline void MUL(int &a, int b){a = (LL)a * b % MOD;}
//inline int pdt(int a, int b){return (LL)a * b % MOD;}
inline int pdt(int x,int y) {
    int ret; __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
    return ret;
}


inline int gcd(int m, int n, int &x, int &y){

    x = 1, y = 0; int xx = 0, yy = 1, q;

    while (1){
        q = m / n, m %= n;
        if (!m){x = xx, y = yy; return n;}
        DEC(x, pdt(q, xx)), DEC(y, pdt(q, yy));
        q = n / m, n %= m;
        if (!n) return m;
        DEC(xx, pdt(q, x)), DEC(yy, pdt(q, y));
    }
}

inline int sum(int a, int b, int c){return sum(a, sum(b, c));}
inline int sum(int a, int b, int c, int d){return sum(sum(a, b), sum(c, d));}
inline int pdt(int a, int b, int c){return pdt(a, pdt(b, c));}
inline int pdt(int a, int b, int c, int d){return pdt(pdt(a, b), pdt(c, d));}

inline int pow(int a, LL b){
    int c(1); while (b){
        if (b&1) MUL(c, a);
        MUL(a, a), b >>= 1;
    }
    return c;
}

template<class T> inline T pow(T a, LL b){
    T c(1); while (b){
        if (b&1) c *= a;
        a *= a, b >>= 1;
    }
    return c;
}

template<class T> inline T pow(T a, int b){
    return pow(a, (LL)b);
}

inline int _I(int b){
    int a = MOD, x1 = 0, x2 = 1, q; while (1){
        q = a / b, a %= b;
        if (!a) return x2;
        DEC(x1, pdt(q, x2));

        q = b / a, b %= a;
        if (!b) return x1;
        DEC(x2, pdt(q, x1));
    }
}

inline void DIV(int &a, int b){MUL(a, _I(b));}
inline int qtt(int a, int b){return pdt(a, _I(b));}

struct Int{
    int val;

    operator int() const{return val;}

    Int(int _val = 0):val(_val){
        val %= MOD; if (val < 0) val += MOD;
    }
    Int(LL _val):val(_val){
        _val %= MOD; if (_val < 0) _val += MOD;
        val = _val;
    }

    Int& operator +=(const int& rhs){INC(val, rhs);rTs;}
    Int operator +(const int& rhs) const{return sum(val, rhs);}
    Int& operator -=(const int& rhs){DEC(val, rhs);rTs;}
    Int operator -(const int& rhs) const{return dff(val, rhs);}
    Int& operator *=(const int& rhs){MUL(val, rhs);rTs;}
    Int operator *(const int& rhs) const{return pdt(val, rhs);}
    Int& operator /=(const int& rhs){DIV(val, rhs);rTs;}
    Int operator /(const int& rhs) const{return qtt(val, rhs);}
    Int operator-()const{return MOD-*this;}
};

} using namespace NT;//}


const int N = 109;
Int Fact[109];

Int f(int n, int m) {
    //cout << Fact[n] <<" " << Fact[n] / Fact[n-m] << endl;
    //cout << 26*26<10 <<endl;

    return Fact[n] / Fact[n-m];
}


/*
Int dp[109][109][109], dp2[109][109][109];

void gao(int n, int m, int l) {

    REP(i, n+1) {

#define u dp[i][][l-j]

        RPE(j, l+1) if () {
        }

    }
} */


Int dp[N], dp2[N];

Int Comb(int n, int m) {
    return Fact[n] / (Fact[m] * Fact[n-m]);
}
Int Cha(int n, int m) {
    --m;
    return Comb(n+m, n);
}


void gao(int t, int n) {

    REP(i, N) dp2[i] = 0;

    REP(i, N) if (dp[i] != 0){ // 总共 t 个，有 i 个坏位置

        FOR(j, -n, n) { // 坏位置的 delta
            if (i+j >= 0) {
                REP(k, i+1) { // 从之前的怀位置取多少个
                    REP(kk, t-i+1) { // 从之前的好位置取多少个

                        // n == k+kk + r

                        // j == r - k


                        int r = n - k - kk;
                        if (k +kk == 0) continue;
                        if (r<0) continue;

                        if (j == r-k ) {

                            //cout << r << " " << t << " "<< i+j << " " << i << " " << k << " " << kk << ": "
                             //<< " " <<dp[i] << " " <<Comb(i,k) << " "<< Comb(t-i, kk) << " "<<  Cha(r, kk+k) << endl;
                            dp2[i+j] += dp[i] * Comb(i,k) * Comb(t-i, kk) *  Cha(r, kk+k);

                            //cout << dp2[i+j] << endl;
                        }
                    }

                }
            }
        }

    }

    REP(i, N) dp[i] = dp2[i];
}

// 1 1
// 2 * 3


Int g(int a, int b, int c) {
    /*REP(i, 100) REP(j, 100) REP(k, 100) dp[i][j][k] = 0;
    dp[a+1][a-1][b] = 1;

    gao(a+1,a-1, b);

    REP(i, 100) REP(j, 100) REP(k, 100) dp2[i][j][k] = 0;
    REP(i, 100) REP(j, 100) dp2[i][j][c] = dp[i][j][0];
    REP(i, 100) REP(j, 100) REP(k, 100) dp[i][j][k] = dp2[i][j][k];

    gao(a+b+1,a+b-1, c);


    return dp[a+b+c+1][0][0];*/

    // 1 1 1
    //

    REP(i, N) dp[i] = 0; dp[0] = 1;

    if (a) gao(1, a);
    if (b) gao(a+1, b);
    if (c) gao(a+b+1, c);

    return dp[0];
}


class AnnoyingPasswords {
	public:
	int count(int U, int L, int D) {

	    Fact[0] = 1; REP(i, 100) Fact[i+1] = Fact[i] * (i+1);
        Int z = f(26,U)*f(26,L)*f(10,D)*g(U,L,D);
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
			int U                     = 26;
			int L                     = 26;
			int D                     = 10;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 1: {
			int U                     = 5;
			int L                     = 0;
			int D                     = 4;
			int expected__            = 783743727;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 2: {
			int U                     = 1;
			int L                     = 1;
			int D                     = 1;
			int expected__            = 40560;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 3: {
			int U                     = 2;
			int L                     = 2;
			int D                     = 3;
			int expected__            = 559599923;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}
		case 4: {
			int U                     = 0;
			int L                     = 0;
			int D                     = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int U                     = ;
			int L                     = ;
			int D                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int U                     = ;
			int L                     = ;
			int D                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int U                     = ;
			int L                     = ;
			int D                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
			return verify_case(casenum, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int U                     = ;
			int L                     = ;
			int D                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AnnoyingPasswords().count(U, L, D);
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

