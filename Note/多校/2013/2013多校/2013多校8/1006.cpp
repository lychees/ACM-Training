/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/15 12:34:55
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£8\1006.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MAXN = 1010;
char str1[MAXN],str2[MAXN],str3[MAXN];
int dp1[MAXN][MAXN];
int dp2[MAXN][MAXN];
int dp[MAXN][MAXN];
int dp3[MAXN][MAXN];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
	scanf("%d",&T);
	int iCase = 0;
	while(T--)
	{
		iCase++;
		scanf("%s%s%s",str1,str2,str3);
		int len1 = strlen(str1);
		int len2 = strlen(str2);
		int len3 = strlen(str3);
		for(int i = 0; i <= len1;i++)
			dp[i][0] = 0;
		for(int i = 0;i <= len2;i++)
			dp[0][i] = 0;
		for(int i = 1;i <= len1;i++)
			for(int j = 1;j <= len2;j++)
			{
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
				if(str1[i-1] == str2[j-1])
					dp[i][j] = max(dp[i][j],dp[i-1][j-1]+1);
			}
		for(int i = 0; i <= len1;i++)
			dp3[i][0] = 0;
		for(int i = 0;i <= len2;i++)
			dp3[0][i] = 0;
		for(int i = 1;i <= len1;i++)
			for(int j = 1;j <= len2;j++)
			{
				dp3[i][j] = max(dp3[i-1][j],dp3[i][j-1]);
				if(str1[len1-i] == str2[len2-j])
					dp3[i][j] = max(dp3[i][j],dp3[i-1][j-1]+1);
			}
		for(int i = 1;i <= len3;i++)
			dp1[0][i] = -1;
		for(int i = 0;i <= len1;i++)
			dp1[i][0] = i;
		for(int i = 1;i <= len1;i++)
			for(int j = 1;j <= len3;j++)
			{
				if(str1[i-1] == str3[j-1])
					dp1[i][j] = dp1[i-1][j-1];
				else dp1[i][j] = dp1[i-1][j];
			}
		for(int i = 1;i <= len3;i++)
			dp2[0][i] = -1;
		for(int i = 0;i <= len2;i++)
			dp2[i][0] = i;
		for(int i = 1;i <= len2;i++)
			for(int j = 1;j <= len3;j++)
			{
				if(str2[i-1] == str3[j-1])
					dp2[i][j] = dp2[i-1][j-1];
				else dp2[i][j] = dp2[i-1][j];
			}
		int ans = 0;
		for(int i = 0;i <= len1;i++)
			for(int j = 0;j <= len2;j++)
			{
				int t1 = dp1[len1-i][len3];
				int t2 = dp2[len2-j][len3];
				if(t1 == -1 || t2 == -1)continue;
				ans = max(ans,dp3[i][j]+dp[t1][t2]);
			}
		printf("Case #%d: %d\n",iCase,ans+len3);
	}
    return 0;
}
