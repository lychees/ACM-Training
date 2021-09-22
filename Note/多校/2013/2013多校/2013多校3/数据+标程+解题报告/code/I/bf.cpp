#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

//n<=10

const int MAX_N = 10;
const double EPS = 1e-8;
inline int sign(double a) {
	return a < -EPS ? -1 : a > EPS;
}

struct Point {
	double x, y;
	Point() {
		x = y = 0;
	}
	Point(double _x, double _y) :
			x(_x), y(_y) {
	}
	Point operator+(const Point&p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator-(const Point&p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator*(double d) const {
		return Point(x * d, y * d);
	}
	Point operator/(double d) const {
		return Point(x / d, y / d);
	}
	bool operator<(const Point&p) const {
		int c = sign(x - p.x);
		if (c)
			return c == -1;
		return sign(y - p.y) == -1;
	}
	double dot(const Point&p) const {
		return x * p.x + y * p.y;
	}
	double det(const Point&p) const {
		return x * p.y - y * p.x;
	}
	double alpha() const {
		return atan2(y, x);
	}
	double distTo(const Point&p) const {
		double dx = x - p.x, dy = y - p.y;
		return hypot(dx, dy);
	}
	double alphaTo(const Point&p) const {
		double dx = x - p.x, dy = y - p.y;
		return atan2(dy, dx);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	double abs() {
		return hypot(x, y);
	}
	double abs2() {
		return x * x + y * y;
	}
	void write() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))

#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

Point isSS(Point p1, Point p2, Point q1, Point q2) {
	double a1 = cross(q1,q2,p1), a2 = -cross(q1,q2,p2);
	return (p1 * a2 + p2 * a1) / (a1 + a2);
}

vector<Point> convexCut(const vector<Point>&ps, Point q1, Point q2) {
	vector<Point> qs;
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		Point p1 = ps[i], p2 = ps[(i + 1) % n];
		int d1 = crossOp(q1,q2,p1), d2 = crossOp(q1,q2,p2);
		if (d1 >= 0)
			qs.push_back(p1);
		if (d1 * d2 < 0)
			qs.push_back(isSS(p1, p2, q1, q2));
	}
	return qs;
}

double calcArea(const vector<Point>&ps) {
	int n = ps.size();
	double ret = 0;
	for (int i = 0; i < n; ++i) {
		ret += ps[i].det(ps[(i + 1) % n]);
	}
	return ret / 2;
}

vector<Point> convexHull(vector<Point> ps) {
	int n = ps.size();
	if (n <= 1)
		return ps;
	sort(ps.begin(), ps.end());
	vector<Point> qs;
	for (int i = 0; i < n; qs.push_back(ps[i++])) {
		while (qs.size() > 1 && crossOp(qs[qs.size()-2],qs.back(),ps[i]) <= 0)
			qs.pop_back();
	}
	for (int i = n - 2, t = qs.size(); i >= 0; qs.push_back(ps[i--])) {
		while ((int) qs.size() > t
				&& crossOp(qs[qs.size()-2],qs.back(),ps[i]) <= 0)
			qs.pop_back();
	}
	qs.pop_back();
	return qs;
}

vector<Point> readTriangle() {
	vector<Point> ret;
	for (int i = 0; i < 3; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		ret.push_back(Point(x, y));
	}
	return convexHull(ret);
}

vector<Point> tri[MAX_N];
int n;
double dp[1 << MAX_N];
double cnt[MAX_N + 1];

vector<Point> is(vector<Point> ps, vector<Point> qs) {
	int n = qs.size();
	for (int i = 0; i < n; ++i) {
		ps = convexCut(ps, qs[i], qs[(i + 1) % n]);
	}
	return ps;
}

void work() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		tri[i] = readTriangle();
	}

	for (int i = 1; i < (1 << n); ++i) {
		vector<Point> cur;
		bool first = true;
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1) {
				if (first)
					cur = tri[j];
				else {
					cur = is(cur, tri[j]);
				}
				first = false;
			}
		}
		dp[i] = calcArea(cur);
	}

	int super = (1 << n) - 1;
	fill(cnt, cnt + n + 1, 0.0);

	for (int i = (1 << n) - 1; i >= 1; --i) {
		for (int j = i; j <= super; (++j) |= i)
			if (j > i)
				dp[i] -= dp[j];
		int num = 0;
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1)
				++num;
		}
		cnt[num] += dp[i];
	}

	for (int i = 1; i <= n; ++i) {
		printf("%0.10lf\n", cnt[i]);
	}
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
}
