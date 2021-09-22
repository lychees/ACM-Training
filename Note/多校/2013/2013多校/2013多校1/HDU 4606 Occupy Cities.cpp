#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;

const double eps = 1e-6;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
struct Point
{
    double x,y;
    Point(double _x = 0,double _y = 0)
    {
        x = _x; y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
};
struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e)
    {
        s = _s; e = _e;
    }
    void input()
    {
        s.input();
        e.input();
    }
};
double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}
bool inter(Line l1,Line l2)
{
    return
    sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e)) < 0 &&
    sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e)) < 0;
}

const int MAXN = 440;
Point p[MAXN];
Line line[MAXN];
const double INF = 100000000.0;
double dis[MAXN][MAXN];
int n,m,P;

int b[MAXN];

int uN,vN;
struct Edge
{
    int to,next;
}edge[MAXN*MAXN];
int head[MAXN];
int tot;
void addedge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)
{
    for(int i = head[u]; i!= -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(!used[v])
        {
            used[v] = true;
            if(linker[v]==-1 || dfs(linker[v]))
            {
                linker[v] = u;
                return true;
            }
        }
    }

    return false;
}
int hungary()
{
    int res = 0;
    memset(linker,-1,sizeof(linker));
    for(int u = 0;u < uN;u ++)
    {
        memset(used,false,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}
bool check(double d)
{
    uN = vN = n;
    init();
    for(int i = 0;i < n;i++)
        for(int j = i+1;j < n;j++)
           if(dis[b[i]][b[j]] < d + eps)
              addedge(b[i],b[j]);
    if(n - hungary() <= P)return true;
    else return false;
}
double solve()
{
    double l = 0, r = 100000.0;
    double ans;
    while(r-l >= eps)
    {
        double mid = (l+r)/2;
        if(check(mid))
        {
            ans = mid;
            r = mid - eps;
        }
        else l = mid + eps;
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&P);
        for(int i = 0;i < n;i++)
            p[i].input();
        int t = n;
        for(int i = 0;i < m;i++)
        {
            line[i].input();
            p[n+2*i] = line[i].s;
            p[n+2*i+1] = line[i].e;
        }
        for(int i = 0;i < n+2*m;i++)
            for(int j = 0;j < n+2*m;j++)
            {
                if(i == j)
                {
                    dis[i][j] = 0;
                    continue;
                }
                bool flag = false;
                for(int k = 0;k < m;k++)
                    if(inter(line[k],Line(p[i],p[j])))
                    {
                        flag = true;
                        break;
                    }
                if(flag)dis[i][j] = 1e20;
                else dis[i][j] = dist(p[i],p[j]);
            }
        for(int k = 0;k < n+2*m;k++)
            for(int i = 0;i < n+2*m;i++)
                for(int j = 0;j < n+2*m;j++)
                    dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
        for(int i = 0;i < n;i++)
        {
            scanf("%d",&b[i]);
            b[i]--;
        }
        printf("%.2lf\n",solve());
    }
    return 0;
}
