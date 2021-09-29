#include<iostream>
using namespace std;
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>

const int maxn=20,inf=0x7fffffff/2;
int dp[2][1<<maxn][maxn],used[1<<maxn][maxn];
int n,m,to[maxn][maxn],h,total;
int num[1<<maxn];

typedef struct node
{
    int s,u;
    node(){}
    node(int s,int u):s(s),u(u){}
};
const int M=(1<<25)-1;
node que[M+1];

int lowbit(int x)
{
    static bool first = 1;
    if(first)
    {
        for(int i=0;i<(1<<n);i++)
            num[i]=(i&1)+num[i>>1];
        first=0;
    }
    return num[x];
}
void spfa(int u)
{
    int start,tail;
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<n;j++)
            dp[u==n-1][i][j]=inf;
    dp[u==n-1][0][u]=0;
    que[start=tail=0]=node(0,u);
    while(start<=tail)
    {
        node e=que[start&M];start++;
        used[e.s][e.u]=0;
        for(int v=0;v<n;v++)
            if(to[e.u][v])
            {
                if(dp[u==n-1][e.s][v]>dp[u==n-1][e.s][e.u]+to[e.u][v])
                {
                    dp[u==n-1][e.s][v]=dp[u==n-1][e.s][e.u]+to[e.u][v];
                    if(!used[e.s][v])
                    {
                        used[e.s][v]=1;
                        tail++;
                        que[tail&M]=node(e.s,v);
                    }
                }
                if(!((e.s>>v)&1) && v>0 && v<n-1 && lowbit(e.s^(1<<v))<= h-h/2 && 
                    dp[u==n-1][e.s^(1<<v)][v]>dp[u==n-1][e.s][e.u]+to[e.u][v])
                    {
                        dp[u==n-1][e.s^(1<<v)][v]=dp[u==n-1][e.s][e.u]+to[e.u][v];
                        if(!used[e.s^(1<<v)][v])
                        {
                            used[e.s^(1<<v)][v]=1;
                            tail++;
                            que[tail&M]=node(e.s^(1<<v),v);
                        }
                    }
            }
    }
}

int main()
{
   	freopen("bus.in","r",stdin);
	freopen("bc.out","w",stdout);
 scanf("%d%d",&n,&m);
    int a,b,c;
    h=n-2;
    total=((1<<n)-1)^1^(1<<(n-1));
    
    while(m--)
    {
        scanf("%d%d%d",&a,&b,&c);
        if(to[a][b])
            to[a][b]=to[b][a]=min(to[a][b],c);
        else to[a][b]=to[b][a]=c;
    }
    spfa(0);
    spfa(n-1);
    int ans=inf;
    
    for(int s=0;s<(1<<n);s++)
        if((s&total)==s && lowbit(s)==h/2)
        {
            int a=inf,b=inf;
            for(int u=0;u<n;u++)
            {
                a=min(a,dp[0][s][u]+dp[1][s^total][u]);
                b=min(b,dp[1][s][u]+dp[0][s^total][u]);
            }
            ans=min(ans,a+b);
        }
    cout<<ans<<endl;
    
    return 0;
}
