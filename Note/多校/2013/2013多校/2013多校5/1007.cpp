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
int a[500];
char op[500];
double p[2];
double b[500];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    int iCase = 0;
    while(scanf("%d",&n) == 1)
    {
        iCase ++;
        for(int i = 0;i <= n;i++)
            scanf("%d",&a[i]);
        gets(op);
        gets(op);
        for(int i = 1;i <= n;i++)
            scanf("%lf",&b[i]);
        double ans = 0;
        for(int k = 0;k <= 20;k++)
        {
            if(a[0] & (1<<k))
            {
                p[0] = 0;
                p[1] = 1;
            }
            else
            {
                p[0] = 1;
                p[1] = 0;
            }
            for(int i = 1;i <= n;i++)
            {
                if(op[2*(i-1)]=='&')
                {
                    if((a[i] & (1<<k))==0)
                    {
                        p[1] = (b[i])*p[1];
                        p[0] = 1-p[1];
                    }
                }
                else if(op[2*(i-1)]=='|')
                {
                    if(a[i]&(1<<k))
                    {
                        p[0] = b[i]*p[0];
                        p[1] = 1-p[0];
                    }
                }
                else
                {
                    if(a[i]&(1<<k))
                    {
                        double p0 = b[i]*p[0] + (1-b[i])*p[1];
                        double p1 = 1-p0;
                        p[0] = p0;
                        p[1] = p1;
                    }
                    else
                    {
                        p[0] = b[i]*p[0] + (1-b[i])*p[0];
                        p[1] = 1-p[0];
                    }
                }

            }
            ans += p[1]*(1<<k);
        }
        printf("Case %d:\n%.6lf\n",iCase,ans);
    }
    return 0;
}
