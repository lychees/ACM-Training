#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;

typedef long long LL;
typedef double dll;
typedef struct node
{
    int op;dll ang;
    node(){}
    node(int op,dll ang):op(op),ang(ang){}
    bool operator <(const node&B)const
    {
        return ang<B.ang;
    }
};
const int maxn = 52*52+100,inf=0x7fffffff/2;
const dll eps=1e-3,pi=3.1415926535897932384626433832795;
int dcmp(dll x)
{
    if(fabs(x)<eps)
        return 0;
    return x>0?1:-1;
}

int n,m,X[maxn],Y[maxn],H[maxn];
int point_num[200][200],point_cnt;
map<LL,int> area_num;int area_cnt;
int Map[maxn][maxn];
int head[maxn*4],next[maxn*100],to[maxn*100],w[maxn*100],op;
int dis[maxn*4],used[maxn*4],minH[maxn*4],fa[maxn*4];
vector<node> V;

int point(char *s)
{
    if(!point_num[(int)s[0]][(int)s[1]])
        point_num[(int)s[0]][(int)s[1]]=++point_cnt;
    return point_num[(int)s[0]][(int)s[1]];
}
int area(int a,int b,int c)
{
    if(a>b)swap(a,b);
    if(a>c)swap(a,c);
    if(b>c)swap(b,c);
    
    LL q=(LL(a)*(n+1)+b)*(n+1)+c;
    if(!area_num.count(q))
    {
        area_cnt++;
        //cout<<"area  "<<a<<" "<<b<<" "<<c<<endl;
        minH[area_cnt]=min(min(H[a],H[b]),H[c]);
        area_num.insert(pair<LL,int>(q,area_cnt));
    }
    return area_num[q];
}
void build(int a,int b,int c)
{
    next[++op]=head[a];head[a]=op;to[op]=b;w[op]=c;
}
void spfa()
{
    for(int i=0;i<=area_cnt;i++)
        dis[i]=inf;
    dis[0]=0;
    queue<int> que;
    que.push(0);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        used[u]=0;
        for(int pos=head[u];pos;pos=next[pos])
            if(dis[to[pos]]>max(dis[u],w[pos]))
            {
                dis[to[pos]]=max(dis[u],w[pos]);
                if(!used[to[pos]])
                {
                    used[to[pos]]=1;
                    que.push(to[pos]);
                }
            }
    }
}
int findfa(int x)
{
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
bool isok(int a,int b,int c)
{
    LL x1=X[b]-X[a],y1=Y[b]-Y[a],x2=X[c]-X[a],y2=Y[c]-Y[a];
    return x1*y2-y1*x2>0;
}
void solve()
{
    for(int i=1;i<=n;i++)
    {
        V.clear();
        for(int j=1;j<=n;j++)
            if(Map[i][j])
                V.push_back(node(j,atan2(Y[j]-Y[i],X[j]-X[i])));
        sort(V.begin(),V.end());
        
        //cout<<"---  "<<i<<" ------"<<endl;
        //for(int k=0;k<(int)V.size();k++)
        //    printf("%d %lf  ",V[k].op,V[k].ang);
        //cout<<endl;
        
        int q=V.size();
        if(q<=2)
        {
            node a=V[0],b=V[1];
            build(0,area(i,a.op,b.op),min(min(H[a.op],H[b.op]),H[i]));
            continue;
        }
        for(int k=0;k<q;k++)
        {
            node a=V[k],b=V[(k+1)%q],c=V[(k+2)%q];
            
            //cout<<"build "<<a.op<<" "<<b.op<<" "<<c.op<<endl;
            //cout<<Map[a.op][b.op]<<" "<<Map[b.op][c.op]<<endl;
            if(Map[a.op][b.op]==1)
            {
                if(!isok(i,a.op,b.op))continue;
                if(Map[b.op][c.op]==1)
                {
                    if(isok(i,b.op,c.op))
                        build(area(i,a.op,b.op),area(i,b.op,c.op),min(H[i],H[b.op]));
                }
                else
                    build(0,area(i,a.op,b.op),min(H[i],H[b.op]));
            }else 
                if(isok(i,c.op,b.op))
                    build(0,area(i,b.op,c.op),min(H[i],H[b.op]));
        }
    }
    spfa();
    //for(int i=1;i<=area_cnt;i++)
    //    printf("%d\n",dis[i]);
    for(int i=1;i<=area_cnt;i++)
        fa[i]=i;
    for(int u=1;u<=area_cnt;u++)
        if(minH[u]<dis[u])
        {
            for(int pos=head[u];pos;pos=next[pos])
            {
                int v=to[pos];
                if(v!=0 && dis[v]==dis[u] && dis[u]>w[pos] && minH[v]<dis[v])
                {
                    //cout<<"------"<<endl;
                    fa[findfa(u)]=findfa(v);
                }
            }
        }
    memset(used,0,sizeof(used));
    for(int i=1;i<=area_cnt;i++)
        if(minH[i]<dis[i])
            used[findfa(i)]=1;
    vector<int> M;
    for(int i=1;i<=area_cnt;i++)
        if(used[i])M.push_back(dis[i]);
    sort(M.begin(),M.end());
    for(int k=0;k<(int)M.size();k++)
        printf("%d\n",M[k]);
    if((int)M.size()==0)
        printf("0\n");
}

int main()
{
	freopen("rain.in","r",stdin);
	freopen("rain.out","w",stdout);
    char s[4];
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);point(s);
        scanf("%d%d%d",&X[i],&Y[i],&H[i]);
    }
    while(m--)
    {
        scanf("%s",s);int a=point(s);
        scanf("%s",s);int b=point(s);
        //cout<<a<<" "<<b<<endl;
        Map[a][b]=Map[b][a]=1;
    }
    solve();
    
    return 0;   
}
