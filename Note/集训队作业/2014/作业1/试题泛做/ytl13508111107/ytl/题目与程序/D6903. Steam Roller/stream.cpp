#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
const int maxn = 110;
int num[maxn][maxn][4][2][2],from_w[maxn][maxn][4],to_w[maxn][maxn][4],top;
int n,m,r1,c1,r2,c2;
int head[maxn*maxn*4*2*2],to[maxn*maxn*100],next[maxn*maxn*100],w[maxn*maxn*100],op;
int used[maxn*maxn*4*2*2];
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
void init()
{
    memset(head,0,sizeof(head));
    memset(from_w,0,sizeof(from_w));
    memset(to_w,0,sizeof(to_w));
    memset(used,0,sizeof(used));
    op=0;
    top=0;   
}
bool isok(int x,int y)
{
    return x>=1 && x<=n && y>=1 && y<=m;
}
void build(int a,int b,int c)
{
    next[++op]=head[a];head[a]=op;to[op]=b;w[op]=c;
}
typedef pair<int,int> node;
int dijkstra(int s,int t)
{
    priority_queue<node> que;
    que.push(node(0,s));
    while(!que.empty())
    {
        node e=que.top();que.pop();
        if(used[e.second])continue;
        used[e.second]=1;
        if(e.second==t)
            return -e.first;
        for(int pos=head[e.second];pos;pos=next[pos])
            que.push(node(e.first-w[pos],to[pos]));
    }
    return -1;
}
int solve()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int d=0;d<4;d++)
                if(isok(i+dx[d],j+dy[d]) && to_w[i][j][d])
                    for(int k1=0;k1<2;k1++)
                        for(int k2=0;k2<2;k2++)
                            build(num[i][j][d][0][k1],num[i][j][d][1][k2],to_w[i][j][d]*(2-int(k1==0&&k2==0)));
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int d=0;d<4;d++)
                if(isok(i+dx[d],j+dy[d]))
                {
                    int x=i+dx[d],y=j+dy[d];
                    for(int d2=0;d2<4;d2++)
                        if(isok(x+dx[d2],y+dy[d2]))
                        {
                            if(d==d2)
                                build(num[i][j][d][1][0],num[x][y][d2][0][0],0);
                            else build(num[i][j][d][1][1],num[x][y][d2][0][1],0);
                        }
                }
    int s=++top,t=++top;
    for(int d=0;d<4;d++)
    {
        if(isok(r1+dx[d],c1+dy[d]))
            build(s,num[r1][c1][d][0][1],0);
        if(isok(r2+dx[d],c2+dy[d]))
            build(num[r2+dx[d]][c2+dy[d]][d^1][1][1],t,0);
    }
    return dijkstra(s,t);
}
int main()
{
    int kase=0,x;
    while(scanf("%d%d%d%d%d%d",&n,&m,&r1,&c1,&r2,&c2)==6)
    {
        if(n==0 && m==0 && r1==0 && c1==0 && r2==0 && c2==0)
            break;
        init();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                for(int d=0;d<4;d++)
                    if(isok(i+dx[d],j+dy[d]))
                        for(int k1=0;k1<2;k1++)
                            for(int k2=0;k2<2;k2++)
                                num[i][j][d][k1][k2]=++top;
        
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<m;j++)
            {
                scanf("%d",&x);
                to_w[i][j][0]=x;
                to_w[i][j+1][1]=x;
                from_w[i][j+1][1]=x;
                from_w[i][j][0]=x;
            }
            if(i==n)continue;
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&x);
                to_w[i][j][2]=x;
                from_w[i][j][2]=x;
                from_w[i+1][j][3]=x;
                to_w[i+1][j][3]=x;
            }
        }
        
        printf("Case %d: ",++kase);
        int ans=solve();
        if(ans!=-1)
            printf("%d\n",ans);
        else printf("Impossible\n");
    }
    
    return 0;   
}
