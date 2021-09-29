#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <ctime>
#include <map>
#include <queue>
#include <set>
using namespace std;
 
const int maxn=100+15;
typedef __float128 ll;
//typedef long long ll;
struct Seg
{
    int a,b,c,w;
}a[maxn];
struct Point
{
    int x,y;
}b[maxn],c[maxn];
int n,m,ans,sum;
bool includ(Seg a,Point b)
{
    return a.a*b.x+a.b*b.y<=a.c;
}
long long A,B,C;
bool cmp(Point a,Point b)
{
    return (ll)(a.x*C-A)*(b.y*C-B)-(ll)(a.y*C-B)*(b.x*C-A)<0;
}
int f[maxn],w[maxn][maxn];
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d%d%d%d",&a[i].a,&a[i].b,&a[i].c,&a[i].w);
    for (int i=1;i<=m;i++) scanf("%d%d",&b[i].x,&b[i].y);
    for (int i=1;i<=m;i++)
    {
        bool boo=false;
        for (int j=1;j<=n;j++)
         if (includ(a[j],b[i])) boo=true;
        if (!boo)
        {
            printf("-1\n");
            return 0;
        }
    }
    ans=100000000;
    for (int i=1;i<=n;i++)
    {
        bool boo=true;
        for (int j=1;j<=m;j++)
         if (!includ(a[i],b[j])) boo=false;
        if (boo) ans=min(ans,a[i].w);
    }
    for (int i=1;i<=n;i++)
     for (int j=i+1;j<=n;j++)
     {
        sum=0;
        for (int k=1;k<=m;k++)
         if (!includ(a[i],b[k]) && !includ(a[j],b[k]))
          c[++sum]=b[k];
        if (sum==0)
        {
            ans=min(ans,a[i].w+a[j].w);
            continue;
        }
        A=(long long)a[j].c*a[i].b-(long long)a[i].c*a[j].b;
        B=(long long)a[i].c*a[j].a-(long long)a[j].c*a[i].a;
        C=(long long)a[j].a*a[i].b-(long long)a[i].a*a[j].b;
        if (C<0) A=-A,B=-B,C=-C;
        sort(c+1,c+sum+1,cmp);
        for (int k=1;k<=sum;k++)
         for (int l=k;l<=sum;l++)
          w[k][l]=100000000;
        for (int k=1;k<=n;k++)
        {
            int las=-1;
            for (int l=1;l<=sum;l++)
             if (includ(a[k],c[l]))
             {
                if (las==-1) las=l;
             }
             else
             {
                if (las!=-1) w[las][l-1]=min(w[las][l-1],a[k].w);
                las=-1;
             }
            if (las!=-1) w[las][sum]=min(w[las][sum],a[k].w);
        }
        for (int len=sum;len>1;len--)
         for (int i=1;i<=sum-len+1;i++)
          w[i][i+len-1-1]=min(w[i][i+len-1-1],w[i][i+len-1]),
          w[i+1][i+len-1]=min(w[i+1][i+len-1],w[i][i+len-1]);
        for (int k=1;k<=sum;k++)
        {
            f[k]=w[1][k];
            for (int l=1;l<k;l++) f[k]=min(f[k],f[l]+w[l+1][k]);
        }
        ans=min(ans,a[i].w+a[j].w+f[sum]);
     }
    printf("%d\n",ans);
    return 0;
}
