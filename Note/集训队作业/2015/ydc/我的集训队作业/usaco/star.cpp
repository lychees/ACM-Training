#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn 510
#define eps 1e-10
using namespace std;
int dcmp(double p)
{
	if(abs(p)<eps)
		return 0;
	return p>eps?1:-1;
}
struct Point
{
	double x,y;
	Point() {}
	Point(double x,double y): x(x),y(y) {}
	friend Point operator - (Point a,Point b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend Point operator + (Point a,Point b)
	{
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator * (Point a,double p)
	{
		return Point(a.x*p,a.y*p);
	}
}poly[maxn];
typedef Point Vector;
double Cross(Vector a,Vector b)
{
	return a.x*b.y-a.y*b.x;
}
double Dot(Vector a,Vector b)
{
	return a.x*b.x+a.y*b.y;
}
struct Line
{
	Point p;
	Vector v;
	double rad;
	Line() {}
	Line(Point p,Vector v): p(p),v(v)
	{
		rad=atan2(v.y,v.x);
	}
};
int n,m,np;
Line L[maxn];
int tot;
Point getInter(Point a,Vector v1,Point b,Vector v2)
{
	Vector v3=a-b;
	double t=Cross(v2,v3)/Cross(v1,v2);
	return a+v1*t;
}
bool OnSegment(Point a,Point b,Point c)
{
	return !dcmp(Cross(b-a,b-c))&&dcmp(b.x-a.x)*dcmp(b.x-c.x)<=0&&dcmp(b.y-a.y)*dcmp(b.y-c.y)<=0;
}
void Cut(Point *p,int &n,Line L)
{
	static Point tmp[maxn];
	int tot=0;
	for(int i=1;i<=n;++i)
	{
		Point a=p[i],b=p[i%n+1];
		if(dcmp(Cross(a-L.p,L.v))<0)
			tmp[++tot]=a;
		if(dcmp(Cross(b-a,L.v)))
		{
			Point inter=getInter(a,b-a,L.p,L.v);
			if(OnSegment(a,inter,b))
				tmp[++tot]=inter;
		}
	}
	n=tot;
	for(int i=1;i<=n;++i)
		p[i]=tmp[i];
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		char c;
		for(c=getchar();!isalpha(c);c=getchar());
		int va1,vb1,vc1,va2,vb2,vc2;
		scanf("%d %d %d %d %d %d",&va1,&vb1,&vc1,&va2,&vb2,&vc2);
		int va=va1-va2,vb=vb1-vb2,vc=vc2-vc1;
		if(!va&&!vb)
			continue;
		if(c=='B')
			va*=-1,vb*=-1,vc*=-1;
		++tot;
		if(!va)
			L[tot]=Line(Point(0,1.0*vc/vb),Vector(1,0));
		else
			L[tot]=Line(Point(0,1.0*vc/vb),Vector(vb,-va));
		if(Cross(L[tot].p,L[tot].v)<0)
			L[tot].v=L[tot].v*-1;
		if(vc>0)
			L[tot].v=L[tot].v*-1;
	}
}
char work(int a,int b,int c)
{
	if(a==0&&b==0&&c==0)
		return 'U';
	bool can1=false,can2=false;
	for(int i=1;i<=np;++i)
	{
		double val=poly[i].x*a+poly[i].y*b-c;
		if(!dcmp(val))
			return 'U';
		dcmp(val)<0?can1=true:can2=true;
	}
	if(can1&&can2)
		return 'U';
	return can1?'B':'J';
}
void work()
{
	poly[++np]=Point(0.01,0.01);
	poly[++np]=Point(100,0.01);
	poly[++np]=Point(100,100);
	poly[++np]=Point(0.01,100);
	L[++tot]=Line(Point(0,0),Vector(100.01,1));
	L[++tot]=Line(Point(0,0),Vector(-1,-100.01));
	for(int i=1;i<=tot;++i)
		Cut(poly,np,L[i]);
	for(int i=1;i<=m;++i)
	{
		int va1,vb1,vc1,va2,vb2,vc2;
		scanf("%d %d %d %d %d %d",&va1,&vb1,&vc1,&va2,&vb2,&vc2);
		int va=va1-va2,vb=vb1-vb2,vc=vc2-vc1;
		printf("%c\n",work(va,vb,vc));
	}
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
