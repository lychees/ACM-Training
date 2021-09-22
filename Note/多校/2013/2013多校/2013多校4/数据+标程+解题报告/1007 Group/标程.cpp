#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int N = 100005;
struct Q
{
    int l,r,id;
}query[N];
bool cmp(Q x,Q y)
{
    return x.r>y.r;
}
int a[N],c[N],d[N];
int lowbit(int x)
{
    return x&(-x);
}
void up(int x,int v)
{
    while(x<N)
    {
        c[x]+=v;
        x+=lowbit(x);
    }
}
int getsum(int x)
{
    int r=0;
    while(x>0)
    {
        r+=c[x];
        x-=lowbit(x);
    }
    return r;
}
bool u[N];
int ret[N],ps[N];
int main()
{
    int T,n,m,i,j;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            ps[a[i]]=i;
        }
        memset(c,0,sizeof(c));
        memset(d,0,sizeof(d));
        memset(u,0,sizeof(u));
        for(i=n;i>0;i--)
        {
            if(u[a[i]-1])d[i]++;
            if(u[a[i]+1])d[i]++;
            if(d[i]==0)
            {
                up(i,1);
            }
            else if(d[i]==2)
            {
                up(i,-1);
            }
            u[a[i]]=true;
        }
        for(i=0;i<m;i++)
        {
            scanf("%d%d",&query[i].l,&query[i].r);
            query[i].id=i;
        }
        sort(query,query+m,cmp);
        int j=n;
        for(i=0;i<m;i++)
        {
            while(j>query[i].r)
            {
                if(a[j]>1&&ps[a[j]-1]<j)
                {
                    d[ps[a[j]-1]]--;
                    up(ps[a[j]-1],1);
                }
                if(a[j]<n&&ps[a[j]+1]<j)
                {
                    d[ps[a[j]+1]]--;
                    up(ps[a[j]+1],1);
                }
                j--;
            }
            ret[query[i].id]=getsum(query[i].r)-getsum(query[i].l-1);
        }
        for(i=0;i<m;i++)printf("%d\n",ret[i]);
    }
    return 0;
}