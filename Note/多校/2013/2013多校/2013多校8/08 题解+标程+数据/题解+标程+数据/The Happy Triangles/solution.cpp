#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <cmath>
#define Mod (1000000007LL)
#define eps (1e-8)
#define Pi (acos(-1.0))
using namespace std;
double R,ans;
int n;
struct Node
{
    double a,b,c,h,s;
}node[100100];
bool check(double x)
{
    double s=0;
    for(int i=1;i<=n;i++)
    {
        //printf("%.3f %.3f %d\n",x,node[i].h,i);
        if(x>node[i].h) continue;
        else
        {
            s+=node[i].a*(1.0-x/node[i].h);
            //printf("%.4f %.4f %.4f %.4f\n",node[i].a,node[i].h,x,s);
        }
    }
   // printf("%.2f %.2f %.2f\n",x,s,R);
    if(s+eps<R) return false;
    else return true;
}
void work(double x)
{
    ans=x*R;
    for(int i=1;i<=n;i++)
    {
        if(x>node[i].h) continue;
        else ans+=node[i].s*(1.0-x/node[i].h)*(1.0-x/node[i].h);
    }
}
int main()
{
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int T;
    scanf("%d",&T);
    int id = 0;
    while(T--)
    {
        scanf("%d%lf",&n,&R);
        double L,r,mid;
        double s,p;
        L=r=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf",&node[i].a,&node[i].b,&node[i].c);
            p=(node[i].a+node[i].b+node[i].c)/2.0;
            s=p*(p-node[i].a)*(p-node[i].b)*(p-node[i].c);
            s=sqrt(s);
            node[i].h=2.0*s/node[i].a;
            node[i].s=s;
            //printf("%.3f %.3f\n",node[i].s,node[i].h);
            r=max(r,node[i].h);
        }
      //  printf("%.2f %.2f\n",L,r);
        int tt = 60;
        //for(;L+eps<r;)
        while (tt--)
        {
            mid=(L+r)/2.0;
            if(check(mid)) L=mid;
            else r=mid;
        }
        work(L);
        id++;
        //printf("%.6f  %.6f\n",L,ans);
        printf("Case #%d: %.3f\n",id,ans);
    }
    return 0;
}
