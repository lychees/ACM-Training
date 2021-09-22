/*
 *  Author:kuangbin
 *  1007.cpp
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
const int MAXN = 100010;
int n;

int lowbit(int x)
{
    return x&(-x);
}
int c[MAXN];
void add(int i,int val)
{
    while(i <= n)
    {
        c[i] += val;
        i += lowbit(i);
    }
}
int sum(int i)
{
    int s = 0;
    while(i > 0)
    {
        s += c[i];
        i -= lowbit(i);
    }
    return s;
}
int a[MAXN];
int num[MAXN];

int ans[MAXN];
struct Node
{
    int l,r;
    int index;
}node[MAXN];
bool cmp(Node a,Node b)
{
    return a.l < b.l;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(c,0,sizeof(c));
        for(int i = 1;i <= n;i++)
        {
            scanf("%d",&a[i]);
            num[a[i]]=i;
        }
        num[0] = n+10;
        num[n+1] = n+10;
        for(int i = 1;i <= n;i++)
        {
            if(i < num[a[i]-1] && i < num[a[i]+1])
                add(i,1);
            else if(i > num[a[i]-1] && i > num[a[i]+1])
                add(i,-1);
        }
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d",&node[i].l,&node[i].r);
            node[i].index = i;
        }
        sort(node,node+m,cmp);
        int i = 1;
        int j = 0;
        while(j < m)
        {
            while(i <= n && i < node[j].l)
            {
                if(i > num[a[i]-1] && i > num[a[i]+1])
                    add(i,-1);
                else if(i < num[a[i]-1] && i < num[a[i]+1])
                {
                    int Min = min(num[a[i]-1],num[a[i]+1]);
                    int Max = max(num[a[i]-1],num[a[i]+1]);
                    add(i,-1);
                    add(Min,1);
                    add(Max,1);
                }
                else if(i < num[a[i]-1])
                {
                    add(i,-1);
                    add(num[a[i]-1],1);
                }
                else
                {
                    add(i,-1);
                    add(num[a[i]+1],1);
                }
                i++;
            }
            while( j < m && node[j].l <= i)
            {
                ans[node[j].index]= sum(node[j].r);
                j++;
            }
        }
        for(int i = 0;i < m;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
