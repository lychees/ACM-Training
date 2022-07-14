#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 10010
#define eps 1e-10
using namespace std;
int dcmp(double p)
{
	if(abs(p)<eps)
		return 0;
	return p>eps?1:-1;
}
const double pi=acos(-1);
struct Point
{
	double x,y;
	Point() {}
	Point(double x,double y): x(x),y(y) {}
	friend Point operator - (const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
}p[maxn];
typedef Point Vector;
double Cross(const Vector &a,const Vector &b)
{
	return a.x*b.y-a.y*b.x;
}
int n;
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=4*n;++i)
		scanf("%lf %lf",&p[i].x,&p[i].y);
}
Point Center(double rad)
{
	static double x[maxn],y[maxn];
	for(int i=1;i<=4*n;++i)
		x[i]=p[i].x*cos(rad)+p[i].y*sin(rad),y[i]=p[i].x*sin(rad)-p[i].y*cos(rad);
	sort(x+1,x+4*n+1),sort(y+1,y+4*n+1);
	Point ans((x[n<<1]+x[n<<1|1])/2,(y[n<<1]+y[n<<1|1])/2);
	return Point(ans.x*cos(rad)+ans.y*sin(rad),ans.x*sin(rad)-ans.y*cos(rad));
}
int calc(double rad)
{
	Point o=Center(rad);
	Vector v1(-cos(rad),-sin(rad));
	Vector v2(v1.y,-v1.x);
	int cnt=0;
	for(int i=1;i<=4*n;++i)
	{
		int d1=dcmp(Cross(v1,p[i]-o)),d2=dcmp(Cross(p[i]-o,v2));
		if(!d1||!d2)
			return 1<<30;
		cnt+=d1<0&&d2<0;
	}
	return cnt;
}
void print()
{
	double l=0,r=pi/2;
	int x=calc(l);
	if(x<n)
	{
		while(1)
		{
			double mid=(l+r)/2;
			int x=calc(mid);
			while(x==1<<30)
				mid-=1e-5,x=calc(mid);
			x<=n?l=mid:r=mid;
			if(x==n)
				break;
		}
	}
	else if(x>n)
	{
		while(1)
		{
			double mid=(l+r)/2;
			int x=calc(mid);
			while(x==1<<30)
				mid-=1e-5,x=calc(mid);
			x>=n?l=mid:r=mid;
			if(x==n)
				break;
		}
	}
	Point o=Center(l);
	Vector v(-cos(l),-sin(l));
	printf("%.9f %.9f %.9f %.9f\n",o.x,o.y,o.x+v.x*100000,o.y+v.y*100000);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		read();
		printf("Case #%d: ",++C);
		print();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
