#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#define pb push_back
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=503,inf=100000000;
map<string,int> hash;
char str[20];
int n,cL[maxn],cR[maxn],Link[maxn],pre[maxn*maxn],t[maxn*maxn],tot;
int col[maxn],N,bL[maxn],bR[maxn],cnt[maxn][2],v[maxn][2],fa[maxn];
bool st[maxn];
int vis[maxn][maxn*2],f[maxn][maxn*2],T,_;
vector<int> block[maxn],g[maxn];
inline void gmin(int &x,int y){if(x>y)x=y;}
inline void gmax(int &x,int y){if(x<y)x=y;}
inline void add(int x,int y)
{
	pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y;
}
int dfs(int x)
{
	int res=1;
	for(int i=0;i<g[x].size();i++)gmax(res,dfs(g[x][i])+1);
	return res;
}
void calc(int x)
{
	vector<int> &a=block[x];
	for(int i=0;i<a.size();i++)g[i].clear();
	for(int i=0;i<a.size();i++)
	{
		int p=-1;
		for(int j=0;j<a.size();j++)
			if(col[a[i]]==col[a[j]]&&cL[a[j]]<cL[a[i]]&&cR[a[i]]<cR[a[j]]&&(p<0||cL[a[j]]>cL[a[p]]))p=j;
		if(p==-1)st[i]=1;else st[i]=0,g[p].pb(i);
	}
	v[x][0]=v[x][1]=0;
	for(int i=0;i<a.size();i++)
		if(st[i])gmax(v[x][col[a[i]]],dfs(i));
}
void build()
{
	for(int i=1;i<=N;i++)
	{
		bL[i]=inf,bR[i]=fa[i]=Link[i]=0;
		for(int j=0;j<block[i].size();j++)
			gmin(bL[i],cL[block[i][j]]),gmax(bR[i],cR[block[i][j]]);
	}
	tot=0;
	for(int i=1;i<=N;i++)
	{
		int k=-1;
		for(int j=1;j<=N;j++)
			if(bL[j]<bL[i]&&bR[i]<bR[j]&&(k<0||bL[j]>bL[k]))k=j;
		if(k>0)add(k,i),fa[i]=k;
	}
	for(int i=1;i<=N;i++)
	{
		calc(i);
		cnt[i][0]=cnt[i][1]=0;
		int k=fa[i];
		for(int j=0,t;j<block[k].size();j++)
			if(cL[t=block[k][j]]<bL[i]&&bR[i]<cR[t])cnt[i][col[t]]++;
	}
}
bool paint(int x,int c)
{
	if(col[x]>=0)return col[x]==c;
	col[x]=c;block[N].pb(x);
	for(int i=Link[x];i;i=pre[i])
		if(!paint(t[i],1-c))return 0;
	return 1;
}
inline bool have_answer()
{
	tot=0,memset(Link,0,4*(n+1));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(cL[i]<cL[j]&&cL[j]<cR[i]&&cR[i]<cR[j])add(i,j),add(j,i);
	N=0,memset(col,-1,4*(n+1));
	for(int i=1;i<=n;i++)
	{
		if(col[i]>=0)continue;
		block[++N].clear();
		if(!paint(i,0))return 0;
	}
	build();
	return 1;
}
bool init()
{
	hash.clear();
	n=get();
	for(int i=1,tot=0;i<=n*2;i++)
	{
		scanf("%s",str);
		if(!hash.count(str))cL[++tot]=i,hash[str]=tot;
		else cR[hash[str]]=i;
	}
	return have_answer();
}
int dp(int x,int h)
{
	if(h<0)return inf;
	if(vis[x][h]==_)return f[x][h];
	f[x][h]=inf,vis[x][h]=_;
	for(int i=0;i<2;i++)
	{
		if(v[x][i]>h)continue;
		int res=v[x][1-i];
		for(int j=Link[x];j;j=pre[j])
			gmax(res,dp(t[j],h-cnt[t[j]][i])+cnt[t[j]][1-i]);
		gmin(f[x][h],res);
	}
	return f[x][h];
}
int work()
{
	int ans=inf;
	for(int i=0;i<=n;i++)
	{
		int res=0;
		for(int j=1;j<=N;j++)
			if(!fa[j])gmax(res,dp(j,i));
		gmin(ans,res+i);
		if(i>=res)break;
	}
	return ans;
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	for(_=1,T=get();_<=T;_++)
		printf("Case #%d: %d\n",_,!init()?-1:work());
	return 0;
}
