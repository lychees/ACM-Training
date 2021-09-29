#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<(int)n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define ACCU accumulate
#define TWO(x) (1<<(x))
#define TWOL(x) (1ll<<(x))
#define clr(a) memset(a,0,sizeof(a))
typedef vector<int> VI;
typedef vector<string> VS;
typedef long long ll;
typedef long double LD;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
const int inf=0x20202020;
const ll mod=1000000007;
const double eps=1e-9;
const double pi=3.1415926535897932384626;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const int N=501000;
int n,pl[N],pr[N];
ll l[N],dp[N],pd[N],ptl[N],p[N];

int gao(int tl,int tr) {
	n=tr-tl+1;
	rep(i,1,n+1) l[i]=p[i+tl-1];
	l[1]=-100000000;
	rep(i,1,n+1) l[i+1]=p[i+tl-1];
	n+=1; l[n+1]=1ll<<50;
	dp[0]=1; dp[1]=1; pd[0]=1; pd[1]=1; ptl[1]=1; pr[n]=n;
	rep(i,2,n+1) rep(j,pl[i-1],i) if (l[j]+1000000<l[i]&&l[i]<l[j+1]+1000000) {
		pl[i]=j;
		break;
	}
	per(i,1,n) per(j,i,pr[i+1]+1) if (l[j]<l[i]+1000000&&l[i]+1000000<l[j+1]) {
		pr[i]=j;
		break;
	}
	ll dl=0,dr=0; int sr=1;
	ll ld=0,rd=0; int rs=1;
	rep(i,2,n+1) {
		dp[i]=dp[i-1]*2;
		ptl[i]=dp[i-2];
		while (pr[sr]<=pl[i]&&sr<i) {
			if (pr[sr]>sr&&l[sr+1]<l[sr-1]+1000000) 
				dl=(dl+ptl[sr+1])%mod,dr=(dr+ptl[sr+1]*pr[sr])%mod;
			else dl=(dl+pd[sr-1])%mod,dr=(dr+pd[sr-1]*pr[sr])%mod;
			sr++;
		}
		ll dd=(dl*pl[i]-dr)%mod;
		dp[i]=(dp[i]-dd)%mod;
		ptl[i]=(ptl[i]-dd)%mod;
		while (rs<=i&&pr[rs]<=i) {
			if (pr[rs]>rs&&l[rs+1]<l[rs-1]+1000000) 
				ld=(ld+ptl[rs+1])%mod,rd=(rd+ptl[rs+1]*pr[rs])%mod;
			else ld=(ld+pd[rs-1])%mod,rd=(rd+pd[rs-1]*pr[rs])%mod;
			rs++;
		}
		dd=(ld*i-rd)%mod;
		pd[i]=(dp[i]-dd)%mod;
	}
	return pd[n];
}
class FrozenStandings {
	public:
		int countStandings(int N, int A, int seed)  {
			ll x = seed;
			for (int i = 0; i < N; i++) {
    			x = x * 20142014 % 1000000007;
    			p[i+1]=(500000-x%A)*1000000+i;
			}
			sort(p+1,p+N+1);
			int pr=1;
			ll ans=1;
			rep(i,1,N+1) if (i==N||p[i]+1000000<p[i+1]) {
				ans=ans*gao(pr,i)%mod; pr=i+1;
			}
			if (ans<0) ans+=mod;
			return ans;
		}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 2137378; int Arg3 = 2; verify_case(0, Arg3, countStandings(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 565225711; int Arg3 = 1; verify_case(1, Arg3, countStandings(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 765276374; int Arg3 = 27; verify_case(2, Arg3, countStandings(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 8; int Arg1 = 2; int Arg2 = 667363653; int Arg3 = 226; verify_case(3, Arg3, countStandings(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 20; int Arg1 = 4; int Arg2 = 765276374; int Arg3 = 933806; verify_case(4, Arg3, countStandings(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 500000; int Arg1 = 100; int Arg2 = 123456789; int Arg3 = 482934470; verify_case(5, Arg3, countStandings(Arg0, Arg1, Arg2)); }
//	void test_case_5() { int Arg0 = 30; int Arg1 = 30; int Arg2 = 2333; int Arg3 = 2432836; verify_case(5, Arg3, countStandings(Arg0, Arg1, Arg2)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main() {
	FrozenStandings ___test;
	___test.run_test(5);
	return 0;
}
// END CUT HERE  
