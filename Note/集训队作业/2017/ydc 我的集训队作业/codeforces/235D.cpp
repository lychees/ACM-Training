#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 3010
using namespace std;
bool isCir[maxn];
int a[maxn];
short lca[maxn][maxn];
int n,dfn[maxn],nC,cir[maxn],father[maxn],pos[maxn],dis[maxn];
int nEdge=1,to[maxn*2],next[maxn*2],start[maxn];
void make(int a,int b)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void read()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		++a,++b;
		make(a,b),make(b,a);
	}
}
short LCA(int a,int b)
{
	if(a==b)
		return a;
	if(lca[a][b])
		return lca[a][b];
	short &ans=lca[a][b];
	if(dis[a]>dis[b])
		ans=LCA(father[a],b);
	else if(dis[b]>dis[a])
		ans=LCA(a,father[b]);
	else
		ans=LCA(father[a],father[b]);
	return ans;
}
void DFS(int p,int c)
{
	pos[p]=c;
	for(int i=start[p];i;i=next[i])
		if(!isCir[to[i]]&&!dis[to[i]])
		{
			dis[to[i]]=dis[p]+1,father[to[i]]=p;
			DFS(to[i],c);
		}
}
void Tarjan(int p,int fa)
{
	static int id;
	dfn[p]=++id,father[p]=fa;
	for(int i=start[p];i;i=next[i])
		if(to[i]!=fa)
		{
			int q=to[i];
			if(!dfn[q])
				Tarjan(q,p);
			else if(dfn[q]<dfn[p])
				for(int j=p;j!=father[q];j=father[j])
					isCir[j]=true,cir[++nC]=j;
		}
}
void work()
{
	for(int i=1;i<=nC;++i)
		DFS(cir[i],i);
	double ans=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			if(pos[i]==pos[j])
			{
				int dist=dis[i]+dis[j]-2*dis[LCA(i,j)]+1;
				ans+=1.0/dist;
			}
			else
			{
				int dist=dis[i]+dis[j];
				ans+=1.0/(dist+abs(pos[i]-pos[j])+1)+1.0/(dist+nC-abs(pos[i]-pos[j])+1)-1.0/(dist+nC);
			}
		}
	printf("%.20f\n",ans);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	Tarjan(1,-1);
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
