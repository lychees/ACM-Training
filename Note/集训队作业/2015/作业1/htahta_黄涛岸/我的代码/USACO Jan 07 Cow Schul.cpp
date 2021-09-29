#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=50003;
typedef long long LL;
struct Tpoint
{
	LL x,y;
	Tpoint(){}
	Tpoint(LL _x,LL _y){x=_x,y=_y;}
	inline bool operator <(const Tpoint &b)const{return x*b.y-y*b.x>0;}
	inline Tpoint operator -(const Tpoint &b)const{return Tpoint(x-b.x,y-b.y);}
	inline Tpoint operator +(const Tpoint &b)const{return Tpoint(x+b.x,y+b.y);}
	inline LL operator *(const Tpoint &b)const{return x*b.y-y*b.x;}
}a[maxn],s[maxn],tot,f[maxn];
int n,t,b[maxn],m=0;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)a[i].y=get(),a[i].x=get();
	sort(a+1,a+1+n);
	tot=Tpoint(0,0);
	for(int i=n;i;i--)
	{
		while(t&&s[t].x<=a[i].x)--t;
		while(t>1&&(s[t]-s[t-1])*(a[i]-s[t-1])>=0)--t;
		s[++t]=a[i];tot=tot+a[i];
		while(t>1&&(s[t-1]-s[t])*tot>=0)--t;
		f[i]=s[t];
	}
	t=0;
	for(int i=1;i<n;i++)
	{
		while(t&&s[t].x>=a[i].x)--t;
		while(t>1&&(s[t]-s[t-1])*(a[i]-s[t-1])>=0)--t;
		s[++t]=a[i];tot=tot-a[i];
		while(t>1&&(s[t]-s[t-1])*tot>=0)--t;
		if(tot*(s[t]-f[i+1])>0)b[++m]=i;
	}
	printf("%d\n",m);
	for(int i=1;i<=m;i++)printf("%d\n",b[i]);
	return 0;
}
