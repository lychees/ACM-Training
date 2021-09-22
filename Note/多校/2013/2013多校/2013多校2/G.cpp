#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
using namespace std;
const double eps = 1e-8;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
struct Point3D
{
    double x,y,z;
    Point3D(double _x = 0,double _y = 0,double _z = 0)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    Point3D operator -(const Point3D &b)const
    {
        return Point3D(x-b.x,y-b.y,z-b.z);
    }
    Point3D operator ^(const Point3D &b)const
    {
        return Point3D(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);
    }
    double operator *(const Point3D &b)const
    {
        return x*b.x+y*b.y+z*b.z;
    }
    void input()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
};
double Norm(Point3D p)
{
    return sqrt(p*p);
}
//计算两个异面直线的距离
//第一条直线过点a,方向向量为k1,第二条直线过点
double calc(Point3D a,Point3D k1,Point3D b,Point3D k2)
{
    Point3D tmp = k1^k2;
    return fabs(tmp*(a-b))/sqrt(tmp*tmp);
}

struct Node
{
    Point3D o,p1,p2;
    void input()
    {
        o.input();
        p1.input();
        p2.input();
    }
}node[50];

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0;i < n;i++)
            node[i].input();
        bool flag = false;
        double Min = 1e20;
        for(int i = 0;i < n;i++)
            for(int j = i+1;j < n;j++)
            {
                if(flag)break;
                double  r1 = sqrt((node[i].p1-node[i].o)*(node[i].p1-node[i].o));
                double  r2 = sqrt((node[j].p1-node[j].o)*(node[j].p1-node[j].o));
                Point3D  k1 = (node[i].p1-node[i].o)^(node[i].p2-node[i].o);
                Point3D  k2 = (node[j].p1-node[j].o)^(node[j].p2-node[j].o);
                if(sgn(Norm(k1^k2))==0)
                {
                    if(sgn( Norm( k1^(node[i].o-node[j].o)) ) == 0)//同轴
                    {
                        if(sgn(r1-r2) == 0)
                        {
                            flag = true;
                            break;
                        }
                        else continue;
                    }
                    else
                    {
                        double dd = (k1*(node[i].o-node[j].o))/Norm(k1);
                        double d = sqrt( Norm(node[i].o-node[j].o)*Norm(node[i].o-node[j].o) - dd*dd );
                        if(d > fabs(r1-r2) &&d < fabs(r1+r2))
                        {
                            flag = true;
                            break;
                        }
                        Min = min(Min,d-r1-r2);
                    }
                    continue;
                }
                double d = calc(node[i].o,k1,node[j].o,k2);
                if(d < r1 + r2 -eps)
                {
                    flag = true;
                    break;
                }
                Min = min(Min,d-r1-r2);
            }
        if(flag || sgn(Min)<=0)printf("Lucky\n");
        else printf("%.2lf\n",Min);
    }
    return 0;
}







