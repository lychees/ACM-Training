#include<cstdio>
#include<algorithm>
#include<cmath>
#define N 50
using namespace std;
const double eps=1e-8;
const double PI=3.1415926535897932384626433832795;
struct Point
{int x,y;}p[N],dir;
int dcmp(double a,double b=0)
{
 if (a-b>eps) return 1;
 if (b-a>eps) return -1;
 return 0;
}
Point operator -(const Point &a,const Point &b)
{
 Point c;
 c.x=a.x-b.x;
 c.y=a.y-b.y;
 return c;
}
Point operator +(const Point &a,const Point &b)
{
 Point c;
 c.x=a.x+b.x;
 c.y=a.y+b.y;
 return c;
}
int n;
int gcd(int a,int b)
{
 if (b==0) return a;
 return gcd(b,a%b);
}
void read(Point &a)
{
 scanf("%d%d",&a.x,&a.y);
}
int det(Point a,Point b)
{
 return a.x*b.y-a.y*b.x;
}
int dot(Point a,Point b)
{
 return a.x*b.x+a.y*b.y;
}
bool online(Point p,Point a,Point b)
{
 if (det(p-a,b-a)!=0) return 0;
 if (dot(p-a,p-b)<=0) return 1;
 return 0;
}
bool jiao(Point A1,Point B1,Point A2,Point B2)
{
 long long t1=(long long)det(A2-A1,B1-A1)*det(B2-A1,B1-A1);
 long long t2=(long long)det(A1-A2,B2-A2)*det(B1-A2,B2-A2);
 if (t1>0||t2>0) return 0;
 return 1;
}
bool get_in(int x,int y)
{
 int tot=0;
 Point a;
 a.x=x;a.y=y;
 Point b;
 b.x=252;b.y=a.y;
 for (int i=0;i<n;i++)
  {
   if (online(a,p[i],p[i+1])) return 0;
   if (det(p[i+1]-p[i],b-a)==0) continue;
   if (online(p[i],a,b))
    {
	 if (p[i].y>p[i+1].y) tot++;
	 continue;
	}
   if (online(p[i+1],a,b))
    {
	 if (p[i+1].y>p[i].y) tot++;
	 continue;
	}
   if (jiao(p[i],p[i+1],a,b)) tot++;
  }
 if (tot%2==0) return 0;
 return 1;
}

double dis(Point a)
{
 return sqrt(a.x*a.x+a.y*a.y);
}
double ptol(const Point &p,const Point &a,const Point &b)
{
 if (dot(b-a,p-a)<0) return dis(p-a);
 if (dot(a-b,p-b)<0) return dis(p-b);
 return (double)abs(det(p-a,b-a))/(dis(a-b));
}
void write(Point a)
{
 printf("%d %d\n",a.x,a.y);
}
bool real_in(int x,int y)
{
 Point a;
 a.x=x;a.y=y;
 for (int i=0;i<n;i++)
 {
   double Len=ptol(a,p[i],p[i+1]);
   if (online(a,p[i],p[i+1])) continue;
   if (dcmp(Len-0.5)<0) return 0;
 }
 return 1;
}
double get_angle(Point dir1,Point dir2)
{
 double x,y;
 x=(double)dot(dir1,dir2)/(dis(dir1)*dis(dir2));
 y=(double)det(dir1,dir2)/(dis(dir1)*dis(dir2));
 double ans=atan2(y,x);
 if (dcmp(ans)<0) ans+=2*PI;
 return ans/8;
}
int get_tot(Point a,Point b)
{
 Point dir=b-a;
 int d=abs(gcd(dir.x,dir.y));
 dir.x/=d;dir.y/=d;
 Point New=a;
 int tot=0;
 for (int i=1;i<=500;i++)
  {
   New=New+dir;
   if (New.x==b.x&&New.y==b.y) return tot;
   if (real_in(New.x,New.y))tot++;
  }
 return tot;
}
void work()
{
 for (int i=1;i<=n;i++)
  read(p[i]);
 p[0]=p[n];
 int tot=0;
 for (int i=0;i<n;i++)
  tot+=get_tot(p[i],p[i+1]);
 double ans=(double)tot*PI/8;
 tot=0;
 for (int i=-250;i<=250;i++)
  for (int j=-250;j<=250;j++)
   if (get_in(i,j)&&real_in(i,j))tot++;
 ans=ans+(double)tot*PI/4;
 p[n+1]=p[1];
 for (int i=1;i<=n;i++)
  if (real_in(p[i].x,p[i].y))ans+=fabs(get_angle(p[i-1]-p[i],p[i+1]-p[i]));
 printf("%0.3lf\n",ans);
}
int main()
{
 freopen("clear.in","r",stdin);
 freopen("bc.out","w",stdout);
 while (scanf("%d",&n)!=EOF&&n) work();
 return 0;
}
