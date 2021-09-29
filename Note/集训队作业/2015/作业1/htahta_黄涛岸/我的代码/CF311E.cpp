#include <iostream>
#include <cstdio>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=15000,maxm=70000,inf=1000000000;
struct Tedge
{
	int s,t,v,op,pre;
	Tedge(){}
	Tedge(int _s,int _t,int _v,int _op,int _pre){s=_s,t=_t,v=_v,op=_op,pre=_pre;}
}g[maxm];
int n,m,K,source,sink,s[maxn],h[maxn],a[maxn],ans=0,tot=0,Link[maxn];
inline void add(int s,int t,int v)
{
	int tp;
	tp=Link[s]; Link[s]=++tot; g[tot]=Tedge(s,t,v,tot+1,tp);
	tp=Link[t]; Link[t]=++tot; g[tot]=Tedge(t,s,0,tot-1,tp);
}
inline bool bfs()
{
	for(int i=1;i<=sink;i++)h[i]=-1;
	int front=0,rear=1;
	s[front]=source,h[source]=1;
	while(front!=rear)
		for(int p=s[front++],i=Link[p];i;i=g[i].pre)
			if(h[g[i].t]==-1&&g[i].v)h[g[i].t]=h[p]+1,s[rear++]=g[i].t;
	return h[sink]!=-1;
}
int aug(int x,int flow)
{
	if(x==sink)return flow;
	int tp=flow,d;
	for(int i=Link[x];i;i=g[i].pre)
	{
		if(!g[i].v||h[g[i].t]!=h[x]+1)continue;
		d=min(tp,g[i].v),d=aug(g[i].t,d);
		g[i].v-=d,g[g[i].op].v+=d,tp-=d;
		if(!tp)break;
	}
	if(tp==flow)h[x]=-1;
	return flow-tp;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get(),K=get();
	source=n+m+1,sink=source+1;
	for(int i=1;i<=n;i++)a[i]=get();
	for(int i=1;i<=n;i++)
		if(a[i])add(i,sink,get());else add(source,i,get());
	for(int i=1;i<=m;i++)
	{
		int c=get(),w=get(),k=get(),x;
		while(k--)x=get(),c?add(x,i+n,inf):add(i+n,x,inf);
		ans+=w;w+=get()*K;
		if(c)add(i+n,sink,w);else add(source,i+n,w);
	}
	while(bfs())ans-=aug(source,inf);
	printf("%d\n",ans);
	return 0;
}
