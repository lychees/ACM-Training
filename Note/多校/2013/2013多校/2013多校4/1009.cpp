/*
 *  Author:kuangbin
 *  1009.cpp
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
const int INF = 0x3f3f3f3f;
int g[20][20];

int dp[1<<18][18];


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n,m;
    int u,v,w;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 0;i < n;i++)
            for(int j = 0;j < n;j++)
                g[i][j] = INF;
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            u--;
            v--;
            g[u][v] = g[v][u] = min(w,g[u][v]);
        }
        for(int i = 0;i < (1<<n);i++)
            for(int j = 0;j < n;j++)
              dp[i][j] = INF;
        dp[1][0] =

    }
    return 0;
}
