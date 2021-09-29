#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100033,maxx=2000333;
int u[maxx],d[maxx],n;
double ans=0;
struct Tpoint
{
	int x,y;
}a[maxn];
void work()
{
	double res,c1=0,c2,tot,c3;int mx=0;
	a[n+1]=a[1];
	for(int i=1;i<=n;i++)c1+=LL(a[i].x)*a[i+1].y-LL(a[i].y)*a[i+1].x;
	if(c1>0)reverse(a+1,a+1+n),a[n+1]=a[1];
	for(int i=1;i<=n;i++)
	{
		LL x1=a[i].x,y1=a[i].y,x2=a[i+1].x,y2=a[i+1].y;
		if(x1>mx)mx=x1;
		if(x1==x2)continue;
		if(x1<x2)for(int j=x1;j<=x2;j++)u[j]=(y1*(x2-j)+y2*(j-x1))/(x2-x1);
		else for(int j=x2;j<=x1;j++)d[j]=(y2*(x1-j)+y1*(j-x2)-1)/(x1-x2);
	}
	tot=c1=c2=res=0;
	for(int i=0;i<=mx;i++)
	{
		c3=u[i]-d[i],tot+=c3;
		c1+=c3*i*i,c2+=c3*i;
	}
	ans+=(tot*c1-c2*c2)/(tot*(tot-1));
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	int mx=maxx,my=mx;
	for(int i=1;i<=n;i++)mx=min(mx,a[i].x=get()),my=min(my,a[i].y=get());
	for(int i=1;i<=n;i++)a[i].x-=mx-1,a[i].y-=my-1;
	work();
	for(int i=1;i<=n;i++)swap(a[i].x,a[i].y);
	work();
	printf("%.10lf\n",ans);
	return 0;
}
