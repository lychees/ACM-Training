
#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>

const int maxn = 110,inf=0x7fffffff/10,M=maxn*maxn*2;
int n,m,map[maxn][maxn],dis[maxn][maxn];
int mindis[maxn][maxn],used[maxn][maxn],que[M],start,tail;

void push(int x,int y,int d)
{
    if(mindis[x][y]>d)
    {
        mindis[x][y]=d;
        if(!used[x][y])
        {
            used[x][y]=1;
            tail++;que[tail%M]=x;
            tail++;que[tail%M]=y;
        }
    }
}
int spfa()
{
    memset(used,0,sizeof(used));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            mindis[i][j]=inf;
    start=1;tail=0;
    push(1,1,1);
    while(start<=tail)
    {
        int x=que[start%M];start++;
        int y=que[start%M];start++;
        used[x][y]=0;
        push(y,x,mindis[x][y]+max(0,dis[y][x]-1));
        for(int i=1;i<=n;i++)
        {
            if(map[y][i])
                push(x,i,mindis[x][y]+1-(i==x));
            if(map[i][x])
                push(i,y,mindis[x][y]+1-(i==y));
        }
    }
    
    return mindis[2][2];
}

int main()
{
	freopen("routing.in","r",stdin);
	freopen("bc.out","w",stdout);
    int kase = 0;
    while(scanf("%d%d",&n,&m)==2)
    {
        if(n==0 && m==0)break;
        
        printf("Network %d\n",++kase);
        
        int a,b;
        memset(map,0,sizeof(map));
        while(m--)
        {
            scanf("%d%d",&a,&b);
            map[a][b]=1;
        }
        for(int i=1;i<=n;i++)
        {
            map[i][i]=0;
            for(int j=1;j<=n;j++)
                if(!map[i][j])
                    dis[i][j]=inf;
                else dis[i][j]=1;
            dis[i][i]=0;
        }
        
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        int ans=spfa();
        
        if(ans<inf)
            printf("Minimum number of nodes = %d\n\n",ans);
        else printf("Impossible\n\n");
    }
    
    return 0;
}

 
