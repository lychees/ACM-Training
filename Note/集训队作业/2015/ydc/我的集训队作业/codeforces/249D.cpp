#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define lowbit(x) (x&-x)
#define maxn 100010
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	LL a,b,c;
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.a<b.a||(a.a==b.a&&a.b<b.b)||(a.a==b.a&&a.b==b.b&&a.c<b.c);
	}
}p[maxn];
int Root[maxn],lc[maxn*200],rc[maxn*200],maxv[maxn*200];
int n,tot;
void update(int &a,int b)
{
	if(a<b)
		a=b;
}
void Read(LL &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	int a,b,c,d;
	scanf("%d",&n);
	scanf("%d/%d %d/%d",&a,&b,&c,&d);
	int m=0;
	for(int i=1;i<=n;++i)
	{
		Read(p[i].x),Read(p[i].y);
		p[i].c=p[i].x*p[i].x+p[i].y*p[i].y;
		p[i].a=(b-p[i].x)*a-(a-p[i].y)*b;
		p[i].b=(p[i].x-d)*c-(p[i].y-c)*d;
		if(p[i].x*a-p[i].y*b<0&&p[i].x*c-p[i].y*d>0)
			p[++m]=p[i];
	}
	n=m;
	sort(p+1,p+n+1);
}
int Insert(int p,int l,int r,int x,int v)
{
	if(!p)
		p=++tot;
	update(maxv[p],v);
	if(l==r)
		return p;
	int mid=(l+r)>>1;
	if(x<=mid)
		lc[p]=Insert(lc[p],l,mid,x,v);
	else
		rc[p]=Insert(rc[p],mid+1,r,x,v);
	return p;
}
int Query(int p,int l,int r,int x,int y,const int &nowans)
{
	if(maxv[p]<=nowans)
		return 0;
	if(l==x&&r==y)
		return maxv[p];
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(lc[p],l,mid,x,y,nowans);
	else if(mid<x)
		return Query(rc[p],mid+1,r,x,y,nowans);
	else
		return max(Query(lc[p],l,mid,x,mid,nowans),Query(rc[p],mid+1,r,mid+1,y,nowans));
}
int getmax(int x,int y)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans=max(ans,Query(Root[i],1,n,1,y,ans));
	return ans;
}
void Insert(int x,int y,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
		Root[i]=Insert(Root[i],1,n,y,val);
}
void Dp()
{
	int ans=0;
	static LL tb[maxn],tc[maxn];
	static int dp[maxn],b[maxn],c[maxn];
	for(int i=1;i<=n;++i)
		tb[i]=p[i].b,tc[i]=p[i].c;
	sort(tb+1,tb+n+1),sort(tc+1,tc+n+1);
	int nb=unique(tb+1,tb+n+1)-tb-1,nc=unique(tc+1,tc+n+1)-tc-1;
	for(int i=1;i<=n;++i)
	{
		if(p[i].a!=p[i-1].a)
			for(int j=i-1;j>=1&&p[j].a==p[i-1].a;--j)
				if(p[j].c<tc[nc])
					Insert(b[j]+1,c[j]+1,dp[j]);
		b[i]=lower_bound(tb+1,tb+nb+1,p[i].b)-tb;
		c[i]=lower_bound(tc+1,tc+nc+1,p[i].c)-tc;
		dp[i]=getmax(b[i],c[i]);
		ans=max(ans,++dp[i]);
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Dp();
	printf("%f\n",(double)clock()/CLOCKS_PER_SEC);
	return 0;
}
