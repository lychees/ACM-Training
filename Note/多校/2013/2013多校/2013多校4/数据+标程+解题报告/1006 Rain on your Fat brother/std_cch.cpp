#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define eps 1e-8
#define inf 1000000000
using namespace std;
int sig(double x)
{
	if(x<-eps)return -1;
	if(x>eps)return 1;
	return 0;
}
struct Tpoint
{
	double x,y;
	void in()
	{
		scanf("%lf%lf",&x,&y);
	}
}p[100];
Tpoint operator-(Tpoint a,Tpoint b)
{
	Tpoint ret;
	ret.x=a.x-b.x;
	ret.y=a.y-b.y;
	return ret;
}
bool operator==(Tpoint a,Tpoint b)
{
	return sig(a.x-b.x)==0&&sig(a.y-b.y)==0;
}
struct rain
{
	Tpoint o;
	double r,h;
}s[2010];
struct g
{
	double l,r;
}d[2010];
struct line
{
	Tpoint p,q;
	double k,b;
	void in()
	{
		p.in();
		q.in();
	}
}L[100];
double dis(Tpoint a,Tpoint b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(Tpoint a,Tpoint b,Tpoint c)
{
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
bool is_parallel(line L1,line L2)
{
	Tpoint e=L1.q-L1.p,f=L2.q-L2.p;
	return sig(e.x*f.y-e.y*f.x)==0;
}
bool inside(Tpoint o,line L)
{
	double xl=min(L.p.x,L.q.x);
	double xr=max(L.p.x,L.q.x);
	double yl=min(L.p.y,L.q.y);
	double yr=max(L.p.y,L.q.y);
	if(sig(o.x-xl)>=0&&sig(xr-o.x)>=0&&sig(o.y-yl)>=0&&sig(yr-o.y)>=0)
		return true;
	else
		return false;
}
Tpoint Intersect(line u,line v)//返回两直线的交点  注意是直线。
{
	Tpoint ret=u.p;
	double t=((u.p.x-v.p.x)*(v.p.y-v.q.y)-(u.p.y-v.p.y)*(v.p.x-v.q.x))
			/((u.p.x-u.q.x)*(v.p.y-v.q.y)-(u.p.y-u.q.y)*(v.p.x-v.q.x));
	ret.x+=(u.q.x-u.p.x)*t;
	ret.y+=(u.q.y-u.p.y)*t;
	return ret;
}
double dot(const Tpoint& o,const Tpoint & a,const Tpoint& b)
{
    return (a.x - o.x)* (b.x- o.x) + (a.y - o.y)*(b.y - o.y);
}
int btw(const Tpoint& x,const Tpoint& a,const Tpoint & b)
{
    return sig(dot(x,a,b));
}
int SegCross(line L1,line L2,Tpoint &e)//1为规范相交，2为非规范相交，0不相交
{
	Tpoint a,b,c,d;
	a=L1.p;b=L1.q;
	c=L2.p;d=L2.q;
    int d1,d2,d3,d4;
    d1 = sig( cross(a,b,c));
    d2 = sig( cross(a,b,d));
    d3 = sig( cross(c,d,a));
    d4 = sig( cross(c,d,b));
    if((d1^d2)==-2&& (d3^d4)==-2)
    {
    	e=Intersect(L1,L2);
    	return 1;
    }
    if( d1== 0 && btw(c,a,b)<=0 ||
            d2 == 0 && btw(d,a,b)<=0||
            d3 == 0 && btw(a,c,d)<=0 ||
            d4 == 0 && btw(b,c,d)<=0)
    {
    	e=Intersect(L1,L2);
    	return 2;
    }
    return 0;
}

g gao1(int i,double t,double v1,double vv,double x)
{
	Tpoint e,v,u;
	double r=s[i].r,xx=s[i].o.x,yy=s[i].o.y;
	e.x=-v1*t+x;
	e.y=vv*t;
	int flag1,flag2,flag3;
	flag1=flag2=flag3=0;
	g ret;
	double k,b,aa,bb,cc,x1,x2,y1,y2;
	k=-vv/v1;
	b=-k*x;
	aa=1+k*k;
	bb=2*k*(b-yy)-2*xx;
	cc=xx*xx+(b-yy)*(b-yy)-r*r;
	if(bb*bb-4*aa*cc<eps)
	{
		ret.l=ret.r=0;
		return ret;
	}
	x1=(-bb+sqrt(bb*bb-4*aa*cc))/(2*aa);
	y1=k*x1+b;
	x2=(-bb-sqrt(bb*bb-4*aa*cc))/(2*aa);
	y2=k*x2+b;
	u.x=x1;u.y=y1;v.x=x2;v.y=y2;
	if(u.y<v.y)
		swap(u,v);
	if(y1<s[i].o.y-eps&&y2<s[i].o.y-eps)
	{
		if(v.y>e.y)
		{
			ret.l=ret.r=0;
			return ret;
		}
		else if(u.y>e.y)
		{
			ret.l=e.x;
			ret.r=v.x;
			return ret;
		}
		else
		{
			ret.l=u.x;
			ret.r=v.x;
			return ret;
		}
	}
	else if(v.y<s[i].o.y-eps)
	{
		u.y=s[i].o.y;
		u.x=(s[i].o.y-b)/k;
		if(v.y>e.y)
		{
			ret.l=ret.r=0;
			return ret;
		}
		else if(u.y>e.y)
		{
			ret.l=e.x;
			ret.r=v.x;
			return ret;
		}
		else
		{
			ret.l=u.x;
			ret.r=v.x;
			return ret;
		}
	}
	else
	{
		ret.l=ret.r=0;
		return ret;
	}
}

g gao2(int i,double t,double v1,double vv,double x)
{
	g ret;
	int flag1,flag2,flag3;
	flag1=flag2=flag3=0;
	Tpoint u,v,e,f,d,ee,dd,eee,fff;
	d.x=x;d.y=0;dd=d;
	e.x=s[i].o.x+s[i].r;
	e.y=s[i].o.y;
	f.x=s[i].o.x;
	f.y=s[i].o.y+s[i].h;
	if(t*v1<-1000000)t/=1000;
	ee.x=-v1*t+x;
	ee.y=vv*t;
	eee=e;fff=f;
	if(sig(s[i].r*vv-s[i].h*v1)==0&&sig(cross(d,e,f))==0)
	{
		/*ret.l=ret.r=0;
		return ret;*/
		v=e;u=f;
		ee.x=-v1*t+x;
		ee.y=vv*t;
		if(v.y>ee.y-eps)
		{
			ret.l=ret.r=0;
			return ret;
		}
		else if(u.y>ee.y-eps)
		{
			ret.l=ee.x;
			ret.r=v.x;
			return ret;
		}
		else
		{
			ret.l=u.x;
			ret.r=v.x;
			return ret;
		}
	}
	else
	{
		line L1,L2,L3,L;
		L.p=d;L.q=ee;
		L1.p=e;L1.q.x=e.x-2*s[i].r;L1.q.y=e.y;
		L2.p=e;L2.q=f;
		L3.p=L1.q;L3.q=f;
		flag1=SegCross(L,L1,d);
		flag2=SegCross(L,L2,e);
		flag3=SegCross(L,L3,f);
		if(flag1==0&&flag2==0&&flag3==0)
		{
			if(sig(cross(dd,L1.q,L1.p))>0&&sig(cross(dd,L1.p,L2.q))>0&&sig(cross(dd,L2.q,L1.q))>0)
			{
				ret.l=ee.x;
				ret.r=x;
			}
			else
				ret.l=ret.r=0;
			return ret;
		}
		if(flag1==1&&flag2==1)
		{
			ret.r=d.x;
			ret.l=e.x;
			return ret;
		}
		if(flag1==1&&flag3==1)
		{
			ret.r=d.x;
			ret.l=f.x;
			return ret;
		}
		if(flag2==1&&flag3==1)
		{
			ret.r=e.x;
			ret.l=f.x;
			return ret;
		}
		if(flag1==1&&flag2==2&&flag3==2)
		{
			ret.r=d.x;
			ret.l=s[i].o.x;
			return ret;
		}
		if(flag3==1&&flag2==2&&flag1==2)
		{
			ret.r=s[i].o.x+s[i].r;
			ret.l=f.x;
			return ret;
		}
		if(flag1==2&&flag2==2)
		{
			ret.r=s[i].o.x+s[i].r;
			ret.l=ee.x;
			return ret;
		}
		if(flag2==2&&flag3==2)
		{
			ret.r=x;
			ret.l=s[i].o.x;
			return ret;
		}
		if(flag1==1)
		{
			ret.r=d.x;
			ret.l=ee.x;
			return ret;
		}
		if(flag2==1)
		{
			if(sig(cross(dd,L1.q,L1.p))>0&&sig(cross(dd,L1.p,L2.q))>0&&sig(cross(dd,L2.q,L1.q))>0)
			{
				ret.l=e.x;
				ret.r=x;
			}
			else
			{
				ret.r=e.x;
				ret.l=ee.x;
			}
			return ret;
		}
		if(flag3==1)
		{
			ret.r=x;
			ret.l=f.x;
			return ret;
		}
		if(flag2==2)
		{
			ret.r=x;
			ret.l=e.x;
		}
		if(flag3==2)
		{
			ret.l=f.x;
			ret.r=x;

		}
		ret.l=ret.r=0;
		return ret;
	}
}
bool cmp(g x, g y)
{
	return sig(x.l-y.l)<0||sig(x.l-y.l)==0&&sig(x.r-y.r)<0;
}
int main()
{
	int i,j,k,n,tt,ri,m;
	double now,tmp,ans,v1,v2,v,t,x;
	scanf("%d",&tt);
	for(ri=1;ri<=tt;ri++)
	{
		ans=0;
		scanf("%lf%lf%lf%lf%lf",&v1,&v2,&v,&t,&x);
		tmp=v1*t/(v2-v1);
		t+=tmp;
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			s[i].o.in();
			scanf("%lf%lf",&s[i].r,&s[i].h);
			d[i*2]=gao1(i,t,v1,v,x);
			d[i*2+1]=gao2(i,t,v1,v,x);
			if(d[i*2].l>d[i*2].r)
			{
			//	d[i].l=d[i].r=0;
				swap(d[i].l,d[i].r);
			}
			if(d[i*2+1].l>d[i*2+1].r)
			{
			//	d[i].l=d[i].r=0;
				swap(d[i].l,d[i].r);
			}
		}
		for(i=0;i<2*n;i++)
		{
			if(d[i].l>x)
			{
				d[i].l=d[i].r=0;
				continue;
			}
			if(d[i].r>x)
				d[i].r=x;
		}
		d[2*n].l=1000000000;
		sort(d,d+2*n,cmp);
		ans=d[0].r-d[0].l;
		now=d[0].r;
		for(i=1;i<2*n;i++)
		{
			if(now<d[i].l)
				now=d[i].l;
			if(now<d[i].r)
				ans+=d[i].r-now;
		//	if(ri==90)
			//	printf("%lf %lf %lf %lf\n",d[i].l,d[i].r,now,d[i].r-now);
				now=max(now,d[i].r);

		}
		printf("Case %d: %.4lf\n",ri,(ans+eps)/v1);
	}
}
