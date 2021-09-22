#include<cstdio>
#include<cstring>
#include<ctime>
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
int ret[N],ps[N],fg[N];
int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T,n,m,i,j;
    int t1=clock();
    scanf("%d",&T);
    while(T--)
    {
        //printf("T:%d \n",T);
        scanf("%d%d",&n,&m);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
        }
        memset(fg,0,sizeof(fg));
        int tid=1;
        while(m--)
        {
            int L,R,r=0;
            scanf("%d%d",&L,&R);
            for(i=L;i<=R;i++)
            {
                int d=0;
                if(a[i]>1&&fg[a[i]-1]==tid)d++;
                if(a[i]<n&&fg[a[i]+1]==tid)d++;
                if(d==2)r--;
                else if(d==0)r++;
                fg[a[i]]=tid;
            }
            printf("%d\n",r);
            tid++;
        }
    }
    int t2=clock();
    printf("cost:%d \n",t2-t1);
    return 0;
}

