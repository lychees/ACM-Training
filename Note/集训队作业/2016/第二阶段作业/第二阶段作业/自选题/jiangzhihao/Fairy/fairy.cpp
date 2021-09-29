#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
const int N = 1005000;
const int M = 2005000;
int point[N],to[M],next[M],num[M],cc;
struct Info
{
	int x,y;
	bool ever;
}xu[N];
int depth[N],fa[N],fanum[N],val[N],valx[N];
bool everx[N],every[N];
int sc[N];
int n,m;
int getint()
{
	int res=0;
	char ch=getchar();
	while((ch<'0' || ch>'9') && ch!='-')
		ch=getchar();
	bool fan=0;
	if(ch=='-')
	{
		fan=1;
		ch=getchar();
	}
	while('0'<=ch && ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	if(fan)
		res=-res;
	return res;
}
void AddOne(int x,int y,int z)
{
	cc++;
	next[cc]=point[x];
	point[x]=cc;
	to[cc]=y;
	num[cc]=z;
}
void AddEdge(int x,int y,int z)
{
	AddOne(x,y,z);
	AddOne(y,x,z);
}
int getf(int x)
{
	if(fa[x]!=x)
		fa[x]=getf(fa[x]);
	return fa[x];
}
void GetData()
{
	int i;
	n=getint();
	m=getint();
	for(i=1;i<=m;i++)
	{
		int x=getint();
		int y=getint();
		AddEdge(x,y,i);
		xu[i].x=x;
		xu[i].y=y;
	}
}
void Dfs(int x)
{
	everx[x]=1;
	depth[x]=depth[fa[x]]+1;
	int now=point[x];
	while(now)
	{
		int tox=to[now];
		if(!everx[tox])
		{
			fa[tox]=x;
			fanum[tox]=num[now];
			xu[num[now]].ever=1;
			Dfs(tox);
		}
		now=next[now];
	}
}
void DfsX(int x,int y)
{
	every[x]=1;
	int now=point[x];
	while(now)
	{
		int tox=to[now];
		if(!every[tox])
			DfsX(tox,y);
		now=next[now];
	}
	if(val[x]==y && !valx[x] && fa[x])
		sc[++sc[0]]=fanum[x];
	val[fa[x]]+=val[x];
	valx[fa[x]]+=valx[x];
}
void DoIt()
{
	int i;
	memset(fa,0,sizeof fa);
	for(i=1;i<=n;i++)
	{
		if(!everx[i])
			Dfs(i);
	}
	for(i=1;i<=m;i++)
	{
		if(!xu[i].ever)
		{
			int a=xu[i].x;
			int b=xu[i].y;
			if(depth[a]<depth[b])
				swap(a,b);
			if((depth[a]^depth[b]^1)&1)
			{
				val[a]++;
				val[b]--;
				sc[++sc[0]]=i;
			}
			else
			{
				valx[a]++;
				valx[b]--;
			}
		}
	}
	int tot=sc[0];
	if(!tot)
	{
		for(i=1;i<=m;i++)
			sc[++sc[0]]=i;
	}
	else
	{
		if(sc[0]>1)
			sc[0]=0;
		for(i=1;i<=n;i++)
		{
			if(!every[i])
				DfsX(i,tot);
		}
		sort(sc+1,sc+sc[0]+1);
	}
	printf("%d\n",sc[0]);
	for(i=1;i<=sc[0];i++)
	{
		printf("%d",sc[i]);
		if(i<sc[0])
			printf(" ");
	}
	if(sc[0])
		printf("\n");
}
int main()
{
	GetData();
	DoIt();
	return 0;
}
