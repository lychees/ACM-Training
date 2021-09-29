#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#define pb push_back
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100005,inf=314000000;
vector<int> rule[maxn],g[maxn],belong[maxn];
struct data
{
	int t,v;
	data(){}
	data(int _t,int _v){t=_t,v=_v;}
	inline bool operator <(const data &b)const{return v>b.v;}
};
priority_queue<data> Q;
int T[maxn],cnt[maxn],n,m,a[maxn],b[maxn],val[maxn],vis[maxn];
void init()
{
	m=get(),n=get();
	memset(a,60,sizeof(a));
	for(int i=1;i<=m;i++)
	{
		int x=get(),y=get(),t;
		g[x].pb(i),rule[i].pb(x);
		while(y--)
			if((t=get())<0)val[i]++;else rule[i].pb(t),belong[t].pb(i),T[i]++;
		if(!T[i])a[x]=min(a[x],val[i]);
		cnt[i]=val[i];
	}
}

int dfs(int x)
{
	if(vis[x])return b[x];
	vis[x]=1;
	for(int i=0;i<g[x].size();i++)
	{
		int id=g[x][i],flag=1,tot=cnt[id];
		for(int j=1;j<rule[id].size()&&flag;j++)
			if(a[rule[id][j]]>inf)flag=0;
		if(!flag)continue;
		flag=0;
		for(int j=1;j<rule[id].size();j++)
		{
			int p=rule[id][j],v;
			if(vis[p]==1){flag=1;break;}
			v=dfs(p);
			if(v==-2){flag=1;break;}
			tot=min(tot+v,inf);
		}
		if(flag){b[x]=-2;break;}
		b[x]=max(b[x],tot);
	}
	vis[x]=2;
	return b[x];
}

void work()
{
	for(int i=1;i<=n;i++)
		if(a[i]<1e9)Q.push(data(i,a[i]));
	while(!Q.empty())
	{
		data tp=Q.top();Q.pop();
		int t=tp.t,v=tp.v;
		if(a[t]!=v)continue;
		for(int i=0;i<belong[t].size();i++)
		{
			int p=belong[t][i],s=rule[p][0];
			val[p]=min(val[p]+v,inf);T[p]--;
			if(!T[p]&&a[s]>val[p])Q.push(data(s,a[s]=val[p]));
		}
	}
	for(int i=1;i<=n;i++)
		if(a[i]<=inf)dfs(i);
	for(int i=1;i<=n;i++)
		if(a[i]>inf)puts("-1 -1");else printf("%d %d\n",a[i],b[i]);
}

int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	init();
	work();
	return 0;
}
