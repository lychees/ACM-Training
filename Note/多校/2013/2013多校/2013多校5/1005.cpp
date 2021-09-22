#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
using namespace std;
const int MAXN = 100010;

bool cmp(long long a,long long b)
{
    return a > b;
}
long long val[MAXN];
int main()
{
    int n,m;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i = 1;i <= n;i++)
        {
            scanf("%I64d",&val[i]);
            val[i] *= 2;
        }
        int u,v,w;
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            val[u] += w;
            val[v] += w;
        }
        long long ans = 0;
        sort(val+1,val+n+1,cmp);
        for(int i = 1;i <= n;i++)
        {
            if(i%2)ans += val[i];
            else ans -= val[i];
        }
        printf("%I64d\n",ans/2);
    }
    return 0;
}
