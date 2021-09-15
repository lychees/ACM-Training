#include<cstdio>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 100010
#define maxm maxn*2
using namespace std;
int n,m,size[maxn],root,dep[maxn],father[maxn],pos[maxn],col[maxn],maxdep[maxn];
int nEdge=1,to[maxm],next[maxm],len[maxm],start[maxn];
void addedge(int a,int b,int c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge,len[nEdge]=c;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1,x;i<=m;++i)
	{
		scanf("%d",&x);
		size[x]=col[x]=1;
	}
	for(int i=2,a,b,c;i<=n;++i)
	{
		scanf("%d %d %d",&a,&b,&c);
		addedge(a,b,c),addedge(b,a,c);
	}
}
int FindRoot()
{
	static int use[maxn],dis[maxn],fa[maxn];
	queue<int> q;
	int a,x=-1,y=-1;
	for(int i=1;i<=n;++i)
		if(col[i])
		{
			a=i;
			break;
		}
	q.push(a),use[a]=1,dis[a]=0;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(int i=start[p];i;i=next[i])
			if(use[to[i]]!=1)
			{
				dis[to[i]]=dis[p]+len[i];
				q.push(to[i]);
				use[to[i]]=1;
				if(col[to[i]]&&(x==-1||dis[x]<dis[to[i]]))
					x=to[i];
			}
	}
	q.push(x),use[x]=2,dis[x]=0;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(int i=start[p];i;i=next[i])
			if(use[to[i]]!=2)
			{
				dis[to[i]]=dis[p]+len[i];
				q.push(to[i]);
				use[to[i]]=2;
				if(col[to[i]]&&(y==-1||dis[y]<dis[to[i]]))
					y=to[i];
				fa[to[i]]=p;
			}
	}
	int minv=1<<30,id;
	for(int i=y;i!=x;i=fa[i])
	{
		int del=abs(dis[i]-(dis[y]-dis[i]));
		if(minv>del)
			minv=del,id=i;
	}
	return id;
}
void DFS(int p)
{
	if(col[p])
		maxdep[p]=dep[p];
	for(int i=start[p];i;i=next[i])
		if(to[i]!=father[p])
		{
			father[to[i]]=p;
			dep[to[i]]=dep[p]+len[i];
			pos[to[i]]=p==root?to[i]:pos[p];
			DFS(to[i]);
			maxdep[p]=max(maxdep[p],maxdep[to[i]]);
			size[p]+=size[to[i]];
		}
}
void work()
{
	int maxv=0,sum=0,max1=0,max2=0,s1=0,s2=0,num1,num2;
	for(int i=start[root];i;i=next[i])
	{
		int x=to[i];
		if(max1<maxdep[x])
			max2=max1,max1=maxdep[x],s2=s1,s1=1,num1=x;
		else if(max1==maxdep[x])
			++s1,num2=x;
		else if(max2<maxdep[x])
			max2=maxdep[x],s2=1;
		else if(max2==maxdep[x])
			++s2;
	}
	for(int i=1;i<=n;++i)
		if(!col[i])
		{
			int val;
			if(i==root)
				val=size[i];
			else
			{
				val=size[i];
				if(maxdep[i]==max1&&s1==1)
					val+=size[root]-size[pos[i]];
				if(maxdep[i]==max1&&s1==2)
					val+=size[pos[i]==num1?num2:num1];
				if(maxdep[i]==max2&&s1==1&&s2==1)
					val+=size[num1];
			}
			if(maxv<val)
				maxv=val,sum=1;
			else if(maxv==val)
				++sum;
		}
	printf("%d %d\n",maxv,sum);
}
int main()
{
	freopen("348E.in","r",stdin);
	//freopen("348E.out","w",stdout);
	read();
	root=FindRoot();
	DFS(root);
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
