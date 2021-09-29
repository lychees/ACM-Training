#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const double INF = 100000.0;
const double eps = 1e-14;
const double pi = acos(-1);
struct Point
{
    double x, y, z, r;
    void input()
    {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};
Point p1, p2, p[6];
int n;
bool visit[6];
double ans;
int dbcmp(double x)
{
    if(fabs(x) < eps)  return 0;
    if(x > 0)  return 1;
    else  return -1;
}
double Min(double x, double y)
{
    return x < y ? x : y;
}
double Max(double x, double y)
{
    return x > y ? x : y;
}
double CalV(double r)
{
    return pi*r*r*r*4/3;
}
double Dis(Point p0, Point p1)
{
    double x, y, z;
    x = p0.x - p1.x;
    y = p0.y - p1.y;
    z = p0.z - p1.z;
    return sqrt(x*x + y*y +z*z);
}
void inflat(int v)
{
    int i;
    double r = INF, dis;
    for(i = 0; i < n; i++)
        if(visit[i])
        {
            dis = Dis(p[i], p[v]);
            r = Min(r, dis-p[i].r);
        }
    r = Min(r, p[v].x-Min(p1.x, p2.x));
    r = Min(r, Max(p1.x, p2.x)-p[v].x);
    r = Min(r, p[v].y-Min(p1.y, p2.y));
    r = Min(r, Max(p1.y, p2.y)-p[v].y);
    r = Min(r, p[v].z-Min(p1.z, p2.z));
    r = Min(r, Max(p1.z, p2.z)-p[v].z);
    p[v].r = r;
}
void dfs(int x, double tot)
{
    int i;
    double vv;
    if(tot > ans)  ans = tot;
    if(x == n)  return;
    for(i = 0; i < n; i++)
        if(!visit[i])
        {
            inflat(i);
            if(dbcmp(p[i].r) <= 0)  continue;
            visit[i] = true;
            vv = CalV(p[i].r);
            dfs(x+1, tot+vv);
            visit[i] = false;
        }
}
int main()
{
    freopen("box.in","r",stdin);
	freopen("bc2.out","w",stdout);
	int i;
    double V, xx, yy, zz;
    while(scanf("%d", &n) != EOF)
    {
        p1.input();
        p2.input();
        xx = fabs(p2.x - p1.x);
        yy = fabs(p2.y - p1.y);
        zz = fabs(p2.z - p1.z);
        V = xx * yy * zz;
        for(i = 0; i < n; i++)  p[i].input();
        memset(visit, false, sizeof(visit));
        ans = 0.0;
        dfs(0, 0.0);
        printf("%.lf\n", V-ans);
    }
    return 0;
}
