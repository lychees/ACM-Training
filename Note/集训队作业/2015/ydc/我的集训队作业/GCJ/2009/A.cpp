#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 60
using namespace std;
typedef long double ld;
typedef long long LL;
int n,m,d[maxn][maxn];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&d[i][0]);
		d[i][1]=1;
		for(int j=2;j<=d[i][0];++j)
			scanf("%d",&d[i][j]);
	}
}
void work()
{
	LL K=0,fenzi=0,fenmu=(LL)n*n;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=d[i][0];++j)
			for(int k=1;k<=m;++k)
				for(int l=1;l<=d[k][0];++l)
					if(d[i][j]<=n&&d[k][l]<=n)
					{
						if(i==k&&j==l)
						{
							fenzi+=(LL)n*(n-d[i][j]+1);
							if(fenzi>=fenmu)
								fenzi-=fenmu,++K;
						}
						if(i!=k)
						{
							fenzi+=n-max(d[i][j],d[k][l])+1;
							if(fenzi>=fenmu)
								fenzi-=fenmu,++K;
						}
					}
	LL d=__gcd(fenzi,fenmu);
	fenzi/=d,fenmu/=d;
	printf("%I64d+%I64d/%I64d\n",K,fenzi,fenmu);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
