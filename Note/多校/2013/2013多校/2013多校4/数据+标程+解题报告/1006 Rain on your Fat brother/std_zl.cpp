#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;
typedef __int64 lld;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define eps 1e-8
int Sig(double a)
{
	return a<-eps?-1:(a>eps);
}
struct Point
{
	double x,y;
	Point(){}
	Point(double x0,double y0):x(x0),y(y0){}
	void in()
	{
		scanf("%lf%lf",&x,&y);
	}
	Point operator * (double t)
	{
		return Point(t*x,t*y);
	}
	double len()
	{
		return sqrt(x*x+y*y);
	}
	double operator *(Point pt)
	{
		return x*pt.y-y*pt.x;
	}
	Point operator -(Point pt)
	{
		return Point(x-pt.x,y-pt.y);
	}
	Point operator +(Point pt)
	{
		return Point(x+pt.x,y+pt.y);
	}
};
bool cmp(Point a,Point b)
{
	if(Sig(a.x-b.x) == 0)
		return a.y < b.y;
	return a.x < b.x;
}
bool Is_Parallel(Point up,Point uq,Point vp,Point vq)
{
	Point p=up-uq;
	Point q=vp-vq;
	return Sig(p*q) == 0;
}
Point Intersect(Point up,Point uq,Point vp,Point vq)
{
	Point ret=up;
	double t=((up.x-vp.x)*(vp.y-vq.y)-(up.y-vp.y)*(vp.x-vq.x))
			/((up.x-uq.x)*(vp.y-vq.y)-(up.y-uq.y)*(vp.x-vq.x));
	ret.x+=(uq.x-up.x)*t;
	ret.y+=(uq.y-up.y)*t;
	return ret;
}
int Line_to_circle(Point s,Point e,Point p,double r,Point &p1,Point &p2)
{
   double d=fabs((s-p)*(s-e))/(s-e).len();
   if(Sig(d-r) > 0)
       return 0;
   double h=sqrt(r*r-d*d);
   Point tmp=Point(e.y-s.y,s.x-e.x);
   Point o=Intersect(p,p+tmp,s,e);
   if(Sig(d-r)==0)
   {
       p1=o;
       return 1;
   }
   p1=o+(e-s)*(h/(s-e).len());
   p2=o-(e-s)*(h/(s-e).len());
   return 2;
}
struct Rain
{
	Point a,b,c;
	Point o;
	double r,h;
	void in()
	{
		o.in();
		scanf("%lf %lf",&r,&h);
		a=b=c=o;
		a.x-=r;
		b.x+=r;
		c.y+=h;
	}
	bool inside(Point now)
	{
		if(now.y <= o.y)
			return Sig((now-o).len()-r) <=0;
		else
		{
			if(Sig((b-a)*(now-a)) < 0)
				return false;
			if(Sig((c-b)*(now-b)) < 0)
				return false;
			if(Sig((a-c)*(now-c)) < 0)
				return false;
			return true;
		}
	}
}rain;
Point begin,end;
bool inside(Point o)
{
	return Sig(o.x-end.x) >= 0 && Sig(o.x-begin.x) <= 0;
}
struct Event
{
	double x;
	int flag;
	Event(){}
	Event(double x0,int flag0):x(x0),flag(flag0){}
}pp[100010];
int qq;
bool cmp1(Event a,Event b)
{
	return a.x < b.x;
}
Point ff[100010];
int gg;
int main()
{
//	freopen("output.txt","r",stdin);
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		double v1,v2,v,t,x;
		scanf("%lf %lf %lf %lf %lf",&v1,&v2,&v,&t,&x);
		Point dir=Point(-v1,v);
		t+=(v1*t)/(v2-v1);
		begin=Point(x,0);
		end=Point(x,0)+dir*t;
		int n;
		scanf("%d",&n);
		qq=0;
		for(int i=0;i<n;i++)
		{
			gg=0;
			ff[gg++]=begin;
			ff[gg++]=end;
			rain.in();
			Point p1,p2;
			int flag=Line_to_circle(begin,end,rain.o,rain.r,p1,p2);
			if(flag >= 1 && inside(p1))
				ff[gg++]=p1;
			if(flag >= 2 && inside(p2))
				ff[gg++]=p2;
			if(!Is_Parallel(begin,end,rain.a,rain.b))
			{
				Point o=Intersect(begin,end,rain.a,rain.b);
				if(inside(o))
					ff[gg++]=o;
			}
			if(!Is_Parallel(begin,end,rain.b,rain.c))
			{
				Point o=Intersect(begin,end,rain.b,rain.c);
				if(inside(o))
					ff[gg++]=o;
			}
			if(!Is_Parallel(begin,end,rain.c,rain.a))
			{
				Point o=Intersect(begin,end,rain.c,rain.a);
				if(inside(o))
					ff[gg++]=o;
			}
			sort(ff,ff+gg,cmp);
			for(int j=1;j<gg;j++)
			{
				if(Sig((ff[j]-ff[j-1]).len()) == 0)
					continue;
				Point o=(ff[j-1]+ff[j])*0.5;
				if(rain.inside(o))
				{
					pp[qq++]=Event(ff[j-1].x,1);
					pp[qq++]=Event(ff[j].x,-1);
				}
			}
		}
		double ans=0;
		sort(pp,pp+qq,cmp1);
		int now=0;
		for(int i=1;i<qq;i++)
		{
			now+=pp[i-1].flag;
			if(now > 0)
				ans+=pp[i].x-pp[i-1].x;
		}
		printf("Case %d: %.4f\n",cc,ans/v1);
	}
	return 0;
}
