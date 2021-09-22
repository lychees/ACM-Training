/*
 * Author:  kuangbin
 * Created Time:  2013/8/8 11:54:23
 * File Name: 1010.cpp
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
const int MAXN = 100010;
int sg[MAXN];
bool vis[MAXN];
int mex(int x)
{

    if(sg[x]!=-1)return sg[x];
    if(x == 0)return sg[x] = 0;
    if(x == 1)return sg[x] = 0;
    if(x == 2)return sg[x] = 1;
    if(x == 3)return sg[x] = 1;
    memset(vis,false,sizeof(vis));
    for(int i = 0;i < x-1;i++)
        vis[mex(i)^mex(x-i-2)] = true;
    for(int i = 0;;i++)
        if(!vis[i])
            return sg[x] = i;
}

int SG(int x)
{
    if(x <= 200)return sg[x];
    else
    {
        x %= 34;
        x += 4*34;
        return sg[x];
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(sg,-1,sizeof(sg));
    for(int i = 0;i <= 1000;i++)
    {
        sg[i] = mex(i);
    }
    int T;
    int n;
    int a;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int sum = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%d",&a);
            sum ^= SG(a);
        }
        if(sum)printf("Carol\n");
        else printf("Dave\n");
    }
    return 0;
}

