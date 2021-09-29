#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <list>
#include <bitset>
#include <string>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cassert>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("333.in");
ofstream fout("333.out");
#else
#define fin cin
#define fout cout
#endif
const double EPS=1e-8;
int sgn(const double &x)
{
	if (fabs(x)<EPS) return 0;
	return x>0?1:-1;
}
struct point
{
	double x,y;
	point(){}
	point(const double &x_,const double &y_):x(x_),y(y_){}
	friend istream& operator >>(istream &in,point &x)
	{
		in>>x.x>>x.y;
		return in;
	}
	friend ostream& operator <<(ostream &out,const point &x)
	{
		out<<x.x<<" "<<x.y;
		return out;
	}
	friend point operator +(const point &x,const point &y)
	{
		return point(x.x+y.x,x.y+y.y);
	}
	friend point operator -(const point &x,const point &y)
	{
		return point(x.x-y.x,x.y-y.y);
	}
	friend point operator *(const point &x,const double &y)
	{
		return point(x.x*y,x.y*y);
	}
	friend point operator *(const double &x,const point &y)
	{
		return y*x;
	}
	friend point operator /(const point &x,const double &y)
	{
		return x*(1/y);
	}
	friend double cross(const point &x,const point &y)
	{
		return x.x*y.y-x.y*y.x;
	}
	friend double cross(const point &x,const point &y,const point &z)
	{
		return cross(y-x,z-x);
	}
	friend double dot(const point &x,const point &y)
	{
		return x.x*y.x+x.y*y.y;
	}
	friend double dot(const point &x,const point &y,const point &z)
	{
		return dot(y-x,z-x);
	}
	friend double dist(const point &x,const point &y)
	{
		return sqrt(dot(x,y,y));
	}
};
struct base_line
{
	point a,b;
	friend istream& operator >>(istream &in,base_line &x)
	{
		in>>x.a>>x.b;
		return in;
	}
	friend ostream& operator <<(ostream &out,const base_line &x)
	{
		out<<x.a<<" "<<x.b;
		return out;
	}
	protected:
	base_line(){}
	base_line(const point &a_,const point &b_):a(a_),b(b_){}
};
struct segment:base_line
{
	segment(){}
	segment(const point &a,const point &b):base_line(a,b){}
	friend bool on_segment(const point &x,const segment &y)
	{
		return sgn(cross(x,y.a,y.b))==0&&sgn(dot(x,y.a,y.b))<=0;
	}
	friend bool interQ(const segment &x,const segment &y)
	{
		double d1=cross(x.a,x.b,y.a);
		double d2=cross(x.a,x.b,y.b);
		double d3=cross(y.a,y.b,x.a);
		double d4=cross(y.a,y.b,x.b);
		if (sgn(d1)*sgn(d2)<0&&sgn(d3)*sgn(d4)<0) return true;
		if (sgn(d1)==0&&sgn(dot(y.a,x.a,x.b))<=0) return true;
		if (sgn(d2)==0&&sgn(dot(y.b,x.a,x.b))<=0) return true;
		if (sgn(d3)==0&&sgn(dot(x.a,y.a,y.b))<=0) return true;
		if (sgn(d4)==0&&sgn(dot(x.b,y.a,y.b))<=0) return true;
		return false;
	}
	double getpos(const point &x) const
	{
		return dist(a,x)/dist(a,b);
	}
	double getprlen(const point &x) const
	{
		return cross(a,b,x)/dist(a,b);
	}
	double getprpos(const point &x) const
	{
		return dot(a,b,x)/dot(a,b,b);
	}
};
struct ray:base_line
{
	ray(){}
	ray(const point &a,const point &b):base_line(a,b){}
	friend pair<bool,point> interQP(const ray &x,const segment &y)
	{
		double d1=cross(x.a,x.b,y.a);
		double d2=cross(x.a,x.b,y.b);
		double d3=cross(y.a,y.b,x.a);
		double d4=cross(y.b-y.a,x.b-x.a);
		if (sgn(d1)*sgn(d2)>0||sgn(d3)*sgn(d4)>0||sgn(d3)==0) return make_pair(false,point());
		else return make_pair(true,y.a+d1/(d1-d2)*(y.b-y.a));
	}
	friend pair<bool,point> interQP(const segment &x,const ray &y)
	{
		return interQP(y,x);
	}
};
struct line:base_line
{
	line(){}
	line(const point &a,const point &b):base_line(a,b){}
	explicit line(const segment &x):base_line(x){}
};
struct polygon
{
	static const int MAXN=9;
	int n;
	point a[MAXN];
	friend istream& operator >>(istream &in,polygon &x)
	{
		in>>x.n;
		for (int i=0;i<x.n;++i)
		{
			in>>x.a[i];
			x.a[i]=x.a[i]/100;
		}
		return in;
	}
	double area() const
	{
		double s=0;
		for (int i=0;i<n;++i) s+=cross(a[i],a[(i+1)%n]);
		return s/2;
	}
	segment get_segment(const int &i) const
	{
		return segment(a[i],a[(i+1)%n]);
	}
};
struct square
{
	static const int N=4;
	segment a[N];
	double r;
	square(){}
	explicit square(const double &r_):r(r_)
	{
		a[0]=segment(point(0,0),point(r_,0));
		a[1]=segment(point(r_,0),point(r_,r_));
		a[2]=segment(point(r_,r_),point(0,r_));
		a[3]=segment(point(0,r_),point(0,0));
	}
	point inter(const ray &x) const
	{
		for (int i=0;i<4;++i)
		{
			pair<bool,point> p=interQP(x,a[i]);
			if (p.first) return p.second;
		}
		assert(0);
	}
	pair<point,point> inter(const line &x) const
	{
		return make_pair(inter(ray(x.b,x.a)),inter(ray(x.a,x.b)));
	}
	int on_which_segment(const point &x) const
	{
		for (int i=0;i<N;++i)
			if (on_segment(x,a[i])) return i;
		return -1;
	}
	int on_which_segment(const point &x,const point &y) const
	{
		for (int i=0;i<N;++i)
			if (on_segment(x,a[i])&&on_segment(y,a[i])) return i;
		return -1;
	}
	bool on_square(const point &x) const
	{
		return on_which_segment(x)!=-1;
	}
	bool on_same_segment(const point &x,const point &y) const
	{
		return on_which_segment(x,y)!=-1;
	}
	pair<int,double> segment_pos(const point &x) const
	{
		int p=on_which_segment(x);
		double s;
		assert(p!=-1);
		switch (p)
		{
			case 0:s=x.x;break;
			case 1:s=x.y;break;
			case 2:s=r-x.x;break;
			case 3:s=r-x.y;break;
		}
		return make_pair(p,s);
	}
	double areas_product(const point &x,const point &y) const
	{
		double s;
		pair<point,point> k=inter(line(x,y));
		pair<int,double> p=segment_pos(k.first),q=segment_pos(k.second);
		switch ((q.first-p.first+N)%N)
		{
			case 0:s=0;break;
			case 1:s=(r-p.second)*q.second/2;break;
			case 2:s=(r-p.second+q.second)*r/2;break;
			case 3:s=p.second*(r-q.second)/2;break;
		}
		return s*(r*r-s);
	}
}const sq(1);
struct cmp_of_point
{
	const square &a;
	cmp_of_point(const square &a_):a(a_){}
	bool operator()(const point &x,const point &y) const
	{
		return a.segment_pos(x)<a.segment_pos(y);
	}
};
double integrate(const double &a,const double &b,const double &s,const double &t)
{
	if (sgn(s)==0||sgn(t)==0) return 0;
	assert(sgn(s)==sgn(t));
	if (s>0) return b*(t-s)+a*(log(t)-log(s));
	else return b*(t-s)+a*(log(-t)-log(-s));
}
double getP(const point &a,const point &b,const point &c,const point &d,const point &p,const point &o)
{
	if (sgn(cross(a,b,o))==0||sgn(cross(c,d,o))==0) return 0;
	int pab=sq.on_which_segment(a,b);
	int pcd=sq.on_which_segment(c,d);
	if (pab==(pcd+2)%4) return cross(a,b,o)*cross(c,d,o)/8;
	double ps=sq.a[pab].getprpos(o)-sq.a[pab].getpos(a);
	double pt=sq.a[pab].getprpos(o)-sq.a[pab].getpos(b);
	double ia=-sq.a[pab].getprlen(o)*sq.a[pcd].getprlen(o);
	double ib=sq.a[pcd].getpos(c)-sq.a[pcd].getprpos(o);
	double s=integrate(ia,ib,ps,pt);
	s=s/(dist(a,b)*dist(c,d))*cross(a,b,o)*cross(c,d,o)/4;
	if (!interQ(segment(b,c),segment(p,o)))
		s=cross(a,b,o)*cross(c,d,o)/4-s;
	return s;
}
double getP(const point &x,const point &y)
{
	double sum=0;
	point ps[2*sq.N+3];
	for (int i=0;i<sq.N;++i)
	{
		ps[2*i]=sq.a[i].a;
		ps[2*i+1]=sq.inter(ray(sq.a[i].a,y));
	}
	ps[2*sq.N]=x;
	ps[2*sq.N+1]=sq.inter(ray(x,y));
	sort(ps,ps+2*sq.N+2,cmp_of_point(sq));
	ps[2*sq.N+2]=ps[0];
	for (int i=0;i<2*sq.N+2;++i)
		for (int j=0;j<2*sq.N+2;++j)
			if (i!=j)
			{
				const point &a=ps[i],&b=ps[i+1],&c=ps[j],&d=ps[j+1];
				if (sgn(cross(a,y,c))==0) sum+=getP(a,b,c,d,x,y);
				else
				{
					point p=(a+b)/2;
					point q=(c+d)/2;
					if (interQ(segment(p,q),segment(x,y)))
						sum+=cross(a,b,y)*cross(c,d,y)/4;
				}
			}
	return sum;
}
double getP(const segment &x)
{
	if (sq.on_same_segment(x.a,x.b)) return 0;
	else
	{
		pair<point,point> pr=sq.inter(line(x));
		return 2*sq.areas_product(x.a,x.b)-getP(pr.first,x.a)-getP(pr.second,x.b);
	}
}
int main()
{
	polygon a;
	double ans;
	fin>>a;
	ans=a.area();
	for (int i=0;i<a.n;++i) ans+=getP(a.get_segment(i))/2;
	fout<<fixed<<setprecision(10)<<ans<<endl;
	return 0;
}
