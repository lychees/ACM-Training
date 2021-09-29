#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long LL;
int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
const int maxn=555,maxm=(500*500*2+555)*2,inf=100000000;
struct Tedge
{
	int t,v,op,pre;
	Tedge(){}
	Tedge(int _t,int _v,int _op,int _pre){t=_t,v=_v,op=_op,pre=_pre;}
}g[maxm];
int n,Link[maxn],s[maxn],h[maxn],source,sink,x[maxn],y[maxn],r[maxn],v[maxn],ans,tot,fst[maxn];
inline void add(int s,int t,int v)
{
	int tp;
	tp=Link[s]; Link[s]=++tot; g[tot]=Tedge(t,v,tot+1,tp);
	tp=Link[t]; Link[t]=++tot; g[tot]=Tedge(s,0,tot-1,tp);
	//cout<<s<<" "<<t<<" "<<v<<endl;
}
inline bool bfs()
{
	for(int i=1;i<=sink;i++)h[i]=-1,fst[i]=Link[i];
	int front=0,rear=1;
	s[front]=source,h[source]=1;
	while(front!=rear)
	{
		int p=s[front];
		for(int i=Link[p];i;i=g[i].pre)
			if(h[g[i].t]==-1&&g[i].v)h[g[i].t]=h[p]+1,s[rear++]=g[i].t;
		front++;
	}
	return h[sink]!=-1;
}
inline int aug(int x,int flow)
{
	if(x==sink)return flow;
	int tp=flow,d,i;
	for(i=fst[x];i;i=g[i].pre)
	{
		if(h[g[i].t]!=h[x]+1||g[i].v<=0)continue;
		d=min(tp,g[i].v),d=aug(g[i].t,d);
		g[i].v-=d,g[g[i].op].v+=d,tp-=d;
		if(tp==0)break;
	}
	fst[x]=i;
	if(tp==flow)h[x]=-1;
	return flow-tp;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	for(int _=1,T=get();_<=T;_++)
	{
		n=get();source=n+1,sink=n+2;
		ans=0,tot=0,memset(Link,0,sizeof(Link));
		for(int i=1;i<=n;i++)
		{
			x[i]=get(),y[i]=get(),r[i]=get(),v[i]=get();
			if(v[i]>=0)add(source,i,v[i]),ans+=v[i];else add(i,sink,-v[i]);
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=r[i]*r[i])add(i,j,inf);
		while(bfs())ans-=aug(source,inf);
		printf("Case #%d: %d\n",_,ans);
	}
	cerr<<clock()<<endl;
	return 0;
}

