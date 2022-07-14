#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxc 60
#define maxn maxc*maxc
#define maxm maxn*10
using namespace std;
int S,T,N;
int sum;
int dis[maxn],gap[maxn];
int nRow,nCol;
int nEdge,to[maxm],next[maxm],remain[maxm],start[maxn];
int movex[]={1,-1,0,0};
int movey[]={0,0,1,-1};
void make(int a,int b,int c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge,remain[nEdge]=c;
	++nEdge,to[nEdge]=a,next[nEdge]=start[b],start[b]=nEdge,remain[nEdge]=0;
}
void read()
{
	memset(start,0,sizeof(start));
	nEdge=1,sum=0;
	scanf("%d %d",&nRow,&nCol);
	static char map[maxc][maxc];
	N=nRow*nCol,S=++N,T=++N;
	for(int i=1;i<=nRow;++i)
		scanf("%s",map[i]+1);
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
			if(map[i][j]!='.')
			{
				int x=(i-1)*nCol+j;
				sum+=4;
				if((i+j)&1)
				{
					make(S,x,map[i][j]=='#'?1<<30:4);
					for(int k=0;k<4;++k)
						if(i+movex[k]>=1&&i+movex[k]<=nRow&&j+movey[k]>=1&&j+movey[k]<=nCol&&map[i+movex[k]][j+movey[k]]!='.')
						{
							int y=(i+movex[k]-1)*nCol+j+movey[k];
							make(x,y,2);
						}
				}
				else
					make(x,T,map[i][j]=='#'?1<<30:4);
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
			int t=Sap(to[i],min(remain[i],flow-ans));
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
	int	ans=0;
	for(BFS(T);dis[S]<N;ans+=Sap(S,1<<30));
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		read();
		printf("Case #%d: %d\n",++C,sum-maxflow());
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
