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
char str[20];

int dp[1<<17];
int a[1<<17];
int cnt;
bool b[1<<17];
int n;
char s[20];
bool check(int x)
{
    int len = 0;
    for(int i = 0;i < n;i++)
        if(x &(1<<i) )
           s[len++] = str[i];
    for(int i = 0;i < len;i++)
        if(s[i]!=s[len-1-i])
           return false;
    return true;
}
int used[1<<17];
int bfs()
{
    queue<int>q;
    q.push(0);
    memset(used,-1,sizeof(used));
    used[0] = 0;
    while(!q.empty())
    {
        int tmp = q.front();
        q.pop();
        for(int i = 0;i <cnt;i++)
        {
            if(tmp & a[i])continue;
            if(used[tmp|a[i]]!=-1)continue;
            if((tmp|a[i])==((1<<n)-1))return used[tmp]+1;
            used[tmp|a[i]]=used[tmp]+1;
            q.push(tmp|a[i]);
        }
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",str);
        n = strlen(str);
        cnt = 0;
        for(int i = 1;i < (1<<n);i++)
        {
            b[i]=check(i);
            if(b[i])
                a[cnt++] = i;
        }
        printf("%d\n",bfs());
    }
    return 0;
}
