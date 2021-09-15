#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 40010
#define maxm maxn*2
using namespace std;
struct msgnode
{
	int maxpre,minpre,maxsuf,minsuf;
};
bool ban[maxn];
int n,val[maxn],ans;
int nEdge=1,to[maxm],next[maxm],start[maxn];
void make(int a,int b)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
struct Node
{
	Node *lc,*rc;
	int maxv;
}*Tree[maxm],*Null;
Node* Insert(Node *p,int l,int r,int x,int v1,int v2)
{
	if(p==Null)
	{
		p=new Node;
		*p=*Null;
	}
	p->maxv=max(p->maxv,v1);
	if(l==r)
		return p;
	int mid=(l+r)>>1;
	if(x<=mid)
		p->lc=Insert(p->lc,l,mid,x,v1,v2);
	else
		p->rc=Insert(p->rc,mid+1,r,x,v1,v2);
	return p;
}
int Query(Node *p,int l,int r,int x,int y)
{
	if(p==Null)
		return p->maxv;
	if(l==x&&r==y)
		return p->maxv;
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(p->lc,l,mid,x,y);
	else if(mid<x)
		return Query(p->rc,mid+1,r,x,y);
	else
		return max(Query(p->lc,l,mid,x,mid),Query(p->rc,mid+1,r,mid+1,y));
}
void Erase(Node *p)
{
	if(p->maxv==-1<<30)
		return ;
	p->maxv=-1<<30;
	Erase(p->lc),Erase(p->rc);
}
void read()
{
	scanf("%d",&n);
	for(int i=2,x;i<=n;++i)
	{
		scanf("%d",&x);
		make(x,i),make(i,x);
	}
	char c;
	for(int i=1;i<=n;++i)
	{
		for(c=getchar();c!='('&&c!=')'&&c;c=getchar());
		val[i]=c=='('?1:-1;
		if(c==0)
			val[i]=val[i-1];
	}
	Null=new Node;
	Null->lc=Null->rc=Null,Null->maxv=-1<<30;
	fill(Tree+1,Tree+2*n,Null);
}
int FindRoot(int p)
{
	static int q[maxn],size[maxn],use[maxn],father[maxn],id;
	int tot=0;
	q[++tot]=p,use[p]=++id;
	for(int i=1;i<=tot;++i)
	{
		p=q[i],size[p]=1;
		for(int j=start[p];j;j=next[j])
			if(!ban[to[j]]&&use[to[j]]!=id)
				q[++tot]=to[j],father[to[j]]=p,use[to[j]]=id;
	}
	for(int i=tot;i>1;--i)
		size[father[q[i]]]+=size[q[i]];
	for(int i=1;i<tot;++i)
	{
		int p=q[i],v=tot-size[p];
		for(int j=start[p];j;j=next[j])
			if(use[to[j]]==id&&size[to[j]]<size[p])
				v=max(v,size[to[j]]);
		if(v*2<=tot)
			return p;
	}
	return q[tot];
}
void work(int p)
{
	static msgnode v[maxn];
	static int dis[maxn];
	static int use[maxn],id,q[maxn];
	static int mark[maxn];
	static int maxsufB[maxn*2];
	use[p]=++id,dis[p]=val[p];
	for(int i=start[p];i;i=next[i])
		if(!ban[to[i]])
		{
			int tot=0;
			q[++tot]=to[i],use[to[i]]=id;
			dis[to[i]]=dis[p]+val[to[i]];
			v[to[i]].minpre=min(val[p],val[p]+val[to[i]]);
			v[to[i]].maxpre=max(val[p],val[p]+val[to[i]]);
			v[to[i]].maxsuf=val[to[i]];
			v[to[i]].minsuf=val[to[i]];
			for(int j=1;j<=tot;++j)
			{
				int x=q[j];
				if(mark[n-dis[x]]==id)
				{
					if(n-dis[x]+v[x].minpre>=0&&maxsufB[n-dis[x]]!=-1<<30)
					{
						ans=max(ans,maxsufB[n-dis[x]]);
						ans=max(ans,v[x].maxpre-dis[x]);
					}
					if(v[x].minsuf>=0)
					{
						int val=Query(Tree[n-dis[x]],-n,n,-dis[x],n);
						if(val!=-1<<30)
						{
							ans=max(ans,v[x].maxsuf);
							ans=max(ans,dis[x]+val);
						}
					}
				}
				if(!dis[x]&&val[p]==1&&v[x].minsuf+1>=0)
					ans=max(ans,v[x].maxpre);
				for(int k=start[x];k;k=next[k])
					if(!ban[to[k]]&&use[to[k]]!=id)
					{
						int y=to[k];
						use[y]=id;
						q[++tot]=y;
						dis[y]=dis[x]+val[y];
						v[y].minpre=min(v[x].minpre,dis[y]);
						v[y].maxpre=max(v[x].maxpre,dis[y]);
						v[y].maxsuf=max(v[x].maxsuf,0)+val[y];
						v[y].minsuf=min(v[x].minsuf,0)+val[y];
					}
			}
			for(int j=1;j<=tot;++j)
			{
				int x=q[j];
				if(mark[dis[x]-val[p]+n]!=id)
					mark[dis[x]-val[p]+n]=id,Erase(Tree[dis[x]-val[p]+n]),maxsufB[dis[x]-val[p]+n]=-1<<30;
				Tree[dis[x]-val[p]+n]=Insert(Tree[dis[x]-val[p]+n],-n,n,v[x].minpre-val[p],v[x].maxpre-val[p],v[x].maxsuf);
				if(v[x].minsuf>=0)
					maxsufB[dis[x]-val[p]+n]=max(maxsufB[dis[x]-val[p]+n],v[x].maxsuf);
			}
		}
}
void DFS(int p)
{
	p=FindRoot(p),ban[p]=true;
	work(p);
	for(int i=start[p];i;i=next[i])
		if(ban[to[i]]==false)
			DFS(to[i]);
}
int main()
{
	read();
	DFS(1);
	printf("%d\n",ans);
	return 0;
}
