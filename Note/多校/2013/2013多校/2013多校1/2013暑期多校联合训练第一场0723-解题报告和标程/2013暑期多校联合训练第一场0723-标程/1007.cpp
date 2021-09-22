#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define eps 1e-8
#define N 110
#define M 220
#define oo 1e15
using namespace std;

int dlcmp(double x) {return x<-eps?-1:x>eps;}
double sqr(double x) {return x*x;}

struct Point
{
    double x,y;

    Point(){}
    Point(double a,double b):x(a),y(b){}

    Point operator - (const Point p) {return Point(x-p.x,y-p.y);}
};

double dist(Point a,Point b) {return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
double cross(Point a,Point b) {return a.x*b.y-b.x*a.y;}
int n,m,p;
double dis[N+M][N+M];
char map[N][N],mark[N];
int match[N];
Point pt[N+M];
int seq[N];

int segment_intersect(Point s1,Point e1,Point s2,Point e2)
{
    if (max(s1.x,e1.x)>min(s2.x,e2.x)&&max(s2.x,e2.x)>min(s1.x,e1.x)&&
        max(s1.y,e1.y)>min(s2.y,e2.y)&&max(s2.y,e2.y)>min(s1.y,e1.y)&&
        dlcmp(cross(e1-s1,s2-s1))*dlcmp(cross(e1-s1,e2-s1))<0&&
        dlcmp(cross(e2-s2,s1-s2))*dlcmp(cross(e2-s2,e1-s2))<0)

        return 1;
    else
        return 0;
}

int isBlock(Point a,Point b)
{
    for (int i=1;i<=m;i++)
        if (segment_intersect(a,b,pt[n+i],pt[n+m+i]))
            return 1;
    return 0;
}

double floyd()
{
    int i,j,k;
    int num=n+m+m;
    double res=0.0;

    for (i=1;i<=num;i++)
        for (j=1;j<=num;j++)
            if (i==j)
                dis[i][j]=0;
            else
                dis[i][j]=oo;

    for (i=1;i<=num;i++)
        for (j=i+1;j<=num;j++)
            if (!isBlock(pt[i],pt[j]))
                dis[i][j]=dis[j][i]=min(dis[i][j],dist(pt[i],pt[j]));


    for (k=1;k<=num;k++)
        for (i=1;i<=num;i++)
            for (j=1;j<=num;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);

    for (i=1;i<=n;i++)
        for (j=i+1;j<=n;j++)
            res=max(res,dis[i][j]);

    return res;
}

void build_graph(double d)
{
    int i,j;

    memset(map,0,sizeof(map));
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            if (dlcmp(dis[i][j]-d)<=0 && seq[i]<seq[j])
                map[i][j]=1;

}

int find(int u)
{
    int i;

    for (i=1;i<=n;i++)
        if (map[u][i] && mark[i]==0)
        {
            mark[i]=1;
            if (match[i]==0 || find(match[i]))
            {
                match[i]=u;
                return 1;
            }
        }
    return 0;
}

int check(double d)
{
    int i,res;

    build_graph(d);

    memset(match,0,sizeof(match));
    res=0;
    for (i=1;i<=n;i++)
    {
        memset(mark,0,sizeof(mark));
        res+=find(i);
    }

    if (n-res<=p)
        return 1;
    else
        return 0;
}

int main()
{
    int t,i,j,x;
    double l,r,mid;

//    freopen("data.in","r",stdin);
//    freopen("data.out","w",stdout);

    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d%d",&n,&m,&p);
        for (i=1;i<=n;i++)
            scanf("%lf%lf",&pt[i].x,&pt[i].y);
        for (i=1;i<=m;i++)
            scanf("%lf%lf%lf%lf",&pt[n+i].x,&pt[n+i].y,&pt[n+m+i].x,&pt[n+m+i].y);
        for (i=1;i<=n;i++)
        {
            scanf("%d",&x);
            seq[x]=i;
        }

        l=0;
        r=floyd();

        while ((r-l)>eps)
        {
            mid=(l+r)/2;
            if (check(mid))
                r=mid;
            else
                l=mid;
        }

        printf("%.2f\n",l);
    }

    return 0;
}
