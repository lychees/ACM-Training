#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxm 200000
#define maxn 20
#define mod 10007
using namespace std;
typedef long long LL;
const int MOD=244177;
struct HashTable
{
	int nEdge,next[maxm],start[MOD+10];
	LL to[maxm];
	int Query(LL p)
	{
		for(int i=start[p%MOD];i;i=next[i])
			if(to[i]==p)
				return i;
		++nEdge,to[nEdge]=p,next[nEdge]=start[p%MOD],start[p%MOD]=nEdge;
		return nEdge;
	}
	void clear()
	{
		nEdge=0;
		memset(start,0,sizeof(start));
	}
}T;
int tot,h[maxm][maxn];
int nRow,nCol,F[maxn];
char map[maxn][maxn];
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
void read()
{
	T.clear(),tot=0;
	scanf("%d %d",&nRow,&nCol);
	for(int i=1;i<=nRow;++i)
		scanf("%s",map[i]+1);
}
void DFS(int p)
{
	if(p>nRow)
	{
		LL sum=0;
		++tot;
		for(int i=1;i<=nRow;++i)
			h[tot][i]=F[i],sum=sum*15+F[i];
		T.Query(sum);
		return ;
	}
	for(int i=F[p-1];i<=nCol;++i)
	{
		F[p]=i;
		DFS(p+1);
	}
}
int Dp()
{
	static int vis[30];
	static LL pw[maxn];
	static int dp[maxm],sum[maxn][maxm];
	static int t1[maxn][maxn],t2[maxn][maxn];
	memset(vis,0,sizeof(vis));
	pw[0]=1;
	for(int i=1;i<=15;++i)
		pw[i]=pw[i-1]*15;
	for(int i=1;i<=nRow;++i)
	{
		t1[i][0]=0;
		t2[i][nCol+1]=1<<30;
		for(int j=1;j<=nCol;++j)
			t1[i][j]=max(t1[i][j-1],(int)map[i][j]);
		for(int j=nCol;j>=1;--j)
		{
			t2[i][j]=t2[i][j+1];
			if(isalpha(map[i][j]))
			{
				t2[i][j]=min(t2[i][j],(int)map[i][j]);
				vis[map[i][j]-'a']=1;
			}
		}
	}
	memset(dp,0,sizeof(dp));
	dp[1]=1;
	for(int j=1;j<=tot;++j)
		for(int k=1;k<=nRow;++k)
			sum[k][j]=h[j][nRow-k]==0;
	for(int i=0;i<26;++i)
	{
		for(int j=tot;j>=1;--j)
		{
			if(vis[i])
				dp[j]=0;
			bool mark=true;
			for(int k=1;k<=nRow;++k)
			{
				int col=h[j][nRow-k+1];
				if(t1[k][col]>i+'a')
					mark=false;
				if(t2[k][col+1]<=i+'a')
					mark=false;
			}
			if(mark)
				for(int k=nRow;k>=1;--k)
					if(h[j][nRow-k+1]&&h[j][nRow-k+1]!=h[j][nRow-k])
						add(dp[j],sum[k][T.Query(T.to[j]-pw[k-1])]);
		}
		for(int j=1;j<=tot;++j)
		{
			for(int k=1;k<=nRow;++k)
			{
				sum[k][j]=0;
				if(k>1)
					add(sum[k][j],sum[k-1][j]);
				if(h[j][nRow-k+1]&&h[j][nRow-k+1]!=h[j][nRow-k])
					add(sum[k][j],sum[k][T.Query(T.to[j]-pw[k-1])]);
			}
			for(int k=1;k<=nRow;++k)
				add(sum[k][j],dp[j]);
		}
	}
	return dp[tot];
}
int main()
{
	freopen("input.txt","r",stdin);
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;++i)
	{
		read();
		DFS(1);
		printf("Case #%d: %d\n",i,Dp());
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
