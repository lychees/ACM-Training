#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

#define _int64 long long
#define jin 1000000

struct ty
{
    int w;
    _int64 a[1000];
};

pair<ty,ty> a[200];

bool pcmp(pair<ty,ty> a,pair<ty,ty> b)
{
    return a.first.a[0]*b.second.a[0]<b.first.a[0]*a.second.a[0];
}

void jia(ty &x,ty y)
{
    int i;
    if (y.w>x.w) x.w=y.w;
    for (i=0;i<y.w;i++)
        x.a[i]+=y.a[i];
    for (i=0;i+1<x.w;i++)
        if (x.a[i]>=jin)
        {
            x.a[i]-=jin;
            x.a[i+1]++;
        }
    while (x.a[x.w-1]>=jin)
    {
        x.a[x.w]++;
        x.a[x.w-1]-=jin;
        x.w++;
    }
}

void chen(ty &x,ty y)
{
    int i,j;
    ty z;
    memset(z.a,0,sizeof(z.a));
    z.w=x.w+y.w;
    for (i=0;i<x.w;i++)
        for (j=0;j<y.w;j++)
            z.a[i+j]+=x.a[i]*y.a[j];
    for (i=0;i+1<z.w;i++)
    {
        z.a[i+1]+=z.a[i]/jin;
        z.a[i]%=jin;
    }
    while ((z.w>1)&&(z.a[z.w-1]==0)) z.w--;
    x=z;
}

int dayudengyu(ty x,ty y)
{
    int i;
    if (x.w>y.w) return 1;
    if (x.w<y.w) return 0;
    for (i=x.w-1;i>=0;i--)
    {
        if (x.a[i]>y.a[i]) return 1;
        if (x.a[i]<y.a[i]) return 0;
    }
    return 1;
}

void outputh(ty x)
{
    int i;
    printf("%lld",x.a[x.w-1]);
    for (i=x.w-2;i>=0;i--)
    {
        printf("%06lld",x.a[i]);
    }
    printf("\n");
}

int main()
{
    int i,l,t,n;
    double x,y;
    pair<ty,ty> sum;
    scanf("%d",&t);
    for (l=0;l<t;l++)
    {
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
            scanf("%lf:%lf",&x,&y);
            //cout<<x<<" "<<y<<endl;
            a[i].first.w=1;
            memset(a[i].first.a,0,sizeof(a[i].first.a));
            a[i].first.a[0]=x*1000+0.5;
            
            a[i].second.w=1;
            memset(a[i].second.a,0,sizeof(a[i].second.a));
            a[i].second.a[0]=y*1000+0.5;
            jia(a[i].second,a[i].first);
        }
        sort(a,a+n,pcmp);
        sum.first.w=1;
        memset(sum.first.a,0,sizeof(sum.first.a));
        sum.second.w=1;
        memset(sum.second.a,0,sizeof(sum.second.a));
        sum.second.a[0]=1;
        for (i=0;i<n;i++)
        {
            //outputh(a[i].first);
            //outputh(a[i].second);
            chen(sum.first,a[i].second);
            chen(a[i].first,sum.second);
            jia(sum.first,a[i].first);
            chen(sum.second,a[i].second);
            //outputh(sum.first);
            //outputh(sum.second);
            if (dayudengyu(sum.first,sum.second)==1) break;
        }
        printf("Case #%d: %d\n",l+1,i);
    }
}