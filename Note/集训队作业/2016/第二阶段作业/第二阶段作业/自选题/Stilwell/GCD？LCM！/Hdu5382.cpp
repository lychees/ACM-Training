#include <stdio.h>
#include <stdlib.h>
#define P 258280327
using namespace std;

int T,n,i,j,k,tot;
int prime[1000005],p[1000005];
int sum[1000005],f[1000005],S[1000005],Sum,ans;

int main()
{
	n=1000000;
	for(i=2;i<=n;++i)
	{
		if(!p[i])prime[++tot]=p[i]=i;
		for(j=1;j<=tot&&prime[j]<=p[i]&&prime[j]<=n/i;++j)p[i*prime[j]]=prime[j];
	}
	f[1]=1;
	for(i=2;i<=n;++i)
	if(p[i]==p[i/p[i]])f[i]=f[i/p[i]];
	else
	{
		f[i]=f[i/p[i]]<<1;
		if(f[i]>=P)f[i]-=P;
	}
	for(i=1;i<=n;++i)
	for(j=i+i,k=1;j<=n;j+=i,++k)
	{
		sum[j]+=f[k];
		if(sum[j]>=P)sum[j]-=P;
	}
	for(i=1;i<=n;++i)
	{
		Sum=(Sum+i*2+P-1-sum[i-1])%P;
		S[i]=S[i-1]+Sum;if(S[i]>=P)S[i]-=P;
	}
	scanf("%d",&T);
	for(;T;--T)
	{
		scanf("%d",&n);
		printf("%d\n",S[n]);
	}
}
