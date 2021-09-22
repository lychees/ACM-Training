#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

const int maxn = 22222, maxm = 55;
const double eps = 1e-10, pi = acos(-1.0);
struct point_t {
	double x, y;
	point_t() { }
	point_t(double tx, double ty) : x(tx), y(ty) { }
	point_t operator-(const point_t &r) {
		return point_t(x - r.x, y - r.y);
	}
	point_t operator+(const point_t &r) {
		return point_t(x + r.x, y + r.y);
	}
	point_t operator*(const double r) {
		return point_t(x * r, y * r);
	}
	point_t operator/(const double r) {
		return point_t(x / r, y / r);
	}
	void read() { scanf("%lf%lf", &x, &y); }
};

int dblcmp(double x) {
	return (x < -eps ? -1 : x > eps);
}

double dist(point_t p1, point_t p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double cross(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

double cross(point_t p1, point_t p2) {
	return cross(p1.x, p1.y, p2.x, p2.y);
}

double dot(double x1, double y1, double x2, double y2) {
	return x1 * x2 + y1 * y2;
}

double dot(point_t p1, point_t p2) {
	return dot(p1.x, p1.y, p2.x, p2.y);
}

double angle(double x1, double y1, double x2, double y2) {
	y2 -= y1, x2 -= x1;
	return atan2(y2, x2);
}

double angle(point_t p1, point_t p2) {
	return angle(p1.x, p1.y, p2.x, p2.y);
}

struct circle_t {
	point_t center;
	double radius;
} cir[maxm];
struct triangle_t {
	point_t p1, p2, p3;
} tri[maxm];
int tests, n, m, cnt;
pair<point_t, int> p[maxn];

bool cmp(const pair<point_t, int> &p1, const pair<point_t, int> &p2) {
	return dblcmp(p1.first.y - p2.first.y) == 0 ? p1.first.x < p2.first.x : p1.first.y < p2.first.y;
}

int graham() {
	int top = 0;
	static pair<point_t, int> sk[maxn];
	sort(p + 1, p + 1 + cnt, cmp);
	top = 2, sk[1] = p[1], sk[2] = p[2];
	for (int i = 3; i <= cnt; ++i) {
		while (top >= 2 && dblcmp(cross(p[i].first - sk[top - 1].first, sk[top].first - sk[top - 1].first)) >= 0) --top;
		sk[++top] = p[i];
	}
	int ttop = top;
	for (int i = cnt - 1; i >= 1; --i) {
		while (top > ttop && dblcmp(cross(p[i].first - sk[top - 1].first, sk[top].first - sk[top - 1].first)) >= 0) --top;
		sk[++top] = p[i];
	}
	--top;
	for (int i = 1; i <= top; ++i) p[i] = sk[i];
	return top;
}

void makeCircle(circle_t cir1, circle_t cir2, int i, int j) {
	double d = dist(cir1.center, cir2.center), dr = cir1.radius - cir2.radius;
	double b = acos(dr / d);
	double a = angle(cir1.center, cir2.center);
	double a1 = a - b, a2 = a + b;
	p[++cnt].first = point_t(cos(a1) * cir1.radius, sin(a1) * cir1.radius) + cir1.center;
	p[cnt].second = i;
	p[++cnt].first = point_t(cos(a2) * cir1.radius, sin(a2) * cir1.radius) + cir1.center;
	p[cnt].second = i;
}

void makeCircleTriangle(circle_t cir, point_t pt, int i, int j) {
	double d = dist(cir.center, pt);
	double b = acos(cir.radius / d);
	double a = angle(cir.center, pt);
	double a1 = a - b, a2 = a + b;
	p[++cnt].first = point_t(cos(a1) * cir.radius, sin(a1) * cir.radius) + cir.center;
	p[cnt].second = i;
	p[++cnt].first = point_t(cos(a2) * cir.radius, sin(a2) * cir.radius) + cir.center;
	p[cnt].second = i;
}

void makeCircleTriangle(circle_t cir, triangle_t tri, int i, int j) {
	makeCircleTriangle(cir, tri.p1, i, j);
	makeCircleTriangle(cir, tri.p2, i, j);
	makeCircleTriangle(cir, tri.p3, i, j);
}

void make() {
	cnt = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			makeCircle(cir[i], cir[j], i, j);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			makeCircleTriangle(cir[i], tri[j], i, j);
		}
	}
	for (int i = 1; i <= m; ++i) {
		p[++cnt].first = tri[i].p1; p[cnt].second = -1;
		p[++cnt].first = tri[i].p2; p[cnt].second = -1;
		p[++cnt].first = tri[i].p3; p[cnt].second = -1;
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			cir[i].center.read();
			scanf("%lf", &cir[i].radius);
		}
		for (int i = 1; i <= m; ++i) {
			tri[i].p1.read();
			tri[i].p2.read();
			tri[i].p3.read();
		}
		if (n == 1 && m == 0) { // Tricky case: n == 1 && m == 0
			printf("%.10lf\n", 2 * pi * cir[1].radius);
			#ifdef DEBUG
			printf("0\n");
			#endif
		} else {
			make();
			cnt = graham();
			p[0] = p[cnt];
			double res = 0;
			for (int i = 0; i < cnt; ++i) {
				if (p[i].second != -1 && p[i].second == p[i + 1].second) {
					int c = p[i].second;
					point_t p1 = p[i].first - cir[c].center, p2 = p[i + 1].first - cir[c].center;
					double a1 = atan2(p1.y, p1.x), a2 = atan2(p2.y, p2.x);
					a2 -= a1;
					if (a2 < 0) a2 += 2 * pi;
					res += a2 * cir[c].radius;
				} else {
					res += dist(p[i].first, p[i + 1].first);
				}
			}
			printf("%.10f\n", res);
			#ifdef DEBUG
			printf("%d\n", cnt);
			for (int i = 0; i < cnt; ++i) {
				printf("%.10f %.10f\n", p[i].first.x, p[i].first.y);
			}
			#endif
		}
	}
	return 0;
}
