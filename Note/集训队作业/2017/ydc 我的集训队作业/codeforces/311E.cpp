#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 30000
#define maxm 100000
int gap[maxn],dis[maxn],temp[maxn];
int ans,sex[maxn],S,T,N;
int tot=1,to[maxm],next[maxm],remain[maxm],start[maxn];
void make(int a,int b,int c)
{
	tot++,to[tot]=b,next[tot]=start[a],remain[tot]=c,start[a]=tot;
	tot++,to[tot]=a,next[tot]=start[b],remain[tot]=0,start[b]=tot;
}
void read()
{
	int n,m,g;
	scanf("%d %d %d",&n,&m,&g);
	S=1,T=S+n+m+1,N=T;
	for(int i=1;i<=n;i++)
		scanf("%d",&sex[i]);
	for(int i=1,v;i<=n;i++)
	{
		scanf("%d",&v);
		sex[i]==0?make(S,S+i,v):make(S+i,T,v);
	}
	static int p[15];
	for(int i=1,w,k,t,isfriend,p;i<=m;i++)
	{
		scanf("%d %d %d",&t,&w,&k);
		ans+=w;
		for(int j=1;j<=k;j++)
		{
			scanf("%d",&p);
			t==0?make(S+n+i,S+p,1<<30):make(S+p,S+n+i,1<<30);
		}
		scanf("%d",&isfriend);
		if(isfriend)
			w+=g;
		t==0?make(S,S+n+i,w):make(S+n+i,T,w);
	}
}
void Prepare(int a[],int b[])
{
	for(int i=1;i<=N;i++)
		a[i]=b[i];
}
void BFS(int p)
{
	static int queue[maxn];
	for(int i=1;i<=N;i++)
		dis[i]=-1,gap[i]=0;
	int front=0,rear=1;
	gap[dis[p]=0]=1,queue[rear]=p;
	while(front<rear)
	{
		int p=queue[++front];
		for(int i=start[p];i;i=next[i])
			if(dis[to[i]]==-1)
			{
				queue[++rear]=to[i];
				gap[dis[to[i]]=dis[p]+1]++;
			}
	}
}
int Sap(int p,int flow,int start[])
{
	if(p==T)
		return flow;
	int ans=0;
	for(int &i=start[p];i;i=next[i])
		if(dis[p]==dis[to[i]]+1&&remain[i])
		{
			int t=Sap(to[i],std::min(flow-ans,remain[i]),start);
			remain[i]-=t,remain[i^1]+=t,ans+=t;
			if(ans==flow)
				return ans;
		}
	if(dis[S]>N)
		return ans;
	if(--gap[dis[p]]==0)
		dis[S]=N;
	++gap[++dis[p]];
	return ans;
}
int MaxFlow()
{
	static int temp[maxn];
	int sum=0;
	for(BFS(T);dis[S]<N;Prepare(temp,start),sum+=Sap(S,1<<30,temp));
	return sum;
}
int main()
{
	read();
	printf("%d\n",ans-MaxFlow());
	return 0;
}
