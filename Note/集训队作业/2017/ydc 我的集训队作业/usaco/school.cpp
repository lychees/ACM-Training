#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 50010
#define eps 1e-10
using namespace std;
typedef long long LL;
template<class T>
void Read(T &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
int dcmp(double p)
{
	if(abs(p)<eps)
		return 0;
	return p>eps?1:-1;
}
struct Point
{
	LL x,y;
	Point() {}
	Point(LL x,LL y): x(x),y(y) {}
	friend Point operator + (Point a,Point b)
	{
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator - (Point a,Point b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
}p[maxn];
typedef Point Vector;
LL Cross(Vector a,Vector b)
{
	return a.x*b.y-a.y*b.x;
}
bool cmp(const Point &a,const Point &b)
{
	return Cross(a,b)<0;
}
struct Line
{
	Point p;
	Vector v;
	friend bool operator < (const Line &a,const Line &b)
	{
		return Cross(a.v,b.v)>0;
	}
	double calc(double x)
	{
		return p.y+(x-p.x)*v.y;
	}
}L[maxn];
int n;
double sc[maxn],v1[maxn],v2[maxn];
double getInter(Line a,Line b)
{
	Vector v=a.p-b.p;
	double t=1.0*Cross(b.v,v)/Cross(a.v,b.v);
	return a.p.x+a.v.x*t;
}
void read()
{
	Read(n);
	for(int i=1;i<=n;++i)
		Read(p[i].x),Read(p[i].y);
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		L[i].p=Point(0,p[i].x);
		L[i].v=Vector(1,-p[i].y);
	}
}
void update(int l,int mid,int r,double *ans)
{
	static Line stack[maxn];
	static double x[maxn];
	int top=0;
	for(int i=l;i<=mid;++i)
	{
		if(L[i].v.y==stack[top].v.y)
		{
			if(L[i].p.y>stack[top].p.y)
				stack[top]=L[i];
			else
				continue;
		}
		while(top>1&&getInter(L[i],stack[top-1])>getInter(L[i],stack[top]))
			--top;
		stack[++top]=L[i];
	}
	for(int i=1;i<top;++i)
		x[i]=getInter(stack[i],stack[i+1]);
	if(mid+1==r||sc[mid+1]>sc[mid+2])
	{
		int i=1,j=mid+1;
		while(i<top&&j<=r)
		{
			if(x[i]<sc[j])
				++i;
			else
				ans[j]=max(ans[j],stack[i].calc(sc[j])),++j;
		}
		while(j<=r)
			ans[j]=max(ans[j],stack[i].calc(sc[j])),++j;
	}
	else
	{
		int i=1,j=r;
		while(i<top&&j>mid)
		{
			if(x[i]<sc[j])
				++i;
			else
				ans[j]=max(ans[j],stack[i].calc(sc[j])),--j;
		}
		while(j>mid)
			ans[j]=max(ans[j],stack[i].calc(sc[j])),--j;
	}
}
void merge(int l,int r)
{
	static Line tL[maxn];
	int mid=(l+r)>>1,i=l,j=mid+1,tot=0;
	while(i<=mid&&j<=r)
	{
		if(L[i]<L[j])
			++tot,tL[tot]=L[i],++i;
		else
			++tot,tL[tot]=L[j],++j;
	}
	while(i<=mid)
		++tot,tL[tot]=L[i],++i;
	while(j<=r)
		++tot,tL[tot]=L[j],++j;
	for(int k=l;k<=r;++k)
		L[k]=tL[k-l+1];
}
void work(int l,int r,double *ans)
{
	if(l==r)
	{
		ans[l]=max(ans[l],p[l].x-p[l].y*sc[l]);
		return ;
	}
	int mid=(l+r)>>1;
	work(l,mid,ans),work(mid+1,r,ans);
	update(l,mid,r,ans);
	merge(l,r);
}
void work()
{
	Point total(0,0);
	for(int i=1;i<=n;++i)
		total=total+p[i];
	for(int i=1;i<n;++i)
	{
		total=total-p[i];
		sc[i]=1.0*total.x/total.y;
	}
	static int ans[maxn];
	fill(v1+1,v1+n,-1e100);
	fill(v2+1,v2+n,-1e100);
	int tot=0;
	work(1,n-1,v1);
	reverse(sc+1,sc+n),reverse(p+1,p+n+1);
	for(int i=1;i<=n;++i)
	{
		p[i].x=-p[i].x,p[i].y=-p[i].y;
		L[i].p=Point(0,p[i].x);
		L[i].v=Vector(1,-p[i].y);
	}
	work(1,n-1,v2);
	reverse(v2+1,v2+n);
	for(int i=1;i<n;++i)
		if(dcmp(v1[i]+v2[i])>0)
			ans[++tot]=i;
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d\n",ans[i]);
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
