#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
struct Edge
{
	int u,v,id,len;
}e[maxn];
int n,m,ori[maxn],use[maxn*20];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].len);
		e[i].id=i,ori[i]=e[i].len;
	}
}
int Directed_MST(int root)
{
	static int all[maxn*20][2],pre[maxn],preid[maxn],in[maxn],id[maxn],pos[maxn];
	int nall=m,ans=0;
	while(1)
	{
		fill(in+1,in+n+1,1<<30);
		memset(pos,0,sizeof(int)*(n+1));
		memset(id,0,sizeof(int)*(n+1));
		for(int i=1;i<=m;++i)
			if(e[i].u!=e[i].v&&in[e[i].v]>e[i].len)
				in[e[i].v]=e[i].len,pre[e[i].v]=e[i].u,preid[e[i].v]=e[i].id;
		in[root]=0;
		int nCircle=0;
		for(int i=1;i<=n;++i)
		{
			if(in[i]==1<<30)
				return -1;
			if(i!=root)
				++use[preid[i]];
			int v;
			ans+=in[i];
			for(v=i;v!=root&&pos[v]==0;v=pre[v])
				pos[v]=i;
			if(v!=root&&id[v]==0&&pos[v]==i)
			{
				id[v]=++nCircle;
				for(int j=pre[v];j!=v;j=pre[j])
					id[j]=nCircle;
			}
		}
		if(!nCircle)
			break;
		for(int i=1;i<=n;++i)
			if(id[i]==0)
				id[i]=++nCircle;
		for(int i=1;i<=m;++i)
		{
			int &u=e[i].u,&v=e[i].v,&w=e[i].len,pre=preid[v];
			w-=in[v];
			u=id[u],v=id[v];
			if(u!=v)
			{
				++nall;
				all[nall][0]=e[i].id,all[nall][1]=pre;
				e[i].id=nall;
			}
		}
		n=nCircle,root=id[root];
	}
	for(int i=nall;i>m;--i)
		if(use[i])
			++use[all[i][0]],--use[all[i][1]];
	return ans;
}
void print()
{
	int ans=Directed_MST(1);
	printf("%d\n",ans);
	if(ans!=-1)
	{
		for(int i=1;i<=m;++i)
			if(ori[i]&&use[i])
				printf("%d ",i);
		printf("\n");
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
