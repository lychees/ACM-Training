#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 2010
using namespace std;
char str[maxn];
int dp[2][maxn][4][4][4];
void update(int &a,int b)
{
	if(a>b)
		a=b;
}
int Dp()
{
	int n=strlen(str+1),cur=0;
	for(int i=0;i<=1;++i)
		for(int j=0;j<=n;++j)
			for(int a=0;a<=3;++a)
				for(int b=0;b<=3;++b)
					for(int c=0;c<=3;++c)
						dp[i][j][a][b][c]=1<<30;
	dp[cur][0][0][0][0]=0;
	for(int i=0;i<=n;++i,cur^=1)
		for(int j=i;j>=0;--j)
			for(int a=0;a<=3;++a)
				for(int b=0;b<=3;++b)
					for(int c=0;c<=3;++c)
						if(dp[cur][j][a][b][c]!=1<<30)
						{
							int x=str[i+1]-'A'+1,&val=dp[cur][j][a][b][c],newlen,cost;
							if(j!=0)
								update(dp[cur][j-1][j>1?a:0][j>2?b:0][j>3?c:0],val+1);
							if(i==n)
								continue;
							if(x!=a&&x!=b&&x!=c)
								update(dp[cur^1][j+1][j==0?x:a][j==1?x:b][j==2?x:c],val+2);
							else
							{
								bool mark=false;
								if(x==a)
									cost=(j-1)%3,mark=j>=3&&j%3==0;
								else if(x==b)
									cost=(j-2)%3,mark=j>=3&&j%3==1;
								else
									cost=(j-3)%3,mark=j>=3&&j%3==2;
								newlen=j-cost;
								update(dp[cur^1][newlen][newlen>=1?a:0][newlen>=2?b:0][newlen>=3?c:0],val+cost+1);
								if(mark)
									update(dp[cur^1][j+1][a][b][c],val+2);
							}
							val=1<<30;
						}
	return dp[cur^1][0][0][0][0];
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		scanf("%s",str+1);
		printf("Case #%d: %d\n",++C,Dp());
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
