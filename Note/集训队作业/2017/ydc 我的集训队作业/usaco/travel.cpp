#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 100010
#define maxm 400010
using namespace std;
struct Edge
{
	int x,y,val;
	Edge() {}
	Edge(int x,int y,int val): x(x),y(y),val(val) {}
	friend bool operator < (const Edge &a,const Edge &b)
	{
		return a.x<b.x;
	}
};
struct Node
{
	int dis,v;
	Node() {}
	Node(int dis,int v): dis(dis),v(v) {}
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.dis>b.dis;
	}
};
vector<int> adj[maxn];
int L[maxn],R[maxn],stack[maxn],top;
int n,m,dis[maxn];
int nEdge=1,to[maxm],next[maxm],len[maxm],start[maxn];
int Tree[maxn<<2],nTree;
void make(int a,int b,int c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge,len[nEdge]=c;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1,a,b,c;i<=m;++i)
	{
		scanf("%d %d %d",&a,&b,&c);
		make(a,b,c),make(b,a,c);
	}
}
void Dijkstra(int p)
{
	priority_queue<Node> Q;
	fill(dis+1,dis+n+1,1<<30);
	dis[p]=0;
	static int fa[maxn];
	static bool use[maxn];
	Q.push(Node(dis[p],p));
	while(!Q.empty())
	{
		Node p=Q.top();
		Q.pop();
		if(use[p.v])
			continue;
		use[p.v]=true;
		for(int i=start[p.v];i;i=next[i])
			if(dis[to[i]]>p.dis+len[i])
			{
				dis[to[i]]=p.dis+len[i];
				fa[to[i]]=p.v;
				Q.push(Node(dis[to[i]],to[i]));
			}
	}
	for(int i=2;i<=n;++i)
		adj[fa[i]].push_back(i);
}
void DFS(int p)
{
	stack[++top]=p,L[p]=top;
	each(x,adj[p])
		DFS(*x);
	R[p]=top;
}
void Modify(int x,int v)
{
	Tree[x+nTree]=v;
	for(int i=(x+nTree)>>1;i;i>>=1)
		Tree[i]=min(Tree[i<<1],Tree[i<<1|1]);
}
int Query(int l,int r)
{
	int ans=1<<30;
	for(l=l+nTree-1,r=r+nTree+1;l^r^1;l>>=1,r>>=1)
	{
		if(~l&1)
			ans=min(ans,Tree[l^1]);
		if(r&1)
			ans=min(ans,Tree[r^1]);
	}
	return ans;
}
void work()
{
	static Edge e[maxm];
	static int val[maxn],ans[maxn];
	int nE=0;
	for(int i=1;i<=n;++i)
		for(int j=start[i];j;j=next[j])
			if(dis[to[j]]-dis[i]!=len[j])
				e[++nE]=Edge(L[i],L[to[j]],dis[i]+dis[to[j]]+len[j]);
	for(nTree=1;nTree-2<n;nTree<<=1);
	fill(Tree+1,Tree+nTree+nTree+1,1<<30);
	fill(val+1,val+n+1,1<<30);
	fill(ans+1,ans+n+1,1<<30);
	sort(e+1,e+nE+1);
	for(int i=2,j=1;i<=n;++i)
	{
		for(;j<=nE&&e[j].x<i;++j)
			if(val[e[j].y]>e[j].val)
				val[e[j].y]=e[j].val,Modify(e[j].y,e[j].val);
		int minv=Query(i,R[stack[i]]);
		if(minv!=1<<30)
			ans[stack[i]]=min(ans[stack[i]],minv-dis[stack[i]]);
	}
	for(nTree=1;nTree-2<n;nTree<<=1);
	fill(Tree+1,Tree+nTree+nTree+1,1<<30);
	fill(val+1,val+n+1,1<<30);
	static pair<int,int> seq[maxn];
	int cnt=0;
	for(int i=2;i<=n;++i)
		seq[++cnt]=make_pair(R[i],i);
	sort(seq+1,seq+n+1);
	for(int i=cnt,j=nE;i>=1;--i)
	{
		for(;j>=1&&e[j].x>seq[i].first;--j)
			if(val[e[j].y]>e[j].val)
				val[e[j].y]=e[j].val,Modify(e[j].y,e[j].val);
		int minv=Query(L[seq[i].second],seq[i].first);
		if(minv!=1<<30)
			ans[seq[i].second]=min(ans[seq[i].second],minv-dis[seq[i].second]);
	}
	for(int i=2;i<=n;++i)
		printf("%d\n",ans[i]==1<<30?-1:ans[i]);
}
int main()
{
	read();
	Dijkstra(1);
	DFS(1);
	work();
	return 0;
}
