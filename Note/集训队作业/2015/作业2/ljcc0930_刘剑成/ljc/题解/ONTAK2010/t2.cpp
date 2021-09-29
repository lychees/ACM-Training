#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int MAXN=100010;
const int MAXM=1000010;
const int mod=500009;
struct Point{
	int x,y;
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	}
}p[MAXN];
int n,ans,minv=1<<30,maxv=-1<<30;
LL to[MAXN],size[MAXM*4];
int nEdge=1,next[MAXN],start[mod+10];
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();(c<'0'||c>'9')&&c!='-';c=getchar());
	bool type=true;
	if(c=='-')
		c=getchar(),type=false;
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
	if(!type)
		digit=-digit;
}
LL Hash(int x,int y)
{
	return (LL)x<<21|y;
}
inline bool Count(int a,int b)
{
	if(a<minv||a>maxv||b<minv||b>maxv)
		return false;
	LL c=(LL)a<<21|b;
	int x=c%mod;
	if(start[x]==0)
		return false;
	for(int i=start[x];i;i=next[i])
		if(to[i]==c)
			return true;
	return false;
}
void read()
{
	Read(n);
	for(int i=1;i<=n;++i)
	{
		Read(p[i].x),Read(p[i].y);
		p[i].x+=MAXM,p[i].y+=MAXM;
		minv=min(minv,p[i].x),minv=min(minv,p[i].y);
		maxv=max(maxv,p[i].x),maxv=max(maxv,p[i].y);
		LL c=Hash(p[i].x,p[i].y);
		++nEdge,to[nEdge]=c,next[nEdge]=start[c%mod],start[c%mod]=nEdge;
	}
	sort(p+1,p+n+1);
}
int main()
{
	read();
	Point a,b;
	static int seq[MAXN];
	int tot=0,dis;
	LL maxsize=0;
	for(Point *i=p+1;i<=p+n;++i)
		++size[i->x],maxsize=max(maxsize,size[i->x]);
	if(maxsize*maxsize<=n)
	{
		for(Point *i=p+1;i<=p+n;i+=size[i->x])
		{
			Point *r=i+size[i->x];
			for(Point *a=i;a<r;++a)
				for(Point *b=a+1;b<r;++b)
				{
					dis=b->y-a->y;
					if(Count(a->x-dis,a->y)&&Count(b->x-dis,b->y))
						++ans;
				}
		}
	}
	else
	{
		for(Point *i=p+1;i<=p+n;i+=size[i->x])
		{
			Point *r=i+size[i->x];
			if(size[i->x]*size[i->x]<=n)
			{
				for(Point *a=i;a<r;++a)
					for(Point *b=a+1;b<r;++b)
					{
						dis=b->y-a->y;
						if(Count(a->x-dis,a->y)&&Count(b->x-dis,b->y))
							++ans;
						if(size[a->x+dis]*size[a->x+dis]>n&&Count(a->x+dis,a->y)&&Count(a->x+dis,b->y))
							++ans;
					}
			}
			else
			{
				for(int j=1;j<=tot;++j)
				{
					int x=seq[j];
					for(Point *a=i;a<r;++a)
					{
						int r=a->x-x;
						if(Count(x,a->y)&&Count(x,a->y+r)&&Count(a->x,a->y+r))
							++ans;
					}
				}
				seq[++tot]=i->x;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

