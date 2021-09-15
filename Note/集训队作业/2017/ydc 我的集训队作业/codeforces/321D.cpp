#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 40
using namespace std;
int n,x,map[maxn][maxn],sig[]={1,-1};
void read()
{
	scanf("%d",&n);
	x=(n+1)>>1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&map[i][j]);
}
void work()
{
	int ans=-1<<30;
	for(int S=0;S<(1<<x);++S)
	{
		int sum=0,vxx=S>>(x-1)&1;
		for(int i=1;i<=x;++i)
		{
			int vix=S>>(i-1)&1;
			sum+=map[i][x]*sig[vix];
			sum+=map[i+x][x]*sig[vix^vxx];
		}
		for(int j=1;j<x;++j)
		{
			int v1=0;
			for(int tD=0;tD<=1;++tD)
			{
				int v=map[x][j]*sig[tD]+map[x][j+x]*sig[tD^vxx];
				for(int i=1;i<x;++i)
				{
					int tR=S>>(i-1)&1;
					v+=abs(map[i][j]+map[i][j+x]*sig[tR]+map[i+x][j]*sig[tD]+map[i+x][j+x]*sig[tR^tD^vxx]);
				}
				v1=max(v1,v);
			}
			sum+=v1;
		}
		ans=max(ans,sum);
	}
	printf("%d\n",ans);
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
