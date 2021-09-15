#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 100010
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	Point() {}
	Point(LL x,LL y): x(x),y(y) {}
	void Read()
	{
		cin>>x>>y;
	}
	friend Point operator - (const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.x<b.x||(a.x==b.x&&a.y<b.y); 
	}
}p[maxn];
bool cmp(const Point &a,const Point &b)
{
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}
double Len(const Point &a)
{
	return sqrt(a.x*a.x+a.y*a.y);
}
double ans=1e100;
int n;
void read()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		p[i].Read();
	sort(p+1,p+n+1);
}
void update(double &a,double b)
{
	if(a>b)
		a=b;
}
void work(int l,int r)
{
	if(r-l<=5)
	{
		for(int i=l;i<=r;++i)
			for(int j=i+1;j<=r;++j)
				for(int k=j+1;k<=r;++k)
					ans=min(ans,Len(p[i]-p[j])+Len(p[i]-p[k])+Len(p[j]-p[k]));
		sort(p+l,p+r+1,cmp);
		return ;
	}
	static Point a[maxn],b[maxn];
	int mid=(l+r)>>1,na=0,nb=0;
	work(l,mid),work(mid+1,r);
	for(int i=l;i<=mid;++i)
		if(p[mid].x-p[i].x<=ans/2)
			a[++na]=p[i];
	for(int i=mid+1;i<=r;++i)
		if(p[i].x-p[mid+1].x<=ans/2)
			b[++nb]=p[i];
	for(int i=1,L=1,R=1;i<=na;++i)
	{
		while(L<=nb&&a[i].y-b[L].y>ans/2)
			++L;
		while(R<=nb&&b[R].y-a[i].y<=ans/2)
			++R;
		bool mark=false;
		for(int j=L;j<R&&!mark;++j)
			if(Len(a[i]-b[j])<=ans/2)
				mark=true;
		if(!mark)
			continue;
		for(int j=L;j<R;++j)
			for(int k=j+1;k<R;++k)
				update(ans,Len(a[i]-b[j])+Len(a[i]-b[k])+Len(b[j]-b[k]));
	}
	for(int i=max(na,nb);i>=1;--i)
		swap(a[i],b[i]);
	swap(na,nb);
	for(int i=1,L=1,R=1;i<=na;++i)
	{
		while(L<=nb&&a[i].y-b[L].y>ans/2)
			++L;
		while(R<=nb&&b[R].y-a[i].y<=ans/2)
			++R;
		bool mark=false;
		for(int j=L;j<R&&!mark;++j)
			if(Len(a[i]-b[j])<=ans/2)
				mark=true;
		if(!mark)
			continue;
		for(int j=L;j<R;++j)
			for(int k=j+1;k<R;++k)
				update(ans,Len(a[i]-b[j])+Len(a[i]-b[k])+Len(b[j]-b[k]));
	}
	na=0,nb=0;
	for(int i=l;i<=mid;++i)
		a[++na]=p[i];
	for(int i=mid+1;i<=r;++i)
		b[++nb]=p[i];
	int i=1,j=1,tot=l;
	while(i<=na&&j<=nb)
		p[tot++]=a[i].y<b[j].y?a[i++]:b[j++];
	while(i<=na)
		p[tot++]=a[i++];
	while(j<=nb)
		p[tot++]=b[j++];
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work(1,n);
	printf("%.20f\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

