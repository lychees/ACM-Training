#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 310
using namespace std;
short up[maxn][maxn][maxn],down[maxn][maxn][maxn];
int can[maxn][maxn],n;
char map[maxn][maxn];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",map[i]+1);
		can[i][n+1]=n+1;
		for(int j=n;j>=1;--j)
			can[i][j]=map[i][j]=='*'?j:can[i][j+1];
	}
}
void Dp()
{
	int ans=-1;
	for(int i=1;i<=n;++i)
		for(int j=i+2;j<=n;++j)
		{
			int num=-1;
			for(int k=1;k<=n;++k)
			{
				if(map[k][i]=='*'||map[k][j]=='*')
					num=-1;
				else if(can[k][i]>j)
				{
					if(~num)
						up[k][i][j]=num;
					else
						num=up[k][i][j]=k;
				}
			}
			num=-1;
			for(int k=n;k>=1;--k)
			{
				if(map[k][i]=='*'||map[k][j]=='*')
					num=-1;
				else if(can[k][i]>j)
				{
					if(~num)
						down[k][i][j]=num;
					else
						num=down[k][i][j]=k;
				}
			}
		}
	static int maxv[maxn][maxn];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			maxv[j][n]=maxv[j-1][n];
			if(down[i][j][n]>=i+2)
				maxv[j][n]=max(maxv[j][n],(int)(down[i][j][n]-i-1)*(n-j-1));
			for(int k=n;k>=j+2;--k)
			{
				maxv[j][k]=max(maxv[j-1][k],maxv[j][k+1]);
				if(down[i][j][k]&&down[i][j][k]>=i+2)
					maxv[j][k]=max(maxv[j][k],(int)(down[i][j][k]-i-1)*(k-j-1));
			}
			for(int k=j+2;k<=n;++k)
				if(up[i][j][k]&&up[i][j][k]<=i-2&&maxv[j][k])
					ans=max(ans,maxv[j][k]*(i-up[i][j][k]-1)*(k-j-1));
		}
	printf("%d\n",ans);
}
int main()
{
	read();
	Dp();
	return 0;
}
