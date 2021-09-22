/*
 *  Author:kuangbin
 *  1001.cpp
 */

#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <math.h>
using namespace std;
const int MOD = 10007;
int dp[1100][1100];
int n;
char str[1100];
int solve(int l,int r)
{
    if(l > r)return 0;
    if(l == r)return dp[l][r] = 1;
    if(dp[l][r] != -1)return dp[l][r];
    if(r == l+1)
    {
        if(str[l] == str[r])
            return dp[l][r] = 3;
        else return dp[l][r] = 2;
    }
    dp[l][r] = solve(l+1,r)+solve(l,r-1);
    if(dp[l][r] >= MOD)dp[l][r]-=MOD;
    if(str[l]==str[r])
    {
        dp[l][r] ++;
        if(dp[l][r] >= MOD)dp[l][r]-=MOD;
    }
    else
    {
        dp[l][r] -= solve(l+1,r-1);
        if(dp[l][r]<0)dp[l][r] += MOD;
    }
    return dp[l][r];
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int iCase = 0;
    scanf("%d",&T);
    while(T--)
    {
        iCase++;
        memset(dp,-1,sizeof(dp));
        scanf("%s",str);
        n = strlen(str);
        printf("Case %d: %d\n",iCase,solve(0,n-1));
    }
    return 0;
}
