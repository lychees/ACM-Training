#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#define maxn 11010
using namespace std;
typedef long long LL;
struct Edge
{
	int v,id;
	Edge() {}
	Edge(int v,int id): v(v),id(id) {}
};
vector<Edge>adj[maxn];
struct Node
{
	int p;
	LL dis;
	Node() {}
	Node(int p,LL dis): p(p),dis(dis) {}
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.dis>b.dis;
	}
};
priority_queue<Node> Q;
LL dis[2][maxn];
int n,m,k,S1,S2,T,cost[maxn];
int u[maxn],v[maxn],L[maxn],R[maxn];
int Tree[maxn],nTree;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	Read(n),Read(m),Read(k),Read(S1),Read(S2),Read(T);
	for(int i=1,a,b,c;i<=m;++i)
	{
		Read(a),Read(b),Read(c);
		adj[a].push_back(Edge(b,i)),cost[i]=c;
	}
	for(int i=1;i<=k;++i)
	{
		Read(u[i]),Read(v[i]),Read(L[i]),Read(R[i]);
		adj[u[i]].push_back(Edge(v[i],i+m)),cost[i+m]=R[i];
	}
}
void print(string str)
{
	cout<<str<<endl;
	if(str=="LOSE")
		exit(0);
	for(int i=m+1;i<=m+k;++i)
		printf("%d%c",cost[i],i<m+k?' ':'\n');
	exit(0);
}
void Modify(int p,LL v,LL *dis)
{
	dis[p]=v,p+=nTree;
	for(p>>=1;p;p>>=1)
		Tree[p]=dis[Tree[p<<1]]<dis[Tree[p<<1|1]]?Tree[p<<1]:Tree[p<<1|1];
}
void Dijkstra(int S,LL *dis) 
{
	static bool use[maxn];
	for(int i=1;i<=n;++i)
		dis[i]=100000000000000LL;
	dis[S]=0,dis[0]=100000000000000LL;
	memset(use,false,sizeof(bool)*(n+1));
	for(nTree=1;nTree-2<n;nTree<<=1);
	for(int i=nTree+1;i<=nTree+n;++i)
		Tree[i]=i-nTree;
	for(int i=nTree;i>=1;--i)
		Tree[i]=dis[Tree[i<<1]]<dis[Tree[i<<1|1]]?Tree[i<<1]:Tree[i<<1|1];
	static LL ans[maxn];
	fill(ans+1,ans+n+1,100000000000000LL);
	for(int i=1;dis[Tree[1]]<100000000000000LL;++i)
	{
		int p=Tree[1];
		LL c=dis[p];
		ans[p]=c;
		Modify(p,100000000000000LL,dis);
		use[p]=true;
		for(vector<Edge>::iterator e=adj[p].begin();e!=adj[p].end();++e)
			if(!use[e->v]&&dis[e->v]>c+cost[e->id])
			{
				dis[e->v]=c+cost[e->id];
				Modify(e->v,dis[e->v],dis);
			}
	}
	for(int i=1;i<=n;++i)
		dis[i]=ans[i];
}
void Greedy()
{
	Dijkstra(S1,dis[0]),Dijkstra(S2,dis[1]);
	if(dis[0][T]<dis[1][T])
		print("WIN");
	bool mark=true;
	while(mark)
	{
		mark=false;
		for(int i=1;i<=k;++i)
			if(dis[0][u[i]]<dis[1][u[i]]&&cost[i+m]==R[i]&&L[i]!=R[i])
			{
				cost[i+m]=L[i],Dijkstra(S1,dis[0]),Dijkstra(S2,dis[1]);
				if(dis[0][T]<dis[1][T])
					print("WIN");
				mark=true;
			}
	}
	print(dis[0][T]==dis[1][T]?"DRAW":"LOSE");  
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	Greedy();
	return 0;
}
