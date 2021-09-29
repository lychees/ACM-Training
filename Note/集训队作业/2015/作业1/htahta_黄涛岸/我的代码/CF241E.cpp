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
const int maxn=1003,maxm=10033,inf=1000000000;
int n,m,Link[maxn],pre[maxm],t[maxm],v[maxm],dist[maxm],s[maxn],cnt[maxn];
bool vis[maxn],can[maxn],can2[maxn];
void dfs(int x)
{
	can[x]=1;
	for(int i=Link[x];i;i=pre[i])
		if(!can[t[i]]&&v[i]<0)dfs(t[i]);
}
void dfs2(int x)
{
	can2[x]=1;
	for(int i=Link[x];i;i=pre[i])
		if(!can2[t[i]]&&v[i]>0)dfs2(t[i]);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	for(int i=1,tot=0;i<=m;i++)
	{
		int x=get(),y=get();
		pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y; v[tot]=2;
		pre[++tot]=Link[y]; Link[y]=tot; t[tot]=x; v[tot]=-1;
	}
	dfs(n);dfs2(1);
	for(int i=1;i<=m+m;i+=2)
		if(!(can2[t[i+1]]&&can[t[i]]))v[i]=v[i+1]=0;
	int front=0,rear=1;
	for(int i=2;i<=n;i++)dist[i]=inf;
	s[front]=1,vis[1]=1,dist[1]=0;
	while(front!=rear)
	{
		int p=s[front];
		for(int i=Link[p];i;i=pre[i])
			if(dist[t[i]]>dist[p]+v[i]&&v[i])
			{
				dist[t[i]]=dist[p]+v[i];
				if(!vis[t[i]])
				{
					cnt[t[i]]++;
					if(cnt[t[i]]>=n)return puts("No"),0;
					vis[t[i]]=1,s[rear++]=t[i];
					if(rear==n)rear=0;
				}
			}
		front++,vis[p]=0;
		if(front==n)front=0;
	}
	puts("Yes");
	for(int i=1;i<=m+m;i+=2)
	{
		int x=t[i+1],y=t[i],d=dist[y]-dist[x];
		if(d<1||d>2)d=1;
		printf("%d\n",d);
	}
	return 0;
}
