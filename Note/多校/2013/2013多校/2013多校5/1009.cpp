#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
const int MOD = 1e9+7;
int dp[100010];
void init()
{
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    for(int i = 1;i <= 100000;i++)
    {
        for(int j = 1, r = 1; i - (3 * j * j - j) / 2 >= 0; j++, r *= -1)
        {
            dp[i] += dp[i -(3 * j * j - j) / 2] * r;
            dp[i] %= MOD;
            dp[i] = (dp[i]+MOD)%MOD;
            if( i - (3 * j * j + j) / 2 >= 0 )
            {
                dp[i] += dp[i - (3 * j * j + j) / 2] * r;
                dp[i] %= MOD;
                dp[i] = (dp[i]+MOD)%MOD;
            }

        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n;
    init();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d\n",dp[n]);
    }
    return 0;
}
