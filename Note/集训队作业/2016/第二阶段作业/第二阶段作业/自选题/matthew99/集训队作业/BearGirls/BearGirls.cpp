#line 5 "BearGirls.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

class BearGirls
{
	public:
		double expectedValue(vector <int> A, vector <int> T, int cost)
		{
			vector<int> v;
			REP(i, 0, SZ(T)) REP(j, 0, T[i]) v.pb(A[i]++);
			sort(ALL(v));
			int n = SZ(v);
			vector<double> dp(n + 5, 0);
			vector<double> E(n, 0);
			REP(i, 0, n) E[i] = v[i];
			dp[n] = -1e100;
			for (int i = n - 1; i >= 0; --i)
			{
				dp[i] = 0;
				REP(j, 0, i + 1) dp[i] = dp[i] + max(dp[i + 1], E[j]) / (i + 1);
				vector<double> tmp(i, 0);
				REP(j, 0, i) tmp[j] = (E[j] * (i - j) + E[j + 1] * (j + 1)) / (i + 1);
				E = tmp;
				dp[i] -= cost;
			}
			return dp[0];
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
