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
const int maxn=200003;
struct data
{
	int x,y,t;
	inline bool operator <(const data &b)const{return t<b.t;}
}a[maxn],g[maxn*2];
int fa[maxn],n,num[maxn],Tnum=0,T,t[maxn],tot=0;
LL ans,cnt,sum;
inline int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	T=get();n=get();
	for(int i=1;i<=n;i++)num[++Tnum]=a[i].x=get(),num[++Tnum]=a[i].y=get(),a[i].t=get();
	sort(num+1,num+1+Tnum),Tnum=unique(num+1,num+1+Tnum)-num-1;
	sort(a+1,a+1+n);
	for(int i=1;i<=Tnum;i++)fa[i]=i,t[i]=-1;
	for(int i=1;i<=n;i++)
	{
		int x=lower_bound(num+1,num+1+Tnum,a[i].x)-num;
		int y=lower_bound(num+1,num+1+Tnum,a[i].y)-num-1;
		for(int j=getfa(x);j<=y;j=getfa(j))t[j]=a[i].t,fa[j]=j+1;
	}
	for(int i=1;i<Tnum;i++)
	{
		if(t[i]==-1)continue;
		g[++tot].t=t[i]-num[i+1],g[tot].x=1;
		g[++tot].t=t[i]-num[i],g[tot].x=-1,g[tot].y=num[i+1]-num[i];
	}
	sort(g+1,g+1+tot);
	ans=cnt=sum=0;
	for(int i=1;T;T--)
	{
		int x=get();
		for(;i<=tot&&g[i].t<=x;cnt+=g[i].x,i++)
			if(g[i].x==-1)ans+=g[i].y,sum-=g[i].t-g[i].y;
			else sum+=g[i].t;
		printf("%d\n",cnt*x-sum+ans);
	}
	return 0;
}
