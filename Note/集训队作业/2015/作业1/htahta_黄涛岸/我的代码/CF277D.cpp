#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long double LD;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=1600;
int n,T;
struct data
{
	int s1,s2,t1,t2;
	LD p;
	void init()
	{
		s1=get(),s2=get(),t1=get(),t2=get();
		double _p;scanf("%lf",&_p);
		p=_p;
	}
	inline bool operator <(const data &b)const
	{
		return t2*p*(1-b.p)<b.t2*b.p*(1-p);
	}
}a[maxn];
struct res
{
	LD s,p;
	res(){}
	res(LD _s,LD _p){s=_s,p=_p;}
}ans,f[maxn];
inline void gmax(res &a,const res &b)
{
	if((fabs(a.s-b.s)<=1e-10&&a.p>b.p)||a.s<b.s)a=b;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),T=get();
	for(int i=1;i<=n;i++)a[i].init();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		int s1=a[i].s1,s2=a[i].s2,t1=a[i].t1,t2=a[i].t2;
		LD p=a[i].p;
		for(int j=T;j>=t1;j--)
		{
			gmax(f[j],res(f[j-t1].s+s1,f[j-t1].p+t1));
			if(j>=t1+t2)gmax(f[j],res(f[j-t1-t2].s+s1+s2*(1-p),(f[j-t1-t2].p+t1)*p+j*(1-p)));
		}
	}
	ans=res(0,0);
	for(int j=0;j<=T;j++)gmax(ans,f[j]);
	printf("%.10lf %.10lf\n",double(ans.s),double(ans.p));
	return 0;
}
