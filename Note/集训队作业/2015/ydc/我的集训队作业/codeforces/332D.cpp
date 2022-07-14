#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 2010
using namespace std;
typedef long long LL;
int n,m,val[maxn][maxn],deg[maxn];
double f[maxn];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
		{
			scanf("%d",&val[i][j]);
			val[j][i]=val[i][j];
			if(val[i][j]!=-1)
				++deg[i],++deg[j];
		}
	f[n]=1.0*m/n;
	for(int i=n-1;i>=m;--i)
		f[i]=f[i+1]/i*(i-m+1);
}
LL work()
{
	double ans=0;
	for(int i=1;i<=n;++i)
		if(deg[i]>=m)
			for(int j=1;j<=n;++j)
				if(val[i][j]!=-1&&i!=j)
					ans+=val[i][j]*f[deg[i]];
	return (LL)(ans+1e-3);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%I64d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
