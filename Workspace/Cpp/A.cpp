// Author: Little09
// Problem: G. Weighed Tree Radius
// Contest: Educational Codeforces Round 141 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1783/problem/G
// Memory Limit: 512 MB
// Time Limit: 6000 ms
// Start Time: 2023-01-09 17:43:33
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
const int N=2e5+5;
int n,m;
int t[N*2],nxt[N*2],h[N],cnt;
inline void add(int x,int y)
{
	t[++cnt]=y;
	nxt[cnt]=h[x];
	h[x]=cnt;
}
int deth[N];
int a[N*2],tot,dfn[N],d[N];

void dfs(int x,int f)
{
	deth[x]=deth[f]+1,a[++tot]=x,dfn[x]=tot;
	for (int i=h[x];i;i=nxt[i])
	{
		if (t[i]==f) continue;
		dfs(t[i],x);
		a[++tot]=x;
	}
}
pii f[N*2][21];
void STwork()
{
	int l=__lg(tot);
	for (int i=1;i<=tot;i++) f[i][0]=mkp(deth[a[i]],a[i]);
	for (int i=1;i<=l;i++)
	{
		for (int j=1;j+(1<<i)-1<=tot;j++)
		{
			f[j][i]=min(f[j][i-1],f[j+(1<<(i-1))][i-1]);
		}
	}
}
inline int LCA(int x,int y)
{
	x=dfn[x],y=dfn[y];
	if (x>y) swap(x,y);
	int l=__lg(y-x+1);
	return min(f[x][l],f[y-(1<<l)+1][l]).se;
}
inline int dis(int x,int y)
{
	return deth[x]+deth[y]-deth[LCA(x,y)]*2+d[x]+d[y];
}
struct point
{
	int u,v;
	point(int x=0,int y=0){u=x,v=y;}
	bool operator <(const point &o) const
	{
		if (dis(u,v)<dis(o.u,o.v)) return 1;
		return 0;
	}
};
point operator +(const point &x,const point &y)
{
	point res=max(x,y);
	res=max(res,point(x.u,y.u));
	res=max(res,point(x.u,y.v));
	res=max(res,point(x.v,y.v));
	res=max(res,point(x.v,y.u));
	return res;
}
point s[N*4];
inline void push_up(int u)
{
	s[u]=s[u*2]+s[u*2+1];
}
void build(int u,int l,int r)
{
	if (l==r)
	{
		s[u]=point(l,l);
		return;
	}
	int mid=(l+r)>>1;
	build(u*2,l,mid),build(u*2+1,mid+1,r);
	push_up(u);
}
inline void update(int u,int l,int r,int x)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) update(u*2,l,mid,x);
	else update(u*2+1,mid+1,r,x);
	push_up(u);
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i=1;i<=n;i++) cin >> d[i];
	for (int i=1;i<n;i++)
	{
		int x,y;
		cin >> x >> y;
		add(x,y),add(y,x);
	}
	dfs(1,0);
	STwork();
	cin >> m;
	build(1,1,n);
	while (m--)
	{
		int x,y;
		cin >> x >> y;
		d[x]=y;
		update(1,1,n,x);
		cout << dis(s[1].u,s[1].v) << "\n";
	}
	return 0;
}
