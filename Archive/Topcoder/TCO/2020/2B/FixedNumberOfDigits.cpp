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

/* -&$&#*( &#*@)^$@&*)*/

LL cnt(LL x) {
    LL z = 0;
    while (x) {
        x /= 10;
        ++z;
    }
    return z;
}

LL _99(int x) {
    LL z = 0;
    while(x--) {
        z *= 10;
        z += 9;
    }
    return z;
}

LL f(LL a, LL d, LL n) {
    
    if (a == 0) {
        if (n == 1) return a;
        n -= 1;
        a += d;
    }
    
    LL an = cnt(a); LL b = _99(an);
    LL len = (b - a) / d  + 1;
    
    while (n > len * an) {
        n -= len * an;
        a += d * len ; an = cnt(a); b = _99(an);
        len = (b - a) / d + 1;
    }
    
    //cout << n << " " << len*an << endl;
    a += (n/an)*d;
    //cout << a << " " << n%an << " " << n << " " << an << endl;
    
    if (n % an == 0) {
        a -= d;
        return a;
    }
    
    vector<int> t; while(a) {
        t.PB(a%10);
        a /= 10;
    }
    reverse(t.begin(), t.end());
    
    LL z = 0;
    for (int i=0;i<n%an;++i) {
        z *= 10;
        z += t[i];
    }
    
    return z;
}


class FixedNumberOfDigits {
public:
    long long sum(int start, int step, long long numberOfDigits) {
        return f(start, step, numberOfDigits);
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
                int start                 = 47;
                int step                  = 10;
                long long numberOfDigits  = 7;
                long long expected__      = 7;
                
                clock_t start__           = clock();
                long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                int start                 = 98;
                int step                  = 1;
                long long numberOfDigits  = 10;
                long long expected__      = 101;
                
                clock_t start__           = clock();
                long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                int start                 = 0;
                int step                  = 1;
                long long numberOfDigits  = 7;
                long long expected__      = 6;
                
                clock_t start__           = clock();
                long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                int start                 = 123456789;
                int step                  = 10;
                long long numberOfDigits  = 5;
                long long expected__      = 12345;
                
                clock_t start__           = clock();
                long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                int start                 = 123456789;
                int step                  = 10;
                long long numberOfDigits  = 17;
                long long expected__      = 12345679;
                
                clock_t start__           = clock();
                long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
            case 5: {
                int start                 = 2359401;
                int step                  = 7;
                long long numberOfDigits  = 27244995092ll;
                long long expected__      = 183492255ll;
                
                clock_t start__           = clock();
                long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                /*      case 6: {
                 int start                 = ;
                 int step                  = ;
                 long long numberOfDigits  = ;
                 long long expected__      = ;
                 
                 clock_t start__           = clock();
                 long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int start                 = ;
                 int step                  = ;
                 long long numberOfDigits  = ;
                 long long expected__      = ;
                 
                 clock_t start__           = clock();
                 long long received__      = FixedNumberOfDigits().sum(start, step, numberOfDigits);
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
