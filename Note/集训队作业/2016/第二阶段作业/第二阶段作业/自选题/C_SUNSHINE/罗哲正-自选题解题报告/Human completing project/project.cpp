#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int N=16,M=998244353;

int n,m,ans;
int adj[N];
int cb[1<<N],fb[1<<N],pw[N+5];
int cir[1<<N][N],f[1<<N];
int d[N],cnt;

void dfs(const int &x,const int &s,const int &t)
{
	if(!t)return;
	if(x==n)
	{
		(f[s]+=t)%=M;
		ans=(ans-((LL)t<<cnt))%M;
		return;
	}
	dfs(x+1,s,t);
	if((~s)>>x&1)
		dfs(x+1,s|1<<x,(LL)-t*d[x]%M);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int u,v,i=0;i<m;i++)
	{
		scanf("%d%d",&u,&v);u--,v--;
		if(u>v)swap(u,v);
		adj[u]|=1<<v,adj[v]|=1<<u;
		cir[1<<u|1<<v][v]++;
	}
	for(int i=pw[0]=1;i<=n;i++)
		pw[i]=pw[i-1]*2%M;
	for(int i=1;i<1<<n;i++)
	{
		for(int j=i;j;j&=j-1)cb[i]++;
		for(int j=i&-i;j>1;j>>=1)fb[i]++;
	}
	for(int i=1,j,k,t;i<1<<n;i++)
		for(j=0;j<n;j++)
			if(t=cir[i][j])
				for(k=fb[i]+1;k<n;k++)
					if(!(i>>k&1)&&(adj[j]>>k&1))
						(cir[i|1<<k][k]+=t)%=M;
	for(int i=1;i<1<<n;i++)
		if(cb[i]>=3)
		{
			int cc=0;
			for(int j=0;j<n;j++)
				if(adj[fb[i]]>>j&1)
					(cc+=cir[i][j])%=M;
			if(cc&1)cc+=M;cc>>=1;
			(f[i]+=cc)%=M;
			for(int j=0;j<n;j++)
				d[j]=cb[adj[j]&i];
			cnt=cb[i];
			dfs(0,i,-f[i]);
		}
	printf("%d\n",(ans+M)%M);
	return 0;
}

