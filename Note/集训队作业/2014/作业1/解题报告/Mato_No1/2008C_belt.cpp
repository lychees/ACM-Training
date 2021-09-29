#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <list>
#include <utility>
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
const int MAXN0 = 22, MAXN = MAXN0 * MAXN0 + 2;
const double pi = acos(-1.0), zero = 1e-15, zero2 = 1e-7, INF = 1e20;
typedef list <pair<int, double> >::iterator li;
struct poi {
	double x, y;
	poi operator+ (poi p0) {return (struct poi) {x + p0.x, y + p0.y};}
	poi operator- (poi p0) {return (struct poi) {x - p0.x, y - p0.y};}
	poi operator* (double k) {return (struct poi) {x * k, y * k};}
} A[MAXN], B[MAXN];
struct sss0 {
	poi o;
	int r; bool FF;
} A0[MAXN0];
list <pair<int, double> > E[MAXN], E2[MAXN];
int n0, n, s0, t0, _A[MAXN], _B[MAXN], Q[MAXN + 1];
double maxd, _W[MAXN], D0[MAXN], res;
bool crs[MAXN][MAXN], vst[MAXN];
double len(poi p)
{
	return sqrt(p.x * p.x + p.y * p.y);
}
double cr(poi p1, poi p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}
poi rot(poi p, double cos0, double sin0)
{
	return (struct poi) {p.x * cos0 - p.y * sin0, p.x * sin0 + p.y * cos0};
}
bool cross0(poi p1, poi p2, int No)
{
	poi _p = p2 - p1, __p = p1 - A0[No].o;
	double _a = _p.x * _p.x + _p.y * _p.y, _b = _p.x * __p.x + _p.y * __p.y, _c = __p.x * __p.x + __p.y * __p.y - A0[No].r * A0[No].r; _b += _b;
	double delt = _b * _b - 4 * _a * _c;
	if (delt > zero2) {
		delt = sqrt(delt); double t1 = (-_b - delt) / _a * 0.5, t2 = (-_b + delt) / _a * 0.5;
		return t1 > zero && t1 + zero < 1 || t2 > zero && t2 + zero < 1;
	} else return 0;
}
bool is_cross(poi p1, poi p2, poi p3, poi p4)
{
	poi _p1 = p2 - p1, _p2 = p4 - p3;
	double a1 = _p1.x, b1 = -_p2.x, c1 = p1.x - p3.x, a2 = _p1.y, b2 = -_p2.y, c2 = p1.y - p3.y, _ = a1 * b2 - a2 * b1;
	if (_ >= -zero2 && _ <= zero2) return 0; else {
		double t1 = (c2 * b1 - c1 * b2) / _, t2 = (c1 * a2 - c2 * a1) / _;
		return t1 >= -zero && t1 - zero <= 1 && t2 >= -zero && t2 - zero <= 1;
	}
}
void prepare()
{
	double d, cos0, sin0, _; poi a, b, _p, _p2; bool FF0; n = 0;
	re(i, n0) re(j, n0) if (i != j) {
		if (A0[i].FF && A0[j].FF) {
			_p = A0[j].o - A0[i].o; d = len(_p);
			cos0 = (A0[i].r - A0[j].r) / d; sin0 = -sqrt(1 - cos0 * cos0);
			_p2 = rot(_p, cos0, sin0); a = A0[i].o + _p2 * (A0[i].r / d);
			_p.x = -_p.x; _p.y = -_p.y;
			cos0 = (A0[j].r - A0[i].r) / d; sin0 = sqrt(1 - cos0 * cos0);
			_p2 = rot(_p, cos0, sin0); b = A0[j].o + _p2 * (A0[j].r / d);
		} else if (A0[i].FF) {
			_p = A0[j].o - A0[i].o; d = len(_p);
			cos0 = (A0[i].r + A0[j].r) / d; sin0 = -sqrt(1 - cos0 * cos0);
			_p2 = rot(_p, cos0, sin0); a = A0[i].o + _p2 * (A0[i].r / d);
			_p.x = -_p.x; _p.y = -_p.y;
			_p2 = rot(_p, cos0, sin0); b = A0[j].o + _p2 * (A0[j].r / d);
		} else if (A0[j].FF) {
			_p = A0[j].o - A0[i].o; d = len(_p);
			cos0 = (A0[i].r + A0[j].r) / d; sin0 = sqrt(1 - cos0 * cos0);
			_p2 = rot(_p, cos0, sin0); a = A0[i].o + _p2 * (A0[i].r / d);
			_p.x = -_p.x; _p.y = -_p.y;
			_p2 = rot(_p, cos0, sin0); b = A0[j].o + _p2 * (A0[j].r / d);
		} else {
			_p = A0[j].o - A0[i].o; d = len(_p);
			cos0 = (A0[i].r - A0[j].r) / d; sin0 = sqrt(1 - cos0 * cos0);
			_p2 = rot(_p, cos0, sin0); a = A0[i].o + _p2 * (A0[i].r / d);
			_p.x = -_p.x; _p.y = -_p.y;
			cos0 = (A0[j].r - A0[i].r) / d; sin0 = -sqrt(1 - cos0 * cos0);
			_p2 = rot(_p, cos0, sin0); b = A0[j].o + _p2 * (A0[j].r / d);
		}
		d = len(a - b);
		if (d + zero2 < maxd) {
			FF0 = 1;
			re(k, n0) if (k != i && k != j && cross0(a, b, k)) {FF0 = 0; break;}
			if (FF0) {
				_A[n] = i; _B[n] = j; A[n] = a; B[n] = b; _W[n++] = d;
			}
		}
	}
	re(i, n+2) {E[i].clear(); E2[i].clear();} _W[n] = _W[n + 1] = 0; 
	re(i, n) re(j, n) {
		crs[i][j] = is_cross(A[i], B[i], A[j], B[j]);
		if (_B[i] == _A[j]) {
			if (B[i].x - A[j].x >= -zero && B[i].x - A[j].x <= zero && B[i].y - A[j].y >= -zero && B[i].y - A[j].y <= zero) {
				E[i].push_back(make_pair(j, 0));
			} else {
				_ = len(B[i] - A[j]) * len(B[i] - A[j]); _ = acos(1 - _ / (A0[_B[i]].r * A0[_A[j]].r) * 0.5);
				if (cr(B[i] - A0[_B[i]].o, A[j] - A0[_A[j]].o) > zero2) {
					if (A0[_B[i]].FF) d = _; else d = pi + pi - _;
				} else {
					if (A0[_B[i]].FF) d = pi + pi - _; else d = _;
				}
				E[i].push_back(make_pair(j, d * A0[_B[i]].r));
			}
		}
	}
	re(i, n) crs[n][i] = crs[i][n] = crs[n + 1][i] = crs[i][n + 1] = 0;
	re(i, n) {
		if (_A[i] == s0) E[n].push_back(make_pair(i, 0));
		if (_B[i] == t0) E[i].push_back(make_pair(n + 1, 0));
	}
	n += 2; li end0;
	re(i, n) {
		end0 = E[i].end();
		for (li j=E[i].begin(); j!=end0; j++) E2[j->first].push_back(make_pair(i, j->second));
	}
	re(i, n-1) {D0[i] = INF; vst[i] = 0;} D0[n - 1] = 0; Q[0] = n - 1; vst[n - 1] = 1; int x, y;
	for (int front=0, rear=0; !(!front && rear==n || front==rear+1); front==n ? front=0 : front++) {
		x = Q[front]; end0 = E2[x].end();
		for (li i=E2[x].begin(); i!=end0; i++) {
			y = i->first; _ = D0[x] + _W[y] + i->second;
			if (_ + zero < D0[y]) {
				D0[y] = _; if (!vst[y]) {vst[y] = 1; Q[rear==n ? rear=0 : ++rear] = y;}
			}
		}
		vst[x] = 0;
	}
	res = INF;
}
void solve(int dep, int x, double sum)
{
	if (sum + D0[x] - _W[x] + zero >= res) return; else if (x == n - 1) {if (sum + zero < res) res = sum; return;} else {
		li end0 = E[x].end(); int y; bool FF;
		for (li i=E[x].begin(); i!=end0; i++) {
			if (vst[y = i->first]) continue; else FF = 1;
			re(j, dep) if (crs[y][Q[j]]) {FF = 0; break;} if (!FF) continue;
			Q[dep] = y; vst[y] = 1; solve(dep + 1, y, sum + _W[y] + i->second); vst[y] = 0;
		}
	}
}
int main()
{
	int testno = 0; char ss[5]; double _;
	while (1) {
		scanf("%d", &n0); if (n0) testno++; else break;
		re(i, n0) {scanf("%lf%lf%d%s", &A0[i].o.x, &A0[i].o.y, &A0[i].r, ss); A0[i].FF = ss[1] == 'C';}
		scanf("%d%d%lf", &s0, &t0, &maxd);
		if (s0 == t0) printf("Case %d: length = 0\n", testno); else {
			prepare();
			solve(0, n - 2, 0);
			if (res > 1e15) printf("Case %d: Cannot reach destination shaft\n", testno); else {
				res = floor(res * 100 + 0.5 + zero2) * 0.01 + 1e-9; _ = floor(res);
				printf("Case %d: length = %.0lf", testno, _ + zero);
				if (res - _ > zero2) {
					printf(".%d", (int) (((floor(res * 10) + zero2) / 10 - _) * 10 + zero2)); res *= 10; _ = floor(res);
					if (res - _ > zero2) printf("%d", (int) (((floor(res * 10) + zero2) / 10 - _) * 10 + zero2));
				}
				puts("");
			}
		}
	}
	return 0;
}

