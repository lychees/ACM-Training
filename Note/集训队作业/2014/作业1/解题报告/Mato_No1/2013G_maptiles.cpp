#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
const int MAXN = 52, MAXM = 11, INF0 = ~0U >> 2;
const double zero = 1e-11, INF = 1e20;
struct poi {
	double x, y;
	poi () {}
	poi (double _x, double _y): x(_x), y(_y) {}
	poi operator+ (poi p0) {return (poi) {x + p0.x, y + p0.y};}
	poi operator- (poi p0) {return (poi) {x - p0.x, y - p0.y};}
	poi operator* (double k) {return (poi) {x * k, y * k};}
} A[MAXN];
struct sss {
	int No;
	double v;
	bool operator< (sss s0) const {return v + zero < s0.v;}
} CX[MAXM][MAXN], CY[MAXM][MAXN];
int n, XS, YS, vst0[MAXN], vst1[MAXN], CX_n[MAXM], CY_n[MAXM], res = INF0;
double minx = INF, miny = INF, maxx = -INF, maxy = -INF, L0_x[MAXM][MAXN], R0_x[MAXM][MAXN], L0_y[MAXM][MAXN], R0_y[MAXM][MAXN];
bool vst[MAXN], cv0[MAXM + 2][MAXM + 1], cv1[MAXM + 1][MAXM + 2];
void init()
{
	scanf("%d%d%d", &n, &XS, &YS);
	re(i, n) scanf("%lf%lf", &A[i].x, &A[i].y);
}
void prepare()
{
	poi p1, p2, p3, p4;
	re(i, n) {
		if (A[i].x + zero < minx) minx = A[i].x;
		if (A[i].y + zero < miny) miny = A[i].y;
		if (A[i].x - zero > maxx) maxx = A[i].x;
		if (A[i].y - zero > maxy) maxy = A[i].y;
		p1 = A[i]; p2 = A[i + 1]; if (i) p3 = A[i - 1]; else p3 = A[n - 1];
		vst[i] = p1.y + zero >= p2.y && p1.y - zero <= p2.y && p1.y + zero >= p3.y && p1.y - zero <= p3.y;
	}
	if (maxx - minx - zero <= XS && maxy - miny - zero <= YS) {res = 1; return;}
	int _n = 0; re(i, n) if (!vst[i]) A[_n++] = A[i]; A[n = _n] = A[0];
	re(i, n) {
		p1 = A[i]; p2 = A[i + 1];
		if (p1.x + zero >= p2.x && p1.x - zero <= p2.x) {
			if (i) p3 = A[i - 1]; else p3 = A[n - 1];
			if (i < n - 1) p4 = A[i + 2]; else p4 = A[1];
			vst0[i] = (p3.x + zero < p1.x && p4.x + zero < p1.x || p3.x - zero > p1.x && p4.x - zero > p1.x) + 1;
		} else vst0[i] = 0;
		if (p1.y + zero >= p2.y && p1.y - zero <= p2.y) {
			if (i) p3 = A[i - 1]; else p3 = A[n - 1];
			if (i < n - 1) p4 = A[i + 2]; else p4 = A[1];
			vst1[i] = (p3.y + zero < p1.y && p4.y + zero < p1.y || p3.y - zero > p1.y && p4.y - zero > p1.y) + 1;
		} else vst1[i] = 0;
	}
}
void sol0(poi p0)
{
	int lx, rx, ly, ry;
	double _v = floor((minx - p0.x) / XS + zero); if (_v > zero) lx = (int) (_v + zero); else lx = (int) (_v - zero);
	_v = floor((miny - p0.y) / YS + zero); if (_v > zero) ly = (int) (_v + zero); else ly = (int) (_v - zero);
	_v = ceil((maxx - p0.x) / XS - zero); if (_v > zero) rx = (int) (_v + zero) - 1; else rx = (int) (_v - zero) - 1;
	_v = ceil((maxy - p0.y) / YS - zero); if (_v > zero) ry = (int) (_v + zero) - 1; else ry = (int) (_v - zero) - 1;
	poi p1, p2, p3; double _x, _y; int nx = 0, ny = 0, _n, __n, _; bool FF0;
	re3(i, lx+1, rx) {
		_x = p0.x + i * XS; _n = 0;
		re(j, n) {
			p1 = A[j]; p2 = A[j + 1];
			if (p1.x + zero >= _x && p1.x - zero <= _x && p2.x + zero >= _x && p2.x - zero <= _x) {
				CX[nx][_n].No = j; CX[nx][_n++].v = p1.y + zero < p2.y ? p1.y : p2.y;
			} else if (p1.x + zero < _x && p2.x - zero > _x || p1.x - zero > _x && p2.x + zero < _x) {
				CX[nx][_n].No = j; CX[nx][_n++].v = p1.y + (_x - p1.x) / (p2.x - p1.x) * (p2.y - p1.y);
			} else if (p1.x + zero >= _x && p1.x - zero <= _x) {
				if (j) p3 = A[j - 1]; else p3 = A[j];
				if (p2.x + zero < _x && p3.x - zero > _x || p2.x - zero > _x && p3.x + zero < _x) {CX[nx][_n].No = j; CX[nx][_n++].v = p1.y;}
			}
		}
		sort(CX[nx], CX[nx] + _n); __n = FF0 = 0;
		re(j, _n) {
			_ = CX[nx][j].No; _y = CX[nx][j].v;
			if (!vst0[_]) {
				if (FF0) R0_x[nx][__n++] = _y; else L0_x[nx][__n] = _y; FF0 = !FF0;
			} else {
				if (_y + zero >= A[_].y && _y - zero <= A[_].y) _v = A[_ + 1].y; else _v = A[_].y;
				if (vst0[_] == 1) {
					if (FF0) R0_x[nx][__n++] = _y; else L0_x[nx][__n] = _v; FF0 = !FF0;
				} else {
					if (FF0) {R0_x[nx][__n++] = _y; L0_x[nx][__n] = _v;}
				}
			}
		}
		CX_n[nx++] = __n;
	}
	re3(i, ly+1, ry) {
		_y = p0.y + i * YS; _n = 0;
		re(j, n) {
			p1 = A[j]; p2 = A[j + 1];
			if (p1.y + zero >= _y && p1.y - zero <= _y && p2.y + zero >= _y && p2.y - zero <= _y) {
				CY[ny][_n].No = j; CY[ny][_n++].v = p1.x + zero < p2.x ? p1.x : p2.x;
			} else if (p1.y + zero < _y && p2.y - zero > _y || p1.y - zero > _y && p2.y + zero < _y) {
				CY[ny][_n].No = j; CY[ny][_n++].v = p1.x + (_y - p1.y) / (p2.y - p1.y) * (p2.x - p1.x);
			} else if (p1.y + zero >= _y && p1.y - zero <= _y) {
				if (j) p3 = A[j - 1]; else p3 = A[j];
				if (p2.y + zero < _y && p3.y - zero > _y || p2.y - zero > _y && p3.y + zero < _y) {CY[ny][_n].No = j; CY[ny][_n++].v = p1.x;}
			}
		}
		sort(CY[ny], CY[ny] + _n); __n = FF0 = 0;
		re(j, _n) {
			_ = CY[ny][j].No; _x = CY[ny][j].v;
			if (!vst1[_]) {
				if (FF0) R0_y[ny][__n++] = _x; else L0_y[ny][__n] = _x; FF0 = !FF0;
			} else {
				if (_x + zero >= A[_].x && _x - zero <= A[_].x) _v = A[_ + 1].x; else _v = A[_].x;
				if (vst1[_] == 1) {
					if (FF0) R0_y[ny][__n++] = _x; else L0_y[ny][__n] = _v; FF0 = !FF0;
				} else {
					if (FF0) {R0_y[ny][__n++] = _x; L0_y[ny][__n] = _v;}
				}
			}
		}
		CY_n[ny++] = __n;
	}
	int __l, __r;
	re(i, nx+2) re(j, ny+1) cv0[i][j] = 0;
	re(i, ny+2) re(j, nx+1) cv1[i][j] = 0;
	_x = p0.x + lx * XS; _y = p0.y + ly * YS;
	re(i, nx) {
		__n = CX_n[i];
		re(j, __n) {
			__l = (int) (floor((L0_x[i][j] - _y) / YS + zero) + zero); __r = (int) (ceil((R0_x[i][j] - _y) / YS - zero) + zero);
			re2(k, __l, __r) cv0[i + 1][k] = 1;
		}
	}
	re(i, ny) {
		__n = CY_n[i];
		re(j, __n) {
			__l = (int) (floor((L0_y[i][j] - _x) / XS + zero) + zero); __r = (int) (ceil((R0_y[i][j] - _x) / XS - zero) + zero);
			re2(k, __l, __r) cv1[i + 1][k] = 1;
		}
	}
	nx++; ny++; _n = 0;
	re(i, ny) re(j, nx) {
		_n += cv0[j][i] || cv1[i][j] || cv0[j + 1][i] || cv1[i + 1][j];
		if (_n >= res) return;
	}
	res = _n;
}
void solve()
{
	re(i, n) re(j, n) if (i != j) sol0((poi) {A[j].x, A[i].y});
	double _x1, _x2, _y1, _y2, _tmp; int __x1, __x2, __y1, __y2;
	re(i, n) re(j, n) if (A[j].y + zero < A[j + 1].y || A[j].y - zero > A[j + 1].y) {
		_y1 = (A[i].y - A[j].y) / YS; _y2 = (A[i].y - A[j + 1].y) / YS; if (_y1 + zero > _y2) {_tmp = _y1; _y1 = _y2; _y2 = _tmp;}
		if (_y1 - zero > -1) __y1 = (int) (ceil(_y1 - zero) + zero); else __y1 = (int) (ceil(_y1 - zero) - zero);
		if (_y2 > zero) __y2 = (int) (floor(_y2 + zero) + zero); else __y2 = (int) (floor(_y2 + zero) - zero);
		re3(k, __y1, __y2) {
			_tmp = A[i].y - k * YS; sol0((poi) {A[j].x + (A[j + 1].x - A[j].x) / (A[j + 1].y - A[j].y) * (_tmp - A[j].y), A[i].y});
		}
	}
	re(i, n) re(j, n) if (A[j].x + zero < A[j + 1].x || A[j].x - zero > A[j + 1].x) {
		_x1 = (A[i].x - A[j].x) / XS; _x2 = (A[i].x - A[j + 1].x) / XS; if (_x1 + zero > _x2) {_tmp = _x1; _x1 = _x2; _x2 = _tmp;}
		if (_x1 - zero > -1) __x1 = (int) (ceil(_x1 - zero) + zero); else __x1 = (int) (ceil(_x1 - zero) - zero);
		if (_x2 > zero) __x2 = (int) (floor(_x2 + zero) + zero); else __x2 = (int) (floor(_x2 + zero) - zero);
		re3(k, __x1, __x2) {
			_tmp = A[i].x - k * XS; sol0((poi) {A[i].x, A[j].y + (A[j + 1].y - A[j].y) / (A[j + 1].x - A[j].x) * (_tmp - A[j].x)});
		}
	}
	double _a1, _b1, _c1, _a2, _b2, _c2, t1, t2;
	re(i, n) re(j, n) if (i != j) re3(k1, -MAXM, MAXM) re3(k2, -MAXM, MAXM) {
		_a1 = A[i + 1].x - A[i].x; _b1 = A[j].x - A[j + 1].x; _c1 = A[i].x - A[j].x - k1 * XS;
		_a2 = A[i + 1].y - A[i].y; _b2 = A[j].y - A[j + 1].y; _c2 = A[i].y - A[j].y - k2 * YS;
		_tmp = _a1 * _b2 - _a2 * _b1;
		if (_tmp > zero || _tmp < -zero) {
			t1 = (_c2 * _b1 - _c1 * _b2) / _tmp; t2 = (_c1 * _a2 - _c2 * _a1) / _tmp;
			if (t1 >= -zero && t1 - zero <= 1 && t2 >= -zero && t2 - zero <= 1) sol0(A[i] + (A[i + 1] - A[i]) * t1);
		}
	}
}
void pri()
{
	printf("%d\n", res);
}
int main()
{
	init();
	prepare();
	if (res == INF0) solve();
	pri();
	return 0;
}

