#line 5 "DemocraticAssignment.cpp"
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

class DemocraticAssignment
{
	public:

		int n;
		
		vector<bool> ty;

		vector<vector<int> > e;

		vector<bool> vis;

		vector<int> linkx;
		vector<int> linky;

		bool find(int x)
		{
			for (auto y : e[x])
			{
				if (!vis[y])
				{
					vis[y] = 1;
					if (linky[y] == -1 || find(linky[y]))
					{
						linky[y] = x;
						linkx[x] = y;
						return 1;
					}
				}
			}
			return 0;
		}

		vector <int> findAssignment(vector <int> preferences)
		{
			n = 0;
			while (n * n != SZ(preferences)) ++n;
			ty = vector<bool>(n, 0);
			REP(i, 0, n) ty[preferences[i * n]] = 1;
			e = vector<vector<int> >(n);
			REP(i, 0, n)
			{
				e[i].pb(preferences[i * n]);
				REP(j, 0, n)
					if (!ty[preferences[i * n + j]])
					{
						e[i].pb(preferences[i * n + j]);
						break;
					}
				sort(ALL(e[i]));
			}
			linkx = vector<int>(n, -1);
			linky = vector<int>(n, -1);
			for (int i = n - 1; i >= 0; --i)
			{
				vis = vector<bool>(n, 0);
				if (!find(i)) return vector<int>(1, -1);
			}
			return linkx;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
