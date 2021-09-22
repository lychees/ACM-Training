#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

char str[30];
char s[30];
int n;
bool b[1<<17];
bool check(int x)
{
    int len = 0;
    for(int i = 0;i < n;i++)
        if(x & (1<<i))
            s[len++] = str[i];
    for(int i = 0;i < len;i++)
        if(s[i] != s[len-1-i])
            return false;
    return true;
}
int dp[1<<17];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",str);
        n = strlen(str);
        for(int i = 1;i < (1<<n);i++)
        {
            dp[i] = n;
            b[i] = check(i);
        }
        dp[0] = 0;
        for(int i = 1;i < (1<<n);i++)
            for(int j = i;j;j=(j-1)&i )
                if(b[j])
                {
                    dp[i] = min(dp[i],dp[i^j]+1);
                }
        printf("%d\n",dp[(1<<n)-1]);
    }
    return 0;
}

