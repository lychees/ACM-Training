#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100,maxm = maxn*maxn;
namespace Dinic{
    const int inf = 0x7fffffff/2;
    int head[maxn],head2[maxn],next[maxm*2],to[maxm*2],f[maxm*2],op;
    int dis[maxn],que[maxn],way[maxn];
    int s,t,stop,maxflow;
    
    void init(){
        op = 1;
        s=t=0;maxflow = 0;
        stop=0;
        memset(head,0,sizeof(head));
        }
    void build(int a,int b,int c){
        next[++op]=head[a];head[a]=op;to[op]=b;f[op]=c;
        next[++op]=head[b];head[b]=op;to[op]=a;f[op]=0;
        }
    bool dfs(){
        memset(dis,0,sizeof(dis));
        dis[s]=1;
        int start,tail;
        que[start=tail=0]=s;
        while(start<=tail){
            int u=que[start++];
            for(int pos=head[u];pos;pos=next[pos])
                if(!dis[to[pos]] && f[pos]){
                    dis[to[pos]]=dis[u]+1;
                    que[++tail]=to[pos];
                    }
            }
        memcpy(head2,head,sizeof(head2));
        //cout<<"debug  "<<dis[t]<<endl;
        return dis[t];
        }
    bool find(int u,int top){
        if(u==t){
            int minflow = inf;
            for(int i=1;i<top;i++)
                if(f[way[i]]<minflow){
                    minflow=f[way[i]];
                    stop=i;
                    }
            maxflow += minflow;
            //cout<<"minflow  "<<minflow<<endl;
            for(int i=1;i<top;i++){
                f[way[i]]-=minflow;
                f[way[i]^1]+=minflow;
                }
            return 1;
            }
        for(int&pos=head2[u];pos;pos=next[pos])
            if(dis[to[pos]]==dis[u]+1 && f[pos]){
                way[top]=pos;
                if(find(to[pos],top+1)&& top!=stop)
                    return 1;
                }
        return 0;
        }
    int findmaxflow(){
        maxflow = 0;
        while(dfs())
            find(s,1);
        return maxflow;
        }
    }
int n,m;
int map[maxn][maxn],used[maxn],M[maxn];
void del(int u){
    for(int i=1;i<=n;i++)
        map[i][u]=map[u][i]=0;
    }
int maxflow(int u){
    Dinic::init();
    Dinic::s=u;Dinic::t=0;
    for(int i=0;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(map[i][j]){
                Dinic::build(i,j,map[i][j]);
                Dinic::build(j,i,map[i][j]);
                }
    return Dinic::findmaxflow();
    }
int main()
{
    freopen("tunnels.in","r",stdin);
    freopen("tunnels.out","w",stdout);
    int cases = 0;
    while(scanf("%d%d",&n,&m)==2 && n && m){
        int a,b;
        memset(map,0,sizeof(map));
        while(m--){
            scanf("%d%d",&a,&b);
            if(a>b)swap(a,b);
            map[a][b]++;
            }
        for(int i=1;i<=n;i++)
            M[i]=maxflow(i);
        memset(used,0,sizeof(used));
        for(int i=1;i<=n;i++){
            int minv = Dinic::inf;
            for(int j=1;j<=n;j++)
                if(!used[j])minv=min(minv,M[j]);
            for(int j=1;j<=n;j++)
                if(M[j]==minv){
                    used[j]=1;
                    del(j);
                    }
            for(int j=1;j<=n;j++)
                if(!used[j])
                    M[j]=min(M[j],minv+maxflow(j));
            }
        printf("Case %d: %d\n\n",++cases,M[1]);
        }
    
    return 0;
}
