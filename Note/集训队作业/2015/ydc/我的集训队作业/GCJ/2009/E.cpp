#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#define maxn 510
using namespace std;
int col[maxn];
struct Seg
{
	int l,r;
}e[maxn];
struct Block
{
	int n,p[maxn],h1,h2;
	void update()
	{
		static pair<int,int> a[maxn];
		static int dp[maxn];
		int tot=0;
		h1=h2=0;
		for(int i=1;i<=n;++i)
			if(!col[p[i]])
				a[++tot]=make_pair(e[p[i]].l,e[p[i]].r);
		sort(a+1,a+tot+1);
		for(int i=1;i<=tot;++i)
		{
			dp[i]=0;
			for(int j=i-1;j>=1;--j)
				if(dp[i]<dp[j]&&a[i].second<a[j].second)
					dp[i]=dp[j];
			h1=max(h1,++dp[i]);
		}
		tot=0;
		for(int i=1;i<=n;++i)
			if(col[p[i]])
				a[++tot]=make_pair(e[p[i]].l,e[p[i]].r);
		sort(a+1,a+tot+1);
		for(int i=1;i<=tot;++i)
		{
			dp[i]=0;
			for(int j=i-1;j>=1;--j)
				if(dp[i]<dp[j]&&a[i].second<a[j].second)
					dp[i]=dp[j];
			h2=max(h2,++dp[i]);
		}
	}
}B[maxn];
int dp[maxn][maxn][2];
int n,nB,pos[maxn];
int nEdge,to[maxn*maxn],next[maxn*maxn],start[maxn];
void update(int &a,int b)
{
	if(a>b)
		a=b;
}
void make(int a,int b)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void read()
{
	map<string,int> hash;
	static string str[maxn*2];
	scanf("%d",&n);
	memset(e,0,sizeof(e));
	int tot=0;
	for(int i=1;i<=2*n;++i)
	{
		cin>>str[i];
		if(!hash.count(str[i]))
			hash[str[i]]=++tot;
		int x=hash[str[i]];
		if(e[x].l==0)
			e[x].l=i;
		else
			e[x].r=i;
	}
}
bool Paint(int p,int c)
{
	B[nB].p[++B[nB].n]=p;
	col[p]=c,pos[p]=nB;
	for(int i=start[p];i;i=next[i])
	{
		int q=to[i];
		if(pos[q]&&col[p]==col[q])
			return false;
		if(!pos[q]&&!Paint(q,c^1))
			return false;
	}
	return true;
}
bool contain(int a,int b)
{
	if(b==-1)
		return false;
	pair<int,int> A=make_pair(e[a].l,e[a].r);
	pair<int,int> B=make_pair(e[b].l,e[b].r);
	return A.first<B.first&&A.second>B.second;
}
void Get(int cnt[2][2],int a,int b)
{
	for(int i=0;i<=1;++i)
		for(int j=0;j<=1;++j)
			cnt[i][j]=0;
	int p0=-1,p1=-1;
	for(int i=1;i<=B[b].n;++i)
		col[B[b].p[i]]?p1=B[b].p[i]:p0=B[b].p[i];
	if(p0==-1)
		cnt[0][0]=B[a].h1,cnt[1][0]=B[a].h2;
	if(p1==-1)
		cnt[0][1]=B[a].h1,cnt[1][1]=B[a].h2;
	for(int i=1;i<=B[a].n;++i)
	{
		int ca=col[B[a].p[i]];
		if(contain(B[a].p[i],p0))
			++cnt[ca][0];
		if(contain(B[a].p[i],p1))
			++cnt[ca][1];
	}
}
void Tree_Dp(int p)
{
	static int tmp[maxn][2],cnt[2][2],h1[2],h2[2];
	int (*f)[2]=dp[p];
	for(int i=0;i<=n;++i)
		f[i][0]=f[i][1]=1<<30;
	for(int i=B[p].h1;i<=n;++i)
		update(f[i][0],B[p].h2);
	for(int i=B[p].h2;i<=n;++i)
		update(f[i][1],B[p].h1);
	for(int i=start[p];i;i=next[i])
	{
		int (*g)[2]=dp[to[i]];
		Tree_Dp(to[i]);
		for(int j=0;j<=n;++j)
			tmp[j][0]=tmp[j][1]=1<<30;
		Get(cnt,p,to[i]);
		h1[0]=B[p].h1,h1[1]=B[p].h2;
		h2[0]=B[to[i]].h1,h2[1]=B[to[i]].h2;
		for(int d1=0;d1<=1;++d1)
			for(int d2=0;d2<=1;++d2)
				for(int j=max(h1[d1],cnt[d1][d2]);j<=n;++j)
					if(h2[d2^1])
						update(tmp[j][d1],max(h1[d1^1],g[j-cnt[d1][d2]][d2]+cnt[d1^1][d2^1]));
					else
						update(tmp[j][d1],max(h1[d1^1],g[j-cnt[d1][d2]][d2]+cnt[d1^1][d2]));
		for(int j=0;j<=n;++j)
			for(int k=0;k<=1;++k)
				f[j][k]=max(f[j][k],tmp[j][k]);
	}
}
int work()
{
	nEdge=1;
	memset(start,0,sizeof(start));
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
		{
			pair<int,int> a=make_pair(e[i].l,e[i].r);
			pair<int,int> b=make_pair(e[j].l,e[j].r);
			if(a>b)
				swap(a,b);
			if(a.second>b.first&&a.second<b.second)
				make(i,j),make(j,i);
		}
	nB=0;
	memset(pos,0,sizeof(pos));
	for(int i=1;i<=n;++i)
		if(!pos[i])
		{
			B[++nB].n=0;
			if(!Paint(i,0))
				return -1;
			B[nB].update();
		}
	static int minv[maxn],fa[maxn];
	fill(minv+1,minv+nB+1,1<<30);
	memset(fa,-1,sizeof(fa));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(pos[i]!=pos[j])
			{
				pair<int,int> a=make_pair(e[i].l,e[i].r);
				pair<int,int> b=make_pair(e[j].l,e[j].r);
				if(a.first<b.first&&a.second>b.second&&minv[pos[j]]>a.second-a.first)
					minv[pos[j]]=a.second-a.first,fa[pos[j]]=pos[i];
			}
	nEdge=1;
	memset(start,0,sizeof(start));
	for(int i=1;i<=nB;++i)
		if(fa[i]==-1)
			fa[i]=nB+1;
	++nB;
	B[nB].n=0,B[nB].h1=B[nB].h2=0;
	for(int i=1;i<nB;++i)
		make(fa[i],i);
	int ans=1<<30;
	Tree_Dp(nB);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=1;++j)
			update(ans,dp[nB][i][j]+i);
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;++i)
	{
		read();
		printf("Case #%d: %d\n",i,work());
	}
	return 0;
}
