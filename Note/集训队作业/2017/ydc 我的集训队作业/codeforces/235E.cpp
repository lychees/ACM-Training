#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<assert.h>
#define maxn 2010
#define mod 1073741824 
using namespace std;
int A,B,C,g[maxn][maxn];
int gcd(int a,int b)
{
	if(b==0)
		return a;
	if(g[a][b])
		return g[a][b];
	g[a][b]=gcd(b,a%b);
	return g[a][b];
}
int calc()
{
	static int mu[maxn],f[maxn],F[maxn*maxn];
	mu[1]=1;
	for(int i=1;i<=C;++i)
		for(int j=1;j<=C/i;++j)
			f[i]+=C/i/j;
	for(int i=2;i<=C;++i)
		for(int j=2;j<=i;++j)
			if(i%j==0)
			{
				if(i/j%j==0)
					mu[i]=0;
				else
					mu[i]=-mu[i/j];
				break;
			}
	int ans=0;
	for(int i=1;i<=C;++i)
		if(mu[i])
			for(int j=i;j<=A*B;j+=i)
				F[j]+=f[i]*mu[i];
	for(int i=1;i<=A;++i)
		for(int j=1;j<=B;++j)
			if(gcd(i,j)==1)
				ans+=(A/i)*(B/j)*F[i*j];
	return (ans%mod+mod)%mod;
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d %d",&A,&B,&C);
	printf("%d\n",calc());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
