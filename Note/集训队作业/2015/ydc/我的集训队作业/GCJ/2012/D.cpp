#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 5010
using namespace std;
typedef long long LL;
template<class T>
void Read(T &digit)
{
	digit=0;
	char c;
	for(c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());
	bool type=true;
	if(c=='-')
		type=false,c=getchar();
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
	if(type==false)
		digit=-digit;
}
struct Point
{
	LL x,y;
	Point() {}
	Point(LL x,LL y): x(x),y(y) {}
	friend Point operator + (const Point &a,const Point &b)
	{
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator - (const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend Point operator * (const Point &a,const Point &b)
	{
		return Point(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);
	}
	friend Point operator * (const Point &a,LL p)
	{
		return Point(a.x*p,a.y*p);
	}
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	}
}p[maxn],A[4][maxn];
typedef Point Vector;
bool isRight(const Vector &a)
{
	if(a.x==0)
		return a.y>0;
	else
		return a.x>0;
}
bool cmp(const Vector &a,const Vector &b)
{
	if(isRight(a)!=isRight(b))
		return isRight(a);
	else
		return (double)a.x*b.y>(double)a.y*b.x;
}
int n,m,N[4];
void read()
{
	Read(n),Read(m);
	for(int i=1;i<=n;++i)
		Read(p[i].x),Read(p[i].y);
}
int convex_hull(Point *p)
{
	static Point stack[maxn];
	sort(p+1,p+n+1);
	int top=0;
	for(int i=1;i<=n;++i)
	{
		while(top>1&&(double)(p[i].x-stack[top-1].x)*(p[i].y-stack[top].y)>=(double)(p[i].x-stack[top].x)*(p[i].y-stack[top-1].y))
			--top;
		stack[++top]=p[i];
	}
	int down=top;
	for(int i=n-1;i>=1;--i)
	{
		while(top>down&&(double)(p[i].x-stack[top-1].x)*(p[i].y-stack[top].y)>=(double)(p[i].x-stack[top].x)*(p[i].y-stack[top-1].y))
			--top;
		stack[++top]=p[i];
	}
	if(top>1)
		--top;
	for(int i=1;i<=top;++i)
		p[i]=stack[i];
	return top;
}
double work(int T)
{
	static Vector vec[maxn*4];
	static Point P[4][maxn];
	int nE=0;
	for(int i=0;i<4&&i<T;++i)
	{
		int x=(T-i-1)/4+1;
		for(int j=1;j<=N[i];++j)
			P[i][j]=A[i][j]*x;
	}
	Point ori(0,0),minp(0,0);
	for(int i=0;i<4;++i)
		if(i<T)
		{
			minp=minp+*min_element(P[i]+1,P[i]+N[i]+1);
			if(N[i]>1)
			{
				for(int j=1;j<=N[i];++j)
					vec[++nE]=P[i][j]-P[i][j%N[i]+1];
			}
		}
	sort(vec+1,vec+nE+1,cmp);
	static Point poly[maxn*4];
	double ans=sqrt((double)minp.x*minp.x+(double)minp.y*minp.y);
	for(int i=1;i<=nE;++i)
	{
		poly[i]=ori;
		ori=ori+vec[i];
	}
	Vector delta=minp-*min_element(poly+1,poly+nE+1);
	for(int i=1;i<=nE;++i)
	{
		poly[i]=poly[i]+delta;
		ans=max(ans,sqrt((double)poly[i].x*poly[i].x+(double)poly[i].y*poly[i].y));
	}
	return ans;
}
double work()
{
	double ans=0;
	Vector v(1,1);
	for(int i=1;i<=n;++i)
		A[0][i]=p[i]*v;
	N[0]=convex_hull(A[0]);
	v=Vector(0,1);
	for(int i=1;i<4;++i)
	{
		N[i]=N[0];
		for(int j=1;j<=N[i];++j)
			A[i][j]=A[i-1][j]*v;
	}
	for(int i=max(1,m-3);i<=m;++i)
		ans=max(ans,work(i));
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		read();
		printf("Case #%d: %.10f\n",++C,work());
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
