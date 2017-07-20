#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <queue>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

#define ALL(A) A.begin(), A.end()
#define PB push_back
#define MP(A, B) make_pair(A, B)

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

template<class T> inline void checkMin(T &a, T b){if (b<a) a=b;}
template<class T> inline void checkMax(T &a, T b){if (b>a) a=b;}

const int MOD = 1000000007;
const int INF = 0x7fffffff;

const int N = 50;

//2^(n-2)

bool ck(int cur, int tar, LL k, int s, vector<int> a, string &z){
    if (!a[cur]) return false;
    --a[cur]; --s; z += 'a'+cur;
    
    int new_tar = tar;
    if (cur != tar){
        k -= 1;
        k -= 1ll << s;
        if (k < 0) return 0;
        new_tar = (0+1+2) - (cur+tar);
    }
    
    string zz = z;
    REP(i, 3){
        if (ck(i, new_tar, k, s, a, z)) return 1;
        z = zz;
    }
    return 0;
}

bool ck(int t, LL k, vector<int> a, string &z){
    if (!a[t]) return false;
    --a[t]; --s; z += char('a'+t);
    string zz = z;
    REP(i, 3){
        if (ck(i, t, k, a, z)) return 1;
        z = zz;
    }
    return 0;
}

class ClassicTowers {
public:
    string findTowers(long long k, vector <int> count) {
        string z; int s = 0; REP(i, 3) s += count[i];
        REP(i, 3) if (ck(i, k, count, z)){
            return z;
        }
        else{
            z.clear();
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
    
    int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
            cerr << "    Expected: \"" << expected << "\"" << endl;
            cerr << "    Received: \"" << received << "\"" << endl;
        }
        
        return verdict == "PASSED";
    }
    
    int run_test_case(int casenum) {
        switch (casenum) {
            case 0: {
                long long k               = 4;
                int count[]               = {1,1,2} ;
                string expected__         = "CCAB";
                
                clock_t start__           = clock();
                string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 1: {
                long long k               = 0;
                int count[]               = {0, 0, 50} ;
                string expected__         = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
                
                clock_t start__           = clock();
                string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 2: {
                long long k               = 0;
                int count[]               = {10,20,20};
                string expected__         = "";
                
                clock_t start__           = clock();
                string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 3: {
                long long k               = 123456123456123LL;
                int count[]               = {10,10,30} ;
                string expected__         = "CCACCCACCABACCABBACCCBBCCBCCCBACCCCABBACCCCCACBCCC";
                
                clock_t start__           = clock();
                string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
            case 4: {
                long long k               = 314159265358979LL;
                int count[]               = {15,16,17};
                string expected__         = "";
                
                clock_t start__           = clock();
                string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                return verify_case(casenum, expected__, received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 5: {
                 long long k               = ;
                 int count[]               = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 6: {
                 long long k               = ;
                 int count[]               = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
                 return verify_case(casenum, expected__, received__, clock()-start__);
                 }*/
                /*      case 7: {
                 long long k               = ;
                 int count[]               = ;
                 string expected__         = ;
                 
                 clock_t start__           = clock();
                 string received__         = ClassicTowers().findTowers(k, vector <int>(count, count + (sizeof count / sizeof count[0])));
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
