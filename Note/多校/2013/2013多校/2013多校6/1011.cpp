/*
 * Author:  kuangbin
 * File Name: 1011.cpp
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 2020;
int a[MAXN];
int s[MAXN];
char ans[MAXN];

bool flag ;
int n;
void dfs(int cur,int t1,int t2)
{
    if(flag)return;
    if(t1 > n/2 || t2 > n/2)return;
    if(cur == n)
    {
        flag = true;
        return;
    }
    s[t1] = a[cur];
    ans[cur] = '0';
    dfs(cur+1,t1+1,t2);
    if(flag)return;
    if(s[t2] == a[cur])
    {
        ans[cur] = '1';
        dfs(cur+1,t1,t2+1);
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0;i < n;i++)
            scanf("%d",&a[i]);
        flag = false;
        dfs(0,0,0);
        for(int i = 0;i < n;i++)printf("%c",ans[i]);
        printf("\n");
    }
    return 0;
}

