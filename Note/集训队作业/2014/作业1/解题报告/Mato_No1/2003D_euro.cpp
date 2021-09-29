#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define re(i, n) for (int i=0; i<n; i++)
#define re1(i, n) for (int i=1; i<=n; i++)
#define re2(i, l, r) for (int i=l; i<r; i++)
#define re3(i, l, r) for (int i=l; i<=r; i++)
#define rre(i, n) for (int i=n-1; i>=0; i--)
#define rre1(i, n) for (int i=n; i>0; i--)
#define rre2(i, r, l) for (int i=r-1; i>=l; i--)
#define rre3(i, r, l) for (int i=r; i>=l; i--)
#define ll long long
const int MAXN = 21, S = 10, P1[4] = {1, 0, -1, 0}, P2[4] = {0, 1, 0, -1}, INF = ~0U >> 2;
struct sss0 {
	char ss[50];
	int xl, yl, xr, yr, res;
	bool operator< (sss0 s0) const {return res < s0.res || res == s0.res && strcmp(ss, s0.ss) < 0;}
} A[MAXN];
int n, W[S][S], NS[S][S], V[S][S], V0[S][S];
void prepare()
{
	int _x, _y;
	re(i, S) re(j, S) if (W[i][j] >= 0) {
		NS[i][j] = 0;
		re(k, 4) {
			_x = i + P1[k]; _y = j + P2[k];
			if (_x >= 0 && _x < S && _y >= 0 && _y < S && W[_x][_y] >= 0) NS[i][j]++;
		}
	}
}
void solve()
{
	int _, _v, _x, _y, sum0;
	re(i, n) {
		_ = sum0 = 0; re(j, S) re(k, S) if (W[j][k] >= 0) {
			if (j >= A[i].xl && j <= A[i].xr && k >= A[i].yl && k <= A[i].yr) V[j][k] = 1000000; else {V[j][k] = 0; sum0++;}
		}
		while (sum0) {
			_++;
			re(j, S) re(k, S) if (W[j][k] >= 0) {
				V0[j][k] = 0;
				re(__, 4) {
					_x = j + P1[__]; _y = k + P2[__];
					if (_x >= 0 && _x < S && _y >= 0 && _y < S && W[_x][_y] >= 0) V0[j][k] += V[_x][_y] / 1000;
				}
			}
			re(j, S) re(k, S) if (W[j][k] >= 0) {
				_v = V[j][k];
				V[j][k] += V0[j][k] - (V[j][k] / 1000) * NS[j][k];
				if (!_v && V[j][k]) {sum0--; if (_ > A[W[j][k]].res) A[W[j][k]].res = _;}
			}
		}
	}
	sort(A, A + n);
}
int main()
{
	int testno = 0, xl, xr, yl, yr;
	while (1) {
		scanf("%d", &n); if (n) testno++; else break;
		re(i, S) re(j, S) W[i][j] = -1;
		re(i, n) {
			scanf("%s%d%d%d%d", A[i].ss, &xl, &yl, &xr, &yr); xl--; yl--; xr--; yr--;
			re3(j, xl, xr) re3(k, yl, yr) W[j][k] = i;
			A[i].xl = xl; A[i].xr = xr; A[i].yl = yl; A[i].yr = yr; A[i].res = 0;
		}
		prepare();
		solve();
		printf("Case Number %d\n", testno);
		re(i, n) printf("   %s   %d\n", A[i].ss, A[i].res);
	}
	return 0;
}

