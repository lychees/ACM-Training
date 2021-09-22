#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define MAXN 1010
#define INF 1000000000
#define MP(x,y) make_pair((x),(y))
#define FI first
#define SE second

struct _node
{
    int q,n,p,m;
}no[MAXN];
int num[10],tmpnum[10],top;
int per[MAXN],sum[MAXN];

void mfind(__int64 &tmon,int h,int tim,int now)
{
    int tt;
    __int64 tmp=0;
    if(now>tim) 
        return;
    if(no[h].m==0)
        tmp=no[h].p;
    else    
        tmp=(__int64)no[h].p*(1+(tim-now)/no[h].m);
    while(top>0&&tmon>0)
    {
        if(top*tmp<=no[h].q)
        {
            top=-1;
            break;
        }
        tt=min((__int64)tmpnum[top],tmon/no[h].q);
        tmon-=tt*no[h].q;
        tmpnum[top]-=tt;
        per[now]+=tt;
        sum[now]+=tt*top;
        if(tmpnum[top]==0)  
            --top;
        else    
            break;
    }
    return ;
}
__int64 cal(int h,int tim,__int64 mon)
{
    memset(per,0,sizeof(per));
    memset(sum,0,sizeof(sum));
    memcpy(tmpnum,num,sizeof(num));
    top=9;
    mfind(mon,h,tim,no[h].n);
    for(int i=1;i<=tim;++i)
    {
        if(sum[i]==0)   continue;
        mon+=sum[i]*no[h].p;
        if(no[h].m==0&&i+no[h].n<=tim)
        {
            mon-=per[i]*no[h].q;
            per[i+no[h].n]+=per[i];
            sum[i+no[h].n]+=sum[i];
        }
        else    if(no[h].m!=0&&i+no[h].m<=tim)
            sum[i+no[h].m]+=sum[i];
        mfind(mon,h,tim,i+no[h].n);
    }
    return mon;
}
int main()
{
    int w,h,a,t,ww,hh;
    __int64 ans,mon;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%I64d",&w,&h,&a,&t,&mon);
        for(int i=0;i<a;++i)
            scanf("%d%d%d%d",&no[i].q,&no[i].p,&no[i].n,&no[i].m);
        memset(num,0,sizeof(num));
        num[9]=w/3*(h/3);
        ww=w,hh=h;
        w%=3,h%=3;
        ++num[9-(3-w)*(3-h)];
        num[h*3]+=ww/3-1;
        num[w*3]+=hh/3-1;
        num[h*w]+=2;
        ans=mon;
        for(int i=0;i<a;++i)
            ans=max(ans,cal(i,t,mon));
        cout<<ans<<'\n';
    }
    return 0;
}
