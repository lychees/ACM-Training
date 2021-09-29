#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int N=14,M=1000000007;

int n,m,ans;
int adj[N];
int cb[1<<N],fb[1<<N],pw[N+5];
int cir[1<<N][N],f[1<<N],g[1<<N];

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
			for(int j=0;j<n;j++)
				if(adj[fb[i]]>>j&1)
					(f[i]+=cir[i][j])%=M;
			if(f[i]&1)f[i]+=M;
			f[i]>>=1;
			ans=(ans+(LL)f[i]*pw[cb[i]])%M;
			for(int j=i;j;j=j-1&i)
			{
				g[j]=f[i^j];
				for(int k=0;k<n;k++)
					if(j>>k&1)
						g[j]=(LL)g[j]*cb[adj[k]&(i^j)]%M;
			}
			for(int k=0;k<n;k++)
				if(i>>k&1)
					for(int j=i;j;j=j-1&i)
						if(!(j>>k&1))
							g[j]=(g[j]-g[j|1<<k]+M)%M;
			for(int j=i;j;j=j-1&i)
			{
				(f[i]+=g[j])%=M;
				ans=(ans+g[j]*(LL)pw[cb[i^j]])%M;
			}
		}
	printf("%d\n",ans);
	return 0;
}

