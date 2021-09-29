#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
typedef long long LL;
const int maxn=10233;
bool vis[maxn];
int Link[maxn],t[maxn],pre[maxn],v[maxn],A,B,T,s[maxn],K,st[maxn],len[maxn],tot=0,n,m;
LL distA[maxn],distB[maxn];
inline void add(int x,int y,int z)
{
	pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y; v[tot]=z;
}
void spfa(LL *dist,int S)
{
	for(int i=1;i<=n;i++)dist[i]=1e16,vis[i]=0;
	int front=0,rear=1;
	s[front]=S,dist[S]=0,vis[S]=1;
	while(front!=rear)
	{
		int p=s[front++];
		if(front==maxn)front=0;
		vis[p]=0;
		for(int i=Link[p];i;i=pre[i])
			if(dist[t[i]]>dist[p]+v[i])
			{
				dist[t[i]]=dist[p]+v[i];
				if(!vis[t[i]])
				{
					vis[t[i]]=1;
					s[rear++]=t[i];
					if(rear==maxn)rear=0;
				}
			}
	}
}

void work(int f)
{
	for(bool g=1;g;)
	{
		g=0;
		for(int i=1;i<=K;i++)
			if(distA[st[i]]<distB[st[i]]+f&&v[i+m]!=len[i])g=1,v[i+m]=len[i];
		spfa(distA,A),spfa(distB,B);
		if(distA[T]<distB[T]+f)
		{
			puts(f?"DRAW":"WIN");
			for(int i=1;i<=K;i++)printf("%d ",v[i+m]);
			exit(0);
		}
	}
}

int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();K=get();
	A=get(),B=get(),T=get();
	for(int i=1,x,y;i<=m;i++)x=get(),y=get(),add(x,y,get());
	for(int i=1,y,z;i<=K;i++)
		st[i]=get(),y=get(),len[i]=get(),z=get(),add(st[i],y,z);
	spfa(distA,A),spfa(distB,B);
	work(0),work(1);
	return puts("LOSE"),0;
}
