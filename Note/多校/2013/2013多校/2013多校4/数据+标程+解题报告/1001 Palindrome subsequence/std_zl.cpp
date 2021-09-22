#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
typedef long long lld;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define mod 10007
char str[1010];
int dp[1010][1010];
int dfs(int x,int y)
{
	if(dp[x][y] != -1)
		return dp[x][y];
	if(x > y)
		return 0;
	dp[x][y]=0;
	dp[x][y]+=dfs(x+1,y);
	dp[x][y]+=dfs(x,y-1);
	dp[x][y]-=dfs(x+1,y-1);
	if(str[x] == str[y])
	{
		dp[x][y]++;
		dp[x][y]+=dfs(x+1,y-1);
	}
	dp[x][y]=(dp[x][y]%mod+mod)%mod;
	return dp[x][y];
}
int main()
{
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		scanf("%s",str);
		int n=strlen(str);
		memset(dp,-1,sizeof(dp));
		printf("Case %d: %d\n",cc,dfs(0,n-1));
	}
	return 0;
}
