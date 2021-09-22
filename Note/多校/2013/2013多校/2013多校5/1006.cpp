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
int a[MAXN];
int b[MAXN];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(scanf("%d%d",&n,&m) == 2)
    {
        memset(b,-1,sizeof(b));
        b[0] = 0;
        int ans = 0;
        int sum = 0;
        for(int i = 1;i <= n;i++)
        {
            scanf("%d",&a[i]);
            sum += a[i];
            sum %= m;
            sum = (sum+m)%m;
            if(b[sum]!=-1)
            {
                ans = max(ans,i-b[sum]);
            }
            if(b[sum] == -1)
                b[sum] = i;
        }
        printf("%d\n",ans);
    }
    return 0;
}
