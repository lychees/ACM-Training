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

const int INF = 0x3f3f3f3f;

int dp[55][55][55][55];
int b[55][55];
int sumb[55][55];
int w[55][55];
int sumw[55][55];

struct Node
{
    int r,c;
    int t;
    int reword;
    Node(int _r = 0,int _c=0,int _reword = 0,int _t = 0)
    {
        r = _r;
        c = _c;
        reword = _reword;
        t = _t;
    }
};
vector<Node>vec[55][55];

int n,m;

int solve(int r1,int c1,int r2,int c2)
{
    if(r1 > r2 || c1 > c2)return 0;
    if(dp[r1][c1][r2][c2]!=-INF)
        return dp[r1][c1][r2][c2];
    int tmp ;
    tmp = solve(r1,c1,r2,c2)
    dp[r1][c1][r2][c2] = max(dp[r1][c1][r2][c2],)
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int r;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&r);
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
              scanf("%d",&b[i][j]);
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
              scanf("%d",&w[i][j]);
        memset(sumb,0,sizeof(sumb));
        memset(sumw,0,sizeof(sumw));
        for(int i = 1;i <= n;i++)
            for(int j = 1;j<= m;j++)
        {
            sumb[i][j] = sumb[i-1][j]+sumb[i][j-1]-sumb[i-1][j-1]+b[i][j];
            sumw[i][j] = sumw[i-1][j]+sumw[i][j-1]-sumw[i-1][j-1]+w[i][j];
        }

        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
               for(int x = 1;x <= n;x++)
                  for(int y = 1;y <= m;y++)
                     dp[i][j][x][y] = -INF;
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
              vec[i][j].clear();
        int r1,c1,r2,c2,t,s;
        while(r--)
        {
            scanf("%d%d%d%d%d%d",&r1,&c1,&r2,&c2,&t,&s);
            vec[r2][c2].push_back(Node(r1,c1,s,t));
        }

    }
    return 0;
}
