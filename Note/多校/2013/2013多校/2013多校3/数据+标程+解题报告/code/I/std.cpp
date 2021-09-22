#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-10;
inline int sign(double a) {
	return a < -EPS ? -1 : a > EPS;
}

struct Point {
	double x, y;
	Point() {
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
		while (qs.size() > t && crossOp(qs[qs.size()-2],qs.back(),ps[i]) <= 0)
			qs.pop_back();
	}
	qs.pop_back();
	return qs;
}

typedef vector<Point> Poly;

const int MAX_N = 50 + 1;
int n;

Poly tri[MAX_N];

Poly readTri() {
	Poly ret;
	for (int i = 0; i < 3; ++i) {
		Point p;
		cin >> p.x >> p.y;
		ret.push_back(p);
	}
	return convexHull(ret);
}

vector<pair<int, Poly> > add(vector<pair<int, Poly> > am, Poly tri) {
	vector<pair<int, Poly> > nam;
	for (int i = 0; i < am.size(); ++i) {
		int cnt = am[i].first;
		Poly ps = am[i].second;
		for (int i = 0; i < tri.size(); ++i) {
			Point p1 = tri[i], p2 = tri[(i + 1) % tri.size()];
			Poly qs = convexCut(ps, p2, p1);
			ps = convexCut(ps, p1, p2);
			if (calcArea(qs) > EPS) {
				nam.push_back(make_pair(cnt, qs));
			}
			if (calcArea(ps) <= EPS)
				break;
		}
		if (calcArea(ps) > EPS) {
			nam.push_back(make_pair(cnt + 1, ps));
		}
	}
	return nam;
}

//[0,100]
int BIG = 200;

void work() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		tri[i] = readTri();
	}
	vector<pair<int, Poly> > am;
	Poly bigSqaure;
	bigSqaure.push_back(Point(0, 0));
	bigSqaure.push_back(Point(200, 0));
	bigSqaure.push_back(Point(200, 200));
	bigSqaure.push_back(Point(0, 200));

	am.push_back(make_pair(0, bigSqaure));

	for (int i = 0; i < n; ++i) {
		if (calcArea(tri[i]) > EPS)
			am = add(am, tri[i]);
	}

	double ans[MAX_N] = { };
	for (int i = 0; i < am.size(); ++i) {
		ans[am[i].first] += calcArea(am[i].second);
	}

	for (int i = 1; i <= n; ++i) {
		printf("%0.10lf\n", ans[i]);
	}
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
