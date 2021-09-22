/*
 * Author:  kuangbin
 * Created Time:  2013/8/8 11:54:08
 * File Name: 1008.cpp
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <time.h>
using namespace std;
char str[1000010];
const int MAXN = 3000010;
bool dp[MAXN];
bool vis[MAXN];
void init()
{
    memset(dp,false,sizeof(dp));
    memset(vis,false,sizeof(vis));
    dp[1] = true;
    queue<int>q;
    q.push(1);
    vis[1] = true;
    while(!q.empty())
    {
        int tmp = q.front();
        dp[tmp] = true;
        q.pop();
        if(tmp == 0){dp[0] = true;vis[0] = true;continue;}
        if(tmp >= 6 && !vis[tmp-6])
        {
            q.push(tmp-6);
            vis[tmp-6] = true;
        }
        tmp *= 2;
        while(tmp < MAXN)
        {
            if(vis[tmp])break;
            dp[tmp] = true;
            if(tmp >= 6 && !vis[tmp-6])
            {
                q.push(tmp-6);
                vis[tmp-6] = true;
            }
            tmp *= 2;
        }
    }
}


int main()
{
    int T;
    init();
    scanf("%d",&T);
    while(T--)
    {
        bool flag = true;
        scanf("%s",str);
        int len = strlen(str);
        if(str[0]!='M')
        {
            printf("No\n");
            continue;
        }
        int cnt = 0;
        for(int i = 1;i < len;i++)
        {
            if(str[i]=='M')
            {
                flag = false;
                break;
            }
            if(str[i] =='I')cnt++;
            else cnt+= 3;
        }
        if(!flag)
        {
            printf("No\n");
            continue;
        }
        if(cnt == 1)
        {
            printf("Yes\n");
            continue;
        }
        if(cnt%2 == 1 || cnt%6 == 0)printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}

