#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;
inline int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
const int maxn=100003,maxm=maxn*4;
int n,m,pre[maxm],t[maxm],v[maxm],Link[maxn],op[maxm],dist[maxn],prev[maxn],d[maxn],res[maxn],fa[maxn];
bool vis[maxn],used[maxm];
struct data
{
    int t,v;
    data(){}
    data(int _t,int _v){t=_t,v=_v;}
    inline bool operator <(const data &b)const{return b.v<v;}
};
struct Tcir
{
    int x,y,len;
    Tcir(){}
    Tcir(int _x,int _y,int _l){x=_x,y=_y,len=_l;}
    inline bool operator <(const Tcir &b)const{return len<b.len;}
}cir[maxm];
priority_queue<data> Q;
  
void dijkstra()
{
    memset(dist,120,sizeof(dist));
    Q.push(data(1,dist[1]=0));d[1]=0;
    while(!Q.empty())
    {
        data tp=Q.top();Q.pop();
        if(dist[tp.t]!=tp.v)continue;
        vis[tp.t]=1;
        for(int i=Link[tp.t];i;i=pre[i])
            if(!vis[t[i]]&&dist[t[i]]>tp.v+v[i])
                d[t[i]]=d[tp.t]+1,prev[t[i]]=i,Q.push(data(t[i],dist[t[i]]=tp.v+v[i]));
    }
}
inline int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
int main()
{
    n=get(),m=get();
    for(int i=1,tot=0;i<=m;i++)
    {
        int x=get(),y=get(),z=get();
        pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y; v[tot]=z; op[tot]=tot+1;
        pre[++tot]=Link[y]; Link[y]=tot; t[tot]=x; v[tot]=z; op[tot]=tot-1;
    }
    dijkstra();
    for(int i=1;i<=n;i++)fa[i]=i,used[prev[i]]=used[op[prev[i]]]=1;
    int tot=0;
    for(int i=1;i<=2*m;i+=2)
        if(!used[i])cir[++tot]=Tcir(t[i],t[op[i]],dist[t[op[i]]]+dist[t[i]]+v[i]);
    sort(cir+1,cir+1+tot);
    for(int i=1;i<=tot;i++)
    {
        int x=getfa(cir[i].x),y=getfa(cir[i].y);
        while(x!=y)
        {
            if(d[x]<d[y])swap(x,y);
            res[x]=cir[i].len-dist[x],fa[x]=t[op[prev[x]]],x=getfa(x);
        }
    }
    for(int i=2;i<=n;i++)
        if(res[i]==0)puts("-1");else printf("%d\n",res[i]);
    return 0;
}
