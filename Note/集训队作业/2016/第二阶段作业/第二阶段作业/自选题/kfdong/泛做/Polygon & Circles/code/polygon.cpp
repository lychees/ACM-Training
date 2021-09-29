#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define fir first
#define sec second
#define mkp make_pair
using namespace std;

const double PI = acos(-1);

const int MaxN = 55;
class Point {
public:
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	double len() {
		return sqrt(x * x + y * y);
	}
	friend Point operator * (const Point &a, const double &b) {
		return Point(a.x * b, a.y * b);
	}
}	H[MaxN], P[MaxN];
double cross(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}
double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}
class circle : public Point {
public:
	double r;
	friend bool operator < (const circle &a, const circle &b) {
		if (a.x != b.x) return a.x < b.x;
		if (a.y != b.y) return a.y < b.y;
		return a.r < b.r;
	}
}	C[MaxN];
int N, M;

inline double integrate_arc(double a, double b, double r, double tl, double tr) {
	return 0.5 * r * (a * (sin(tr) - sin(tl)) + b * (cos(tl) - cos(tr)) + r * (tr - tl));
}

#define sqr(x) ((x) * (x))
struct triple {
	double key;
	int a, b;
	triple() {}
	triple(double key, int a, int b) : key(key), a(a), b(b) {}
	friend bool operator < (const triple &a, const triple &b) {
		return a.key < b.key;
	}
};
double Calc_union_circle(int pos) {
	static triple H[MaxN << 3];
	double ret = 0;
	int cnt = 0, cedge = 0, Htot = 0;
	for (int i = 1; i <= N; ++i)
		if (i != pos) {
			double dist = (C[i] - C[pos]).len();
			if (dist <= C[i].r - C[pos].r) return 0;
			if (dist >= C[i].r + C[pos].r) continue;
			if (dist <= C[pos].r - C[i].r) continue;
			double ang = atan2(C[i].y - C[pos].y, C[i].x - C[pos].x), 
				thita = acos((sqr(C[pos].r) + sqr(dist) - sqr(C[i].r)) / (2 * C[pos].r * dist));
			double l = ang - thita, r = ang + thita;
			if (r > PI) r -= 2 * PI;
			if (l < -PI) l += 2 * PI;
			if (r < l) {
				cnt++;
				H[++Htot] = triple(r, -1, 0);
				H[++Htot] = triple(l, 1, 0);
			} else {
				H[++Htot] = triple(l, 1, 0);
				H[++Htot] = triple(r, -1, 0);
			}
		}
	int edge = 0;
	for (int i = 1; i <= M; ++i) {
		double len = (P[i + 1] - P[i]).len(), dist = -(cross(P[i + 1] - P[i], C[pos] - P[i])) / len;
		if ((fabs(dist) >= C[pos].r)) {
			if (cross(P[i + 1] - P[i], C[pos] - P[i]) < 0) return 0;
			continue;
		}
		++edge;
		double ang = atan2(- P[i + 1].x + P[i].x, P[i + 1].y - P[i].y), thita = acos(dist / C[pos].r);
		Point f = C[pos] + Point(cos(ang), sin(ang)) * C[pos].r;
//		printf("%.5lf %.5lf %.5lf\n", f.x, f.y, ang);
		if (cross(P[i + 1] - P[i], f - P[i]) < 0) {
			ang = PI + ang;
		}
		if (ang > PI) ang -= 2 * PI;
		double l = ang - thita, r = ang + thita;
		if (r > PI) r -= 2 * PI;
		if (l < -PI) l += 2 * PI;
		if (r < l) {
			cedge++;
			H[++Htot] = triple(r, 0, -1);
			H[++Htot] = triple(l, 0, 1);
		} else {
			H[++Htot] = triple(l, 0, 1);
			H[++Htot] = triple(r, 0, -1);
		}
//		printf("%.5lf %.5lf %.5lf %.5lf\n", l, r, ang, thita);
	}
	sort(H + 1, H + Htot + 1);
	H[0].key = -PI;
	H[Htot + 1].key = PI;
	for (int i = 1; i <= Htot + 1; ++i) {
		if ((cnt == 0) && (cedge == edge)) {
			ret += integrate_arc(C[pos].x, C[pos].y, C[pos].r, H[i - 1].key, H[i].key);
//			printf("%.5lf %.5lf %.5lf\n", H[i - 1].key, H[i].key, ret);
		}
		cnt += H[i].a;
		cedge += H[i].b;
	}
//	cerr << ret << endl;
	return ret;
}

inline double integrate_segment(double a, double b, double kx, double ky, double l, double r) {
	return 0.5 * (a * ky - b * kx) * (r - l);
}
double Calc_union_segment(Point a, Point b) {
	static pair<double, int> H[MaxN];
	int Htot = 0;
	double len = (b - a).len();
	for (int i = 1; i <= N; ++i) {
		double dist = fabs(cross(b - a, C[i] - a)) / len;
		if (dist >= C[i].r) continue;
		double pos = dot(C[i] - a, b - a) / len, delta = sqrt(sqr(C[i].r) - sqr(dist));
		double l = max(0.0, pos - delta), r = min(len, pos + delta);
		if (l >= r) continue;
		H[++Htot] = mkp(l, -1);
		H[++Htot] = mkp(r, 1);
	}
	sort(H + 1, H + Htot + 1);
	H[0].fir = 0;
	H[Htot + 1].fir = len;
	int cnt = 0;
	double ret = 0;
	for (int i = 1; i <= Htot + 1; ++i) {
		if (cnt)
			ret += integrate_segment(a.x, a.y, (b.x - a.x) / len, (b.y - a.y) / len, H[i - 1].fir, H[i].fir);
		cnt += H[i].sec;
	}
	return ret;
}

bool cmpx (const Point &a, const Point &b) {
	return a.x < b.x;
}
int Convex_hull() {
	int Ptot = 0, m = Ptot + 1;
	sort(H + 1, H + M + 1, cmpx);
	for (int i = 1; i <= M; ++i) {
		while ((Ptot > m) && (cross(H[i] - P[Ptot - 1], P[Ptot] - P[Ptot - 1]) >= 0)) --Ptot;
		P[++Ptot] = H[i];
	}
	m = Ptot;
	for (int i = M - 1; i; --i) {
		while ((Ptot > m) && (cross(H[i] - P[Ptot - 1], P[Ptot] - P[Ptot - 1]) >= 0)) --Ptot;
		P[++Ptot] = H[i];
	}
//	for (int i = 1; i <= Ptot; ++i) printf("%.1lf %.1lf\n", P[i].x, P[i].y);
	return Ptot - 1;
}

double area_union() {
	double ret = 0;
	for (int i = 1; i <= N; ++i)
		ret += Calc_union_circle(i);
	for (int i = 1; i <= M; ++i)
		ret += Calc_union_segment(P[i], P[i + 1]);
	return ret;
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) scanf("%lf%lf%lf", &C[i].x, &C[i].y, &C[i].r);
	sort(C + 1, C + N + 1);
	int tn = 0;
	for (int i = 1; i <= N; ++i) {
		if ((i < N) && (C[i].x == C[i + 1].x) && (C[i].y == C[i + 1].y)) continue;
		C[++tn] = C[i];
	}
	N = tn;
	scanf("%d", &M);
	for (int i = 1; i <= M; ++i) scanf("%lf%lf", &H[i].x, &H[i].y);
	M = Convex_hull();

	double ans = area_union();
	printf("%.12lf\n", ans);
	return 0;
}
