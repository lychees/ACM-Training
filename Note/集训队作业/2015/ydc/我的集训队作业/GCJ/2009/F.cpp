#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 100
#define Eps 1e-10
using namespace std;
const double pi=acos(-1);
double dcmp(double p)
{
	if(abs(p)<Eps)
		return 0;
	return p>Eps?1:-1;
}
struct Point
{
	double x,y;
	void Read()
	{
		cin>>x>>y;
	}
	Point() {}
	Point(double x,double y): x(x),y(y) {}
	friend Point operator + (Point a,Point b)
	{
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator - (Point a,Point b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend Point operator * (Point a,double p)
	{
		return Point(a.x*p,a.y*p);
	}
	friend Point operator / (Point a,double p)
	{
		return Point(a.x/p,a.y/p);
	}
}A,B;
typedef Point Vector;
double Cross(Vector a,Vector b)
{
	return a.x*b.y-a.y*b.x;
}
double Dot(Vector a,Vector b)
{
	return a.x*b.x+a.y*b.y;
}
double Len(Vector a)
{
	return sqrt(Dot(a,a));
}
struct Cir
{
	Point o;
	double r;
}c[maxn];
double sumArea;
int n,state;
double Helen(double a,double b,double c)
{
	double S=(a+b+c)/2;
	return sqrt(S*(S-a)*(S-b)*(S-c));
}
bool check(Point p1,Point p2,Cir o)
{
	if(dcmp(abs(Cross(o.o-p1,p2-p1))/Len(p2-p1)-o.r)>=0)
		return true;
	return dcmp(Dot(p2-p1,o.o-p1))<0||dcmp(Dot(p1-p2,o.o-p2))<0;
}
void add(pair<double,double> *L,int &tot,Cir &c,Point &p,double x)
{
	if(!dcmp(p.x-x))
	{
		double dy=sqrt(c.r*c.r-(c.o.x-x)*(c.o.x-x));
		if(p.y>c.o.y+dy)
			L[++tot]=make_pair(0,c.o.y+dy);
		if(p.y<c.o.y-dy)
			L[++tot]=make_pair(c.o.y-dy,100);
		return ;
	}
	if(dcmp(c.o.x-c.r-max(p.x,x))>=0)
		return ;
	if(dcmp(c.o.x+c.r-min(p.x,x))<=0)
		return ;
	double l1=c.r,l3=Len(p-c.o),l2=sqrt(Dot(p-c.o,p-c.o)-c.r*c.r);
	if(dcmp(l3-l1)<=0)
		return ;
	double Area=Helen(l1,l2,l3);
	double h=Area*2/l3;
	double len=sqrt(l2*l2-h*h);
	Vector v=(c.o-p)/Len(c.o-p);
	Point a=p+v*len;
	Vector v1=Vector(v.y,-v.x);
	Vector v2=Vector(-v.y,v.x);
	Vector V1=a+v1*h-p,V2=a+v2*h-p;
	bool t1=check(p,Point(x,0.0),c),t2=check(p,Point(x,100.0),c);
	if(!t1&&!t2)
		L[++tot]=make_pair(0,100);
	else if(!t1)
	{
		if(x>p.x)
			swap(V1,V2);
		if(abs(x-p.x)<=abs(V1.x)||!dcmp(V1.x))
			L[++tot]=make_pair(0,c.o.y+sqrt(c.r*c.r-(c.o.x-x)*(c.o.x-x)));
		else
			L[++tot]=make_pair(0,p.y+(x-p.x)/V1.x*V1.y);
	}
	else if(!t2)
	{
		if(x>p.x)
			swap(V1,V2);
		if(abs(x-p.x)<=abs(V2.x)||!dcmp(V2.x))
			L[++tot]=make_pair(c.o.y-sqrt(c.r*c.r-(c.o.x-x)*(c.o.x-x)),100);
		else
			L[++tot]=make_pair(p.y+(x-p.x)/V2.x*V2.y,100);
	}
	else
	{
	 	double l=p.y+(x-p.x)/V1.x*V1.y;
	 	double r=p.y+(x-p.x)/V2.x*V2.y;
		double l1,r1;
		if(dcmp(x-p.x)!=dcmp(V1.x)||dcmp(x-p.x)!=dcmp(V2.x))
			return ;
		if(dcmp(c.o.x-c.r-x)<0&&dcmp(c.o.x+c.r-x)>0)
		{
			double dy=sqrt(c.r*c.r-(c.o.x-x)*(c.o.x-x));
			l1=c.o.y-dy,r1=c.o.y+dy;
		}
		if(abs(x-p.x)<=abs(V1.x))
			l=l<l1?l1:r1;
		if(abs(x-p.x)<=abs(V2.x))
			r=r<l1?l1:r1;
	 	if(l>r)
		 	swap(l,r);
		if(r<0||l>100)
			return ;
		l=max(l,0.0),r=min(r,100.0);
		L[++tot]=make_pair(l,r);
	}
}
double F(double x)
{
	static pair<double,double> L[maxn*10];
	int tot=0;
	for(int i=1;i<=n;++i)
	{
		if(dcmp(c[i].o.x-c[i].r-x)<0&&dcmp(c[i].o.x+c[i].r-x)>0)
		{
			double dy=sqrt(c[i].r*c[i].r-(c[i].o.x-x)*(c[i].o.x-x));
			L[++tot]=make_pair(c[i].o.y-dy,c[i].o.y+dy);
		}
		if(state&1)
			add(L,tot,c[i],A,x);
		if(state&2)
			add(L,tot,c[i],B,x);
	}
	if(!tot)
		return 100;
	sort(L+1,L+tot+1);
	double sum=100.0,l=L[1].first,r=L[1].second;
	for(int i=2;i<=tot;++i)
	{
		if(dcmp(r-L[i].first)<0)
			sum-=r-l,l=L[i].first,r=L[i].second;
		else
			r=max(r,L[i].second);
	}
	sum-=r-l;
	return sum;
}
double S(double l,double r,double Fl,double Fmid,double Fr)
{
	return (Fl+Fmid*4+Fr)*(r-l)/6;
}
double Simpson(double l,double r,double eps,double Fl,double Fmid,double Fr,double s)
{
	double mid=(l+r)/2;
	double v1=F((l+mid)/2),v2=F((mid+r)/2);
	double A=S(l,mid,Fl,v1,Fmid),B=S(mid,r,Fmid,v2,Fr);
	if(abs(A+B-s)<=15*eps)
		return A+B+abs(A+B-s)/15;
	return Simpson(l,mid,eps/2,Fl,v1,Fmid,A)+Simpson(mid,r,eps/2,Fmid,v2,Fr,B);
}
double Simpson(double l,double r,double eps)
{
	double mid=(l+r)/2;
	double Fl=F(l),Fr=F(r),Fmid=F(mid);
	return Simpson(l,r,eps,F(l),F(mid),F(r),S(l,r,Fl,Fmid,Fr));
}
double calc()
{
	double ans=0;
	for(int i=1;i<=100;++i)
		ans+=Simpson(i-1,i,1e-10);
	return ans;
}
void read()
{
	A.Read(),B.Read();
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		c[i].o.Read(),cin>>c[i].r;
		sumArea+=c[i].r*c[i].r*pi;
	}
}
void print()
{
	double Area=10000;
	state=1;
	double area1=calc();
	state=2;
	double area2=calc();
	state=3;
	double area3=calc();
	printf("%.20f\n",Area-area1-area2+area3-sumArea);
	printf("%.20f\n",area1-area3);
	printf("%.20f\n",area2-area3);
	printf("%.20f\n",area3);
}
int main()
{
	read();
	print();
	return 0;
}
