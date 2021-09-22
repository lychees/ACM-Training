/*
 *  Author:kuangbin
 *  1010.cpp
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

const int MAXN = 50010;
int c[MAXN];
int n;
int lowbit(int x)
{
    return x&(-x);
}
void add(int i,int val)
{
    while(i <= n)
    {
        c[i] = max(c[i],val);
        i += lowbit(i);
    }
}
int Max(int i)
{
    int s = 0;
    while(i > 0)
    {
        s = max(s,c[i]);
        i -= lowbit(i);
    }
    return s;
}

int a[MAXN];
int b[MAXN];
int ans[MAXN];

struct Node
{
    int l,r;
    int index;
}node[MAXN];

bool cmp(Node a,Node b)
{
    return a.l > b.l;
}
int input()
{
    char ch;
    int ret;
    ch = getchar();
    while(ch < '0'|| ch>'9')ch= getchar();
    ret = 0;
    while(ch >= '0' && ch <='9')
    {
        ret*=10;
        ret += ch-'0';
        ch = getchar();
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int m;
    int l,r;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d",&node[i].l,&node[i].r);
            node[i].index = i;
        }
        sort(node,node+m,cmp);
        int i = n;
        int j = 0;
        memset(b,0,sizeof(a));
        memset(c,0,sizeof(c));
        while(j < m)
        {
            while(i > 0 && i>= node[j].l)
            {
                for(int k =1;k*k <= a[i];k++)
                {
                    if(a[i]%k == 0)
                    {
                        if(b[k]!=0)
                        {
                            add(b[k],k);
                        }

                        b[k] = i;
                        if(k != a[i]/k)
                        {
                            if(b[a[i]/k]!=0)
                            {
                                add(b[a[i]/k],a[i]/k);
                            }

                            b[a[i]/k]=i;
                        }
                    }
                }
                i--;
            }
            while(j < m && node[j].l > i)
            {
                ans[node[j].index]=Max(node[j].r);
                j++;
            }
        }
        for(int i = 0;i < m;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
