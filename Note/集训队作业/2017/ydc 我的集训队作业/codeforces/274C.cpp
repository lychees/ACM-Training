#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define eps 1e-10
#define maxn 110
using namespace std;
int dcmp(double p)
{
	if(abs(p)<eps)
		return 0;
	return p>0?1:-1;
}
struct Point
{
	double x,y;
	Point() {}
	Point(double x,double y): x(x),y(y) {}
	friend Point operator - (const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend Point operator + (const Point &a,const Point &b)
	{
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator * (const Point &a,double p)
	{
		return Point(a.x*p,a.y*p);
	}
	friend Point operator / (const Point &a,double p)
	{
		return Point(a.x/p,a.y/p);
	}
	friend bool operator != (const Point &a,const Point &b)
	{
		return dcmp(a.x-b.x)||dcmp(a.y-b.y);
	}
	void Read()
	{
		cin>>x>>y;
	}
}p[maxn];
typedef Point Vector;
double Dot(Vector a,Vector b)
{
	return a.x*b.x+a.y*b.y;
}
double Cross(Vector a,Vector b)
{
	return a.x*b.y-a.y*b.x;
}
double Len(Vector a)
{
	return sqrt(Dot(a,a));
}
int n;
void read()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		p[i].Read();
}
bool check(Point a,double r)
{
	for(int i=1;i<=n;++i)
		if(dcmp(Len(a-p[i])-r)<0)
			return false;
	return true;
}
Point GetInter(Point P,Point v1,Point Q,Point v2)
{
	Point v=P-Q;
	double t=Cross(v2,v)/Cross(v1,v2);
	return P+v1*t;
}
void work()
{
	double ans=-1;
	for(int a=1;a<=n;++a)
		for(int b=a+1;b<=n;++b)
			for(int c=1;c<=n;++c)
				if(c!=a&&c!=b)
					for(int d=c+1;d<=n;++d)
						if(d!=a&&d!=b)
						{
							Point o1=(p[a]+p[b])/2,o2=(p[c]+p[d])/2;
							if(o1!=o2||!dcmp(Cross(p[a]-p[b],p[a]-p[c])))
								continue;
							if(check(o1,Len(o1-p[a])))
								ans=max(ans,Len(o1-p[a]));
						}
	for(int a=1;a<=n;++a)
		for(int b=a+1;b<=n;++b)
			for(int c=b+1;c<=n;++c)
				if(dcmp(Dot(p[b]-p[a],p[c]-p[a]))>0&&dcmp(Dot(p[a]-p[b],p[c]-p[b]))>0&&dcmp(Dot(p[a]-p[c],p[b]-p[c]))>0)
				{
					Point m1=(p[a]+p[b])/2,v1=m1-p[a];
					Point m2=(p[b]+p[c])/2,v2=m2-p[b];
					v1=Vector(v1.y,-v1.x),v2=Vector(v2.y,-v2.x);
					Point o=GetInter(m1,v1,m2,v2);
					if(check(o,Len(o-p[a])))
						ans=max(ans,Len(o-p[a]));
				}
	if(ans<0)
		printf("-1\n");
	else
		printf("%.20f\n",ans);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
