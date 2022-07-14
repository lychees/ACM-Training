#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 600
#define maxm maxn*maxn*2
using namespace std;
int gap[maxn],dis[maxn];
int N,S,T,sum;
int nEdge,to[maxm],next[maxm],remain[maxm],start[maxn];
void make(int a,int b,int c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge,remain[nEdge]=c;
	++nEdge,to[nEdge]=a,next[nEdge]=start[b],start[b]=nEdge,remain[nEdge]=0;
}
void read()
{
	static int x[maxn],y[maxn],r[maxn],w[maxn];
	int n;
	scanf("%d",&n);
	memset(start,0,sizeof(start));
	nEdge=1,sum=0;
	N=n,S=++N,T=++N;
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d %d %d",x+i,y+i,r+i,w+i);
		if(w[i]>0)
			make(S,i,w[i]),sum+=w[i];
		else
			make(i,T,-w[i]);
		for(int j=1;j<i;++j)
		{
			int dist=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
			if(dist<=r[i]*r[i])
				make(i,j,1<<30);
			if(dist<=r[j]*r[j])
				make(j,i,1<<30);
		}
	}
}
void BFS(int p)
{
	static int queue[maxn];
	memset(dis,-1,sizeof(int)*(N+1));
	memset(gap,0,sizeof(int)*(N+1));
	int front=0,rear=1;
	queue[rear]=p,dis[p]=0,gap[0]=1;
	while(front<rear)
	{
		int p=queue[++front];
		for(int i=start[p];i;i=next[i])
			if(dis[to[i]]==-1)
			{
				dis[to[i]]=dis[p]+1;
				++gap[dis[to[i]]];
				queue[++rear]=to[i];
			}
	}
}
int Sap(int p,int flow)
{
	if(p==T)
		return flow;
	int ans=0;
	for(int i=start[p];i;i=next[i])
		if(remain[i]&&dis[p]==dis[to[i]]+1)
		{
			int t=Sap(to[i],min(flow-ans,remain[i]));
			remain[i]-=t,remain[i^1]+=t,ans+=t;
			if(ans==flow)
				return ans;
		}
	if(--gap[dis[p]]==0)
		dis[S]=N;
	++gap[++dis[p]];
	return ans;
}
int maxflow()
{
	int ans=0;
	for(BFS(T);dis[S]<N;ans+=Sap(S,1<<30));
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	cin>>T;
	for(int C=1;C<=T;++C)
	{
		read();
		printf("Case #%d: %d\n",C,sum-maxflow());
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
