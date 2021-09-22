/*
 *  Author:kuangbin
 *  1008.cpp
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
int dp[10000];
void init()
{
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3;i < 10000;i++)
        dp[i] = (dp[i-1] + dp[i-2])%MOD;
}

char str[20000];

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    int iCase = 0;
    init();
    while(T--)
    {
        iCase ++;
        scanf("%s",str);
        int ans = 1;
        int len = strlen(str);
        for(int i = 0; i < len;i++)
        {
            if(str[i] == 'h')
            {
                int cnt = 0;
                for(int j = i ; j+1 <len;j+=2)
                {
                    if(str[j]!='h'||str[j+1]!='e')break;
                    cnt++;
                }
                ans = ans*dp[cnt]%MOD;
                if(cnt > 0)
                {
                    i += cnt*2;
                    i--;
                }
            }
        }
        printf("Case %d: %d\n",iCase,ans);
    }
    return 0;
}
