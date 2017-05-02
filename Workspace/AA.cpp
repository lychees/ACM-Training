#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <set>
#include <map>

using namespace std;

#define REP(I, N) for (int I=0;I<int(N);++I)
#define FOR(I, A, B) for (int I=int(A);I<int(B);++I)
#define DWN(I, B, A) for (int I=int(B-1);I>=int(A);--I)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

#define ALL(A) A.begin(), A.end()
#define PB push_back
#define MP(A, B) make_pair(A, B)

typedef long long LL;
typedef double DB;

template<class T> inline void RST(T &A){memset(A, 0, sizeof(A));}
template<class T> inline void FLC(T &A, int x){memset(A, x, sizeof(A));}

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

const int N = 51;

bool ok[N][N];
vector<int> E,lef,rig,a,b,c;
vector<int> ccc[N];
vector<int> adj[N];
int L[N], R[N], cnt;
int n;


inline void dfs2(int u = 0){
    if (u == -1) return;
    L[u] = ++cnt;
    dfs2(lef[u]);
    dfs2(rig[u]);
    R[u] = cnt;
}

int vis[N], tt;
int py[N];

#define y adj[x][i]

bool dfs(int x){
    
    vector<int> ok; REP(i, n) ok.PB(1);
    REP(i, ccc[x].size()){
        int t = ccc[x][i];
        int r = a[t];
        if (r == x) r = b[t];
        
        
        
        int ci = c[t];
        
        
        
        REP(j, n){
            if (L[ci] <= L[j ] && L[j] <= R[ci]){
                
            }
            else{
                ok[j] = false;
            }
        }
        
        
    }
    
    REP(i, adj[x].size()) if (vis[y] != tt && ok[y] ){
        vis[y] = tt;
        if (py[y] == -1 || dfs(py[y])){
            py[y] = x;
            return true;
        }
    }
    return false;
}


class BinaryTreeAndPermutation {
public:
    vector <int> findPermutation(vector <int> lef, vector <int> rig, vector <int> a, vector <int> b, vector <int> c) {
        E.clear(); n = lef.size();
        REP(i, n) adj[i].clear(), ccc[i].clear();
        ::lef = lef, ::rig = rig, ::a = a, ::b = b, ::c = c;
        
        REP(i, n) REP(j, n) ok[i][j] = 1;
        
        cnt = 0; dfs2(0);
        
        REP(i, a.size()){
            //cout << lef[i] << " " << rig[i] << endl;
            
            if (a[i] == b[i]){
                
                //cout << "???" << endl;
                
                REP(j, n) if (j != c[i]) ok[ a[i] ][ j ] = false;
            }
            else{
                
                ccc[a[i]].PB(i);
                ccc[b[i]].PB(i);
                
                REP(j, n){
                    
                    
                    if (L[c[i]] <= L[j] && L[j] <= R[c[i]]){
                        
                    }
                    else{
                        ok[ a[i]  ][j] = false;
                        ok[ b[i]  ][j] = false;
                        
                    }
                }}
        }
        REP(i, n){
            REP(j, n) if (ok[i][j]) adj[i].push_back(j);
        }
        
        /*REP(i, n){
         REP(j, adj[i].size()) cout << adj[i][j] << ", ";
         cout << endl;
         }*/
        
        FLC(py, -1);
        REP(i, n){
            ++tt; if (!dfs(i)) return E;
            // cout << i << endl;
        }
        REP(i, n) E.push_back(py[i]);
        return E;
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
                int lef[]                 = {1,-1,-1};
                int rig[]                 = {2,-1,-1};
                int a[]                   = {2,1};
                int b[]                   = {2,0};
                int c[]                   = {0,0};
                int expected__[]          = {2, 1, 0 };
                
                clock_t start__           = clock();
                vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
            }
            case 1: {
                int lef[]                 = {1,-1,-1};
                int rig[]                 = {2,-1,-1};
                int a[]                   = {2,1};
                int b[]                   = {2,0};
                int c[]                   = {0,1};
                int expected__[]          = { };
                
                clock_t start__           = clock();
                vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
            }
            case 2: {
                int lef[]                 = {1,-1,3,-1,-1};
                int rig[]                 = {2,-1,4,-1,-1};
                int a[]                   = {3,0,0,0};
                int b[]                   = {3,1,2,4};
                int c[]                   = {0,0,0,0};
                int expected__[]          = {1, 3, 4, 0, 2 };
                
                clock_t start__           = clock();
                vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
            }
            case 3: {
                int lef[]                 = {1,-1,3,-1,-1};
                int rig[]                 = {2,-1,4,-1,-1};
                int a[]                   = {3,0,0,1};
                int b[]                   = {3,1,2,4};
                int c[]                   = {0,0,0,0};
                int expected__[]          = { };
                
                clock_t start__           = clock();
                vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
            }
            case 4: {
                int lef[]                 = {1,-1,3,-1,-1};
                int rig[]                 = {2,-1,4,-1,-1};
                int a[]                   = {1,2};
                int b[]                   = {2,1};
                int c[]                   = {0,1};
                int expected__[]          = { };
                
                clock_t start__           = clock();
                vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
            }
            case 5: {
                int lef[]                 = {1,3,5,-1,-1,7,-1,-1,-1};
                int rig[]                 = {2,4,6,-1,-1,8,-1,-1,-1};
                int a[]                   = {6,6,7,7,3,8,5,3};
                int b[]                   = {4,3,7,1,0,0,0,5};
                int c[]                   = {1,0,1,0,2,2,2,5};
                int expected__[]          = {2, 0, 7, 5, 4, 8, 3, 1, 6 };
                
                clock_t start__           = clock();
                vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
            }
                
                // custom cases
                
                /*      case 6: {
                 int lef[]                 = ;
                 int rig[]                 = ;
                 int a[]                   = ;
                 int b[]                   = ;
                 int c[]                   = ;
                 int expected__[]          = ;
                 
                 clock_t start__           = clock();
                 vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                 return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
                 }*/
                /*      case 7: {
                 int lef[]                 = ;
                 int rig[]                 = ;
                 int a[]                   = ;
                 int b[]                   = ;
                 int c[]                   = ;
                 int expected__[]          = ;
                 
                 clock_t start__           = clock();
                 vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
                 return verify_case(casenum, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
                 }*/
                /*      case 8: {
                 int lef[]                 = ;
                 int rig[]                 = ;
                 int a[]                   = ;
                 int b[]                   = ;
                 int c[]                   = ;
                 int expected__[]          = ;
                 
                 clock_t start__           = clock();
                 vector <int> received__   = BinaryTreeAndPermutation().findPermutation(vector <int>(lef, lef + (sizeof lef / sizeof lef[0])), vector <int>(rig, rig + (sizeof rig / sizeof rig[0])), vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])));
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
