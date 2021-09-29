#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;
const double eps = 1e-10;
const double INF = 2e6;
const double pi = acos(-1);

int n, cur;
double w, h, ans;

struct point {
	double x, y;
	void init() {
		scanf("%lf %lf", &x, &y);
	}
} p[N];

struct event {
	double t;
	int v;
} ev[N * 3];
int evt;

double dist(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool cmp_ev(const event& a, const event& b) {
	if (fabs(a.t - b.t) < eps)
		return a.v < b.v;
	return a.t < b.t;
}
void normA(double& A) {
	if (A <= -pi)
		A += 2.0 * pi;
	if (A > pi)
		A -= 2.0 * pi;
}
void addarc(double lA, double rA) {
	normA(lA);
	normA(rA);
	if (lA > rA) {
		++cur;
	}
	ev[++evt] = (event) {lA, 1};
	ev[++evt] = (event) {rA, -1};
}
bool check(int cen, double R) {
	if (R < eps)
		return 1;
	cur = 0;
	evt = 0;
	for (int i = 1; i <= n; ++i)
		if (i != cen) {
			double dx = p[i].x - p[cen].x;
			double dy = p[i].y - p[cen].y;
			if (fabs(dx) < eps && fabs(dy) < eps) {
				continue;
			}
			double tht = atan2(dy, dx);
			double d = dist(p[cen], p[i]);
			if (R + R <= d) {
				continue;
			}
			double dta = acos(d / 2 / R);
			addarc(tht - dta, tht + dta);
		}
	point o = p[cen];
	if (o.x - R < 0) {
		double dta = acos(o.x / R);
		addarc(-pi - dta, -pi + dta);
		addarc(-pi - dta, -pi + dta);
	}
	if (o.x + R > w) {
		double dta = acos((w - o.x) / R);
		addarc(-dta, dta);
		addarc(-dta, dta);
	}
	if (o.y - R < 0) {
		double dta = acos(o.y / R);
		addarc(-pi / 2 - dta, -pi / 2 + dta);
		addarc(-pi / 2 - dta, -pi / 2 + dta);
	}
	if (o.y + R > h) {
		double dta = acos((h - o.y) / R);
		addarc(pi / 2 - dta, pi / 2 + dta);
		addarc(pi / 2 - dta, pi / 2 + dta);
	}
	if (cur <= 1)
		return 1;
	sort(ev + 1, ev + evt + 1, cmp_ev);
	for (int i = 1; i <= evt; ++i) {
		cur += ev[i].v;
		if (cur <= 1) {
			return 1;
		}
	}
	return 0;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("cf.in" , "r", stdin);
	freopen("cf.out", "w", stdout);
#endif
	scanf("%lf %lf %d", &w, &h, &n);
	for (int i = 1; i <= n; ++i) {
		p[i].init();
	}
	random_shuffle(p + 1, p + n + 1);
	for (int i = 1; i <= n; ++i) {
		if (!check(i, ans + 1e-9)) {
			continue;
		}
		double rmax = hypot(w, h), delta = rmax - ans;
		while (delta > eps) {
			double mm = (ans + rmax) / 2;
			if (check(i, mm)) {
				ans = mm;
			} else {
				rmax = mm;
			}
			delta /= 2.0;
		}
	}
	printf("%.12lf\n", ans);
}
