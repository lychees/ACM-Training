#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>
#include<iomanip>
#include<iostream>
#define VI vector<Tscanpoint>::iterator 
using namespace std;
const int MAXN = 100001; 
const double eps = 1e-10;
double p[MAXN * 10];
int dcmp(double t)
{
	if (fabs(t) < eps) return 0;
	if (t < 0) return -1;
	return 1;
}
struct Tline{
	double k, b, s, e; int kind;
	void init(double x1, double y1, double x2, double y2)
	{
		k = (y2 - y1) / (x2 - x1);
		b = y1 - k * x1;
		s = min(x1, x2);
		e = max(x1, x2);
	}
	bool online(double x) { return dcmp(x - s) >= 0 && dcmp(e - x) >= 0; }
	bool inc(double l, double r) { return online(l) && online(r); }
	double value(double x) { return k * x + b; }
	double intersect(const Tline & a) { return (a.b - b) / (k - a.k); }
} line[100001];
struct Tscanpoint{
	double l, r; int kind;
	bool operator < (const Tscanpoint & A) const 
	{ 
		int t = dcmp(l - A.l); if (t != 0) return t == -1;
		t = dcmp(r - A.r); if (t != 0) return t == -1;
		return kind > A.kind;
	}
	void init(double _l, double _r, int _kind) { l = _l; r = _r; kind = _kind; }	
};
double ans[100001];

struct Tinterval{
	double l, r;
	vector<Tscanpoint> s;
	void add(Tline a)
	{
		Tscanpoint temp; temp.init(a.value(l), a.value(r), a.kind);
		s.push_back(temp);
	}
	void calc()
	{
		int now = 0; double l0, r0, l1, r1;
		sort(s.begin(), s.end());
		for (VI vi = s.begin(); vi != s.end(); vi++){
			if (now == 0) ++now; 
			else{ 
				now += vi->kind;
				l1 = vi->l; r1 = vi->r;
				ans[now - vi->kind] += (l1 + r1 - l0 - r0) * (r - l) / 2;
			}
			l0 = vi->l; r0 = vi->r;
		}
		s.clear();
	}
} interval[100001];
int linenum, tot, n;
void CLJZHIYOU5DM()
{
	tot = linenum = 0;
	memset(ans, 0, sizeof ans);
}

int main()
{
//freopen("temp.in", "r", stdin);
//freopen("temp.out", "w", stdout);

int TEST; scanf("%d", &TEST);
while(TEST--){
	CLJZHIYOU5DM();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		double x[3], y[3];
		for (int i = 0; i < 3; i++) scanf("%lf%lf", &x[i], &y[i]);
		for (int i = 0; i < 3; i++) p[++tot] = x[i];
		for (int i = 0; i < 3; i++)
			for (int j = i + 1; j < 3; j++) if (dcmp(x[i] - x[j]) != 0){
				Tline temp; temp.init(x[i], y[i], x[j], y[j]);
				if (dcmp(temp.value(x[3 - i - j]) - y[3 - i - j]) > 0)
					temp.kind = -1; else temp.kind = 1;
				line[++linenum] = temp;
				}
		}
	for (int i = 1; i <= linenum; i++)
		for (int j = i + 1; j <= linenum; j++)
			if (dcmp(line[i].k - line[j].k) != 0){
				double t = line[i].intersect(line[j]);
				if (line[i].online(t) && line[j].online(t)) p[++tot] = t;
				}
	sort(p + 1, p + tot + 1);
	int ttot = 1;
	for (int i = 2; i <= tot; i++) if (dcmp(p[i] - p[i - 1]) != 0) p[++ttot] = p[i];
	tot = ttot;
	for (int i = 1; i < tot; i++) interval[i].l = p[i], interval[i].r = p[i + 1];
	for (int i = 1; i <= linenum; i++)
		for (int j = 1; j < tot; j++)
			if (line[i].inc(interval[j].l, interval[j].r))
				interval[j].add(line[i]);
	for (int i = 1; i < tot; i++) interval[i].calc();
	for (int i = 1; i <= n; i++) printf("%.10lf\n", ans[i]);
}
}
