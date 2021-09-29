#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
inline int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-'0';
    while(isdigit(ch=getchar()))v=v*10+ch-'0';
    if(f==1)return -v;else return v;
}
const int maxn=1000003;
struct Tpoint
{
	int x,y;
	inline bool operator <(const Tpoint &b)const{return x<b.x;}
}a[maxn],b[maxn],c[maxn];
double ans;int n;
inline double dis(const Tpoint &a,const Tpoint &b)
{
	return sqrt(double(a.x-b.x)*(a.x-b.x)+double(a.y-b.y)*(a.y-b.y));
}
inline void solve(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)/2,cnt=0,i=l,j=mid+1,Tc=0,x=a[mid].x;
	solve(l,mid),solve(mid+1,r);
	while(i<=mid&&j<=r)
		if(a[i].y<a[j].y)b[++cnt]=a[i],i++;else b[++cnt]=a[j],j++;
	while(i<=mid)b[++cnt]=a[i],i++;
	while(j<=r)b[++cnt]=a[j],j++;
	for(i=1;i<=cnt;i++)
	{
		a[l+i-1]=b[i];
		if(abs(b[i].x-x)<=ans/2)c[++Tc]=b[i];
	}
	for(i=1;i<Tc;i++)
	{
		int p=i;double tp;
		while(p<Tc&&c[p+1].y-c[i].y<=ans/2)p++;//
		for(j=i+1;j<=p;j++)
		{
			if((tp=dis(c[j],c[i]))>=ans/2)continue;
			for(int k=j+1;k<=p;k++)ans=min(ans,tp+dis(c[i],c[k])+dis(c[j],c[k]));
		}
	}
}
int main()
{
	freopen("s.in","r",stdin);
	freopen("s.out","w",stdout);
	int T=get();
	for(int _=1;_<=T;_++)
	{
		n=get();
		for(int i=1;i<=n;i++)a[i].x=get(),a[i].y=get();
		sort(a+1,a+1+n);
		ans=dis(a[1],a[2])+dis(a[2],a[3])+dis(a[3],a[1]);
		solve(1,n);
		printf("Case #%d: %.12lf\n",_,ans);
	}
	return 0;
}
