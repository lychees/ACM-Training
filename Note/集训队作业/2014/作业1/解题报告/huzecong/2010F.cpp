//ACM/ICPC World Finals 2010 F Contour Mapping
#include <cstdio>
#include <algorithm>
#include <cmath> 
using namespace std;

#define N 100
int a[N + 1][N + 2], n, m, d, h, _n, _m;
struct triangle {
	int a, b, c, type;
	triangle() {}
	triangle(int _a, int _b, int _c) : a(_a), b(_b), c(_c), type(0) {}
} t[N + 1][N << 1 | 1];

// 1 or 2 or 3 vertexes with the same height
//Standardize as well
inline int type(triangle &x) {
	if (x.a == x.b && x.a == x.c) return 3;
	if (x.a == x.c) swap(x.b, x.c);
	if (x.b == x.c) swap(x.a, x.c);
	if (x.a == x.b) return 2;
	return 1;
}

//a, b, c being the 3 sides of a triangle, and h1 and h2 being the height of the edge and the point
//Side b is the important side
inline double calc(double a, double b, double c, int h1, int h2) {
	if (h1 == h2) return 0.0;
	int l, r, u = max(h1, h2), d = min(h1, h2), k;
	double L, R;
	l = h1 - h1 % h, r = h2 - h2 % h;
	if (l < d) l += h;
	if (r < d) r += h;
	if (l > u && r > u) return 0.0;
	if (l > r) swap(l, r);
	k = (r - l) / h + 1;
	L = (double)(h2 - l) * b / (h2 - h1);
	R = (double)(h2 - r) * b / (h2 - h1);
	return (L + R) * k / 2.0;
}

inline double calc(const triangle &x) {
	if (x.type == 2) {
		double _d = (double)d * (abs(x.a - x.c) - 1) / abs(x.a - x.c);
		if (x.a > x.c) return calc(d, _d, d, x.a - 1, x.c);
		return calc(d, _d, d, x.a + 1, x.c);
	}
	int a = x.a, b = x.b, c = x.c;
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	double p = (double)d * (b - a) / (c - a);
	double m = sqrt((double)d * d + p * p - p * d);
	double ret = calc(p, m, d, b, a) + calc(d - p, m, d, b, c);
	if (!(b % h)) ret -= m;
	return ret;
}

inline bool check(int x, int y, int i, int j) {
	if (i < 1 || i > _n) return false;
	if (j < 1 || j > _m + 1) return false;
	if ((i & 1) && (j > _m)) return false;
	if (a[x][y] != a[i][j] || (a[x][y] % h)) return false;
	return true;
}

inline bool check2(int x, int y, int i, int j) {
	if (x < 1 || x > n || y < 1 || y > m) return true;
	else if (i < 1 || i > n || j < 1 || j > m) return true;
	else return t[x][y].type != 3 || t[i][j].type != 3;
}

int main(int argc, char* argv[]) {
#ifdef KANARI
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	scanf("%d%d%d%d", &n, &m, &d, &h);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);
		if (!(i & 1)) scanf("%d", &a[i][m + 1]);
	}
	
	for (int i = 1; i < n; ++i)
		if (i & 1) {
			for (int j = 1; j < m; ++j) {
				t[i][j * 2 - 1] = triangle(a[i][j], a[i + 1][j], a[i + 1][j + 1]);
				t[i][j * 2] = triangle(a[i][j], a[i][j + 1], a[i + 1][j + 1]);
			}
			t[i][m * 2 - 1] = triangle(a[i][m], a[i + 1][m], a[i + 1][m + 1]);
		} else {
			for (int j = 1; j < m; ++j) {
				t[i][j * 2 - 1] = triangle(a[i][j], a[i][j + 1], a[i + 1][j]);
				t[i][j * 2] = triangle(a[i][j + 1], a[i + 1][j], a[i + 1][j + 1]);
			}
			t[i][m * 2 - 1] = triangle(a[i][m], a[i + 1][m], a[i][m + 1]);
		}
	_n = n, _m = m;
	--n, m = m * 2 - 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			t[i][j].type = type(t[i][j]);
	
	double ans = 0;
	//Deal with normal triangles
	//Ignore contour lines on the edge
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (t[i][j].type != 3) ans += calc(t[i][j]);
	//Lines on borders
	for (int i = 1; i <= _n; ++i)
		for (int j = 1; j <= _m + !(i & 1); ++j)
			if (i & 1) {
				if (check(i, j, i + 1, j) && check2(i, j * 2 - 1, i, j * 2 - 2)) ans += d;
				if (check(i, j, i + 1, j + 1) && check2(i, j * 2, i - 1, j * 2)) ans += d;
				if (check(i, j, i, j + 1) && check2(i, j * 2 - 1, i, j * 2)) ans += d;
			} else {
				if (check(i, j, i + 1, j - 1) && check2(i, j * 2 - 2, i, j * 2 - 3)) ans += d;
				if (check(i, j, i + 1, j) && check2(i, j * 2 - 2, i, j * 2 - 1)) ans += d;
				if (check(i, j, i, j + 1) && check2(i, j * 2 - 1, i - 1, j * 2 - 1)) ans += d;
			}
	
	printf("%.0lf\n", round(ans));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

