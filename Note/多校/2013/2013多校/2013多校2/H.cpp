#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
using namespace std;
const int MAXN = 330;
int a[MAXN][MAXN];
int n,m;
int calc(int x,int y,int tt)//tt=0奇数，tt=1偶数
{
    int ans;
    int x1,y1,x2,y2;//两个角坐标
    if(tt == 0)
    {
        ans = 1;
        x1 = x; y1 = y;
        x2 = x; y2 = y;
    }
    else
    {
        if(x+1>=n || y+1>=m)return 0;
        ans = 2;
        x1 = x;y1 = y;
        x2 = x+1;y2 = y+1;
        if(a[x1][y1]!=a[x2][y1]||a[x1][y1]!=a[x2][y1])
        return 0;
        if(a[x2][y2]!=a[x2][y1]||a[x2][y2]!=a[x2][y1])
        return 0;
    }
    while(1)
    {
        x1--;y1--;
        x2++;y2++;
        if(x1 < 0 || y1 < 0 || x2 >= n || y2 >= m)
            return ans;
        for(int i = x1;i <= x2;i++)
            if(a[i][y1]!=a[x2-i+x1][y1])
              return ans;
        for(int i = x1;i <= x2;i++)
            if(a[i][y2]!=a[x2-i+x1][y2])
              return ans;
        for(int i = y1;i <= y2;i++)
            if(a[x1][i]!=a[x1][y2-i+y1])
              return ans;
        for(int i = y1;i <= y2;i++)
            if(a[x2][i]!=a[x2][y2-i+y1])
              return ans;
        for(int i = x1;i <= x2;i++)
            if(a[i][y1]!=a[i][y2])
              return ans;
        for(int i = y1;i <= y2;i++)
            if(a[x1][i]!=a[x2][i])
               return ans;
        ans += 2;
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;

    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 0; i < n;i++)
            for(int j = 0;j < m;j++)
                scanf("%d",&a[i][j]);
        int ans = 0;
        for(int i = 0;i < n;i++)
            for(int j = 0;j < m;j++)
        {
            ans = max(ans,calc(i,j,0));
            ans = max(ans,calc(i,j,1));
        }
        printf("%d\n",ans);

    }
    return 0;


    return 0;
}







