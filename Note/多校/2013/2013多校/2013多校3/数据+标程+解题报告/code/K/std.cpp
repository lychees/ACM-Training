#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <set>
#include <climits>
using namespace std;
typedef long long int64;

void readVector(int n, int x[]) {
	int64 cur = 0;
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	for (int i = 0; i < n; ++i) {
		cur = (cur * a + b) % c;
		x[i] = cur;
	}
}

const int MAX_N = int(5e5) + 10;

int n, x[MAX_N], y[MAX_N];

struct Point {
	int x, y;
	bool operator<(const Point&o) const {
		return x < o.x;
	}
};

void work() {
	cin >> n;
	readVector(n, x);
	readVector(n, y);

	multiset<Point> ps;

	int64 ans = 1LL << 60;
	int64 sum = 0;

	for (int i = 0; i < n; ++i) {
		Point p;
		p.x = x[i], p.y = y[i];

		if (i > 0) {
			multiset<Point>::iterator it = ps.lower_bound(p), e;

			for (e = it; e != ps.end(); ++e) {
				int64 dx = e->x - p.x;
				if (dx * dx >= ans)
					break;
				int64 dy = e->y - p.y;
				ans = min(ans, dx * dx + dy * dy);
			}

			for (e = it; e != ps.begin();) {
				--e;
				int64 dx = e->x - p.x;
				if (dx * dx >= ans)
					break;
				int64 dy = e->y - p.y;
				ans = min(ans, dx * dx + dy * dy);
			}

			sum += ans;
		}

		ps.insert(p);
	}

	cout << sum << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
