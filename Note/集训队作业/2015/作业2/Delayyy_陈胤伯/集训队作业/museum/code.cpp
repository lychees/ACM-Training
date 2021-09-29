#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

const int N = 400040;
const double eps = 1e-10;

int n, m;
double W, H;

double x[N], y[N];
int v[N];

int lst[N];

struct compare {
	bool operator () (int i, int j) {
		return y[i] < y[j] || (y[i] == y[j] && i < j);
	}
};
set<int,compare> S;

bool cmp_x(int i, int j) {
	return x[i] < x[j];
}
int main() {
	scanf("%d %d", &n, &m);
	scanf("%lf %lf", &W, &H);

	for (int i = 1; i <= n + m; ++i) {
		scanf("%lf %lf %d", &x[i], &y[i], &v[i]);
		if (H < W)
			x[i] *= H / W;
		else
			y[i] *= W / H;
		double nx = x[i] + y[i];
		double ny = y[i] - x[i];
		x[i] = nx, y[i] = ny;
		if (i > n) x[i] += eps, y[i] += eps;
	}

	for (int i = 1; i <= n + m; ++i) {
		lst[i] = i;
	}
	sort(lst + 1, lst + n + m + 1, cmp_x);

	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += v[i];
	}
	
	y[n + m + 1] = 1e19;
	S.insert(n + m + 1);
	y[0] = -1e19;
	S.insert(0);

	for (int ii = 1; ii <= n + m; ++ii) {
		int i = lst[ii];
		if (i <= n) {
			S.insert(i);
		} else {
			set<int,compare>::iterator it = S.upper_bound(i), ut;
			for (--it; *it; it = ut) {
				ut = it, --ut;
				int tmp = min(v[*it], v[i]);
				v[*it] -= tmp;
				v[i] -= tmp;
				ans -= tmp;
				if (!v[*it]) S.erase(it);
				else break;
			}
		}
	}
	cout << ans << endl;
}
