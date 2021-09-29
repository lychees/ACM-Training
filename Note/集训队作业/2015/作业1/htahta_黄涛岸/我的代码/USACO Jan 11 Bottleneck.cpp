#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
LL get()
{
	LL f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100033;
struct data
{
	int t,v;
	data(){}
	data(int _t,int _v){t=_t,v=_v;}
	inline bool operator <(const data &b)const{return v>b.v;}
}a[maxn];
priority_queue<data> Q;
int n,T,p[maxn],fa[maxn];
LL c[maxn],out[maxn],in[maxn],ans[maxn],t[maxn];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),T=get();
	for(int i=2;i<=n;i++)p[i]=get(),c[i]=get(),in[p[i]]+=(out[i]=get());
	for(int i=1;i<=T;i++)a[i]=data(i,get());
	sort(a+1,a+1+T);
	for(int i=1;i<=n;fa[i]=i,i++)
		if(out[i]>in[i])Q.push(data(i,t[i]=c[i]/(out[i]-in[i])));
	int k=T;
	while(k&&!Q.empty())
	{
		data tp=Q.top();Q.pop();
		int x=tp.t,v=tp.v;
		for(;k&&a[k].v<=v;k--)ans[a[k].t]=c[1]+in[1]*a[k].v;
		if(fa[x]!=x||t[x]!=v)continue;
		fa[x]=getfa(p[x]);
		c[fa[x]]+=c[x],in[fa[x]]-=out[x]-in[x];
		x=getfa(x);
		if(out[x]>in[x])Q.push(data(x,t[x]=c[x]/(out[x]-in[x])));
	}
	for(;k;k--)ans[a[k].t]=c[1]+in[1]*a[k].v;
	for(int i=1;i<=T;i++)printf("%I64d\n",ans[i]);
	return 0;
}
