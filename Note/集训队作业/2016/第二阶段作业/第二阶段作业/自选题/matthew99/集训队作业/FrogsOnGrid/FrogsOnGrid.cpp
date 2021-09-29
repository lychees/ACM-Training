#line 5 "FrogsOnGrid.cpp"
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
const LL OO = 0x3f3f3f3f3f3f3f3fLL;

int ex_gcd(const int &a, const int &b, int &x, int &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	int d = ex_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

LL get_min(int x, int y, int x0, int y0, int x1, int y1)
{
// x0 + k = x1, y0 - k = y1
// k = (x1 - x0) % x, k = (y0 - y1) % y
	int a = (x1 - x0) % x, b = (y0 - y1) % y;
// k = a % x, k = b % y
	int d = __gcd(x, y);
	if ((b - a) % d) return OO;
	int d0 = b % d;
	a -= d0, b -= d0;
	a /= d, b /= d;
	x /= d, y /= d;
	LL M = (LL)x * y;
	int u, v;
	ex_gcd(x, y, u, v);
	LL tmp0 = (LL)v * y % M, tmp1 = (LL)u * x % M;
	LL ans = (tmp0 * a + tmp1 * b) % M;
	M *= d;
	((ans *= d) += d0) %= M;
	(ans += M) %= M;
	return ans;
}

class FrogsOnGrid
{
	public:
		string isPossible(int H, int W, vector <int> r, vector <int> c)
		{
			int n = SZ(r);
			REP(i, 0, n)
			{
				LL Min0 = OO, Min1 = OO;
				REP(j, 0, n)
				{
					LL T0 = get_min(H, W, r[i], (c[i] + W - 1) % W, r[j], c[j]);
					LL T1 = get_min(H, W, r[i], (c[i] + W - 1) % W, (r[j] + H - 1) % H, c[j]);
					chkmin(Min0, T0);
					chkmin(Min1, T1);
				}
				if (Min0 > Min1) return "Impossible";
			}
			return "Possible";
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
