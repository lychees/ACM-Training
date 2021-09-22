#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;

const double eps = 1e-8;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y)
	{
		x = _x;y = _y;
	}
	void input()
	{
	    scanf("%lf%lf",&x,&y);
	}
};
//*¡Ωµ„º‰æ‡¿Î
inline double dis(Point a,Point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
Point p1[55],p2[55];
int n,m;
inline int Belong(Point p)
{
    int k = 0;
    double d = dis(p,p2[0]);
    for(int i = 1;i < m;i++)
    {
        double d2 = dis(p,p2[i]);
        if(d2 < d)
        {
            d = d2;
            k = i;
        }
    }
    return k;
}
int solve(Point a,Point b)
{
    int k1 = Belong(a);
    int k2 = Belong(b);
    if(k1 == k2)return 0;
    if(dis(a,b)<eps)return 1;
    Point t = Point((a.x+b.x)/2,(a.y+b.y)/2);
    return solve(a,t)+solve(t,b);
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d%d",&n,&m) == 2)
    {
        for(int i = 0;i < n;i++)
            p1[i].input();
        for(int i = 0;i < m;i++)
            p2[i].input();
        int K;
        int u,v;
        scanf("%d",&K);
        while(K--)
        {
            scanf("%d%d",&u,&v);
            u--;v--;
            printf("%d\n",solve(p1[u],p1[v]));
        }
    }
    return 0;
}
