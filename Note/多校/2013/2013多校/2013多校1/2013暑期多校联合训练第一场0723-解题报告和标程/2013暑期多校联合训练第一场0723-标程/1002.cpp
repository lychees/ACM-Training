#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
#include "queue"
#include "algorithm"
#include "cmath"
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;
const int CH = 26;
const int N = 100010;
vector<pair<int,int> > edge[N];
pair<int,int> father[N];
vector<int> dep[N];
int num[N];
int now[N];
int trie[N][CH];
int sz=0,r_sz=0;
int label[N],mark[N];
int d[N],height[N],in_stamp[N],out_stamp[N];
int val[N];
int time_stamp;
int max_height=0;
void rebuild()
{
    queue<int> que;
    sz=0;
    memset(trie[0],0,sizeof(trie[0]));
    label[1]=0;
    que.push(1);
    while(!que.empty()){
        int u=que.front();
        que.pop();
        int lu=label[u];
        for(int i=0;i<edge[u].size();i++){
            int v=edge[u][i].first;
            int w=edge[u][i].second;
            if(!trie[lu][w]){
                trie[lu][w]=++sz;
                for(int j=0;j<CH;j++){
                    trie[sz][j]=0;
                }
                label[v]=sz;
                que.push(v);
            }else{
                label[v]=trie[lu][w];
                que.push(v);
            }
        }
    }
}
void remark(int x)
{
    mark[x]=++time_stamp;
    for(int i=0;i<CH;i++){
        int u=trie[x][i];
        if(u!=0){
            remark(u);
        }
    }
}
const int MOD = 1000000000 + 7;
int hash[N];
void dfs(int x)
{
    d[x]=1;
    val[x]=mark[label[x]];
    in_stamp[x]=++time_stamp;
    out_stamp[x]=x;
    hash[x] = ((long long)hash[father[x].first] * 26 + father[x].second) % MOD;
    for(int i=0;i<edge[x].size();i++){
        int u=edge[x][i].first;
        height[u]=height[x]+1;
        dfs(u);        
        if(in_stamp[out_stamp[x]]<in_stamp[out_stamp[u]]){
            out_stamp[x]=out_stamp[u];
        }
        val[x]=max(val[x],val[u]);
        d[x]=max(d[x],d[u]+1);
    }
    dep[height[x]].PB(x);
    max_height=max(max_height,height[x]);
}
int Max[20][N];
void initRMQ(int n)
{
    for(int i=1;i<=n;i++){
        Max[0][i]=now[i];
    }
    for(int i=1;(1<<i)<=n;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            int u=Max[i-1][j],v=Max[i-1][j+(1<<(i-1))];
            if(val[u]<val[v]){
                Max[i][j]=v;
            }else{
                Max[i][j]=u;
            }
        }
    }
}
int query(int l,int r)
{
    int t=floor(log((double)(r-l+1))/log(2.0));
    int u=Max[t][l],v=Max[t][r-(1<<t)+1];
    if(val[u]<val[v]) return v;
    return u;
}
bool cmp(int a,int b)
{
    return in_stamp[a]<in_stamp[b];
}
int solve(int x,int y)
{
    if(d[x]<=y) return -1;
    int h=height[x]+y;
    vector<int>::iterator iter;
    int l,r;
    iter=lower_bound(dep[h].begin(),dep[h].end(),x,cmp);
    l=iter-dep[h].begin()+1+num[h-1];
    iter=dep[h].begin();
    iter=upper_bound(dep[h].begin(),dep[h].end(),out_stamp[x],cmp);
    r=iter-dep[h].begin()+num[h-1];    
    return query(l,r);
}
void print(int x,int y)
{
    if(y==0){
        return ;
    }
    print(father[x].first,y-1);
    printf("%c",father[x].second+'a');
}
void init(int n)
{
    for(int i=1;i<=n;i++){
        edge[i].clear();
    }
    for(int i=1;i<=n;i++){
        dep[i].clear();
    }
    sz=0;
}
int pow26[N];
int main(void)
{
    pow26[0] = 1;
    for (int i = 1; i < N; ++ i) {
        pow26[i] = (long long)pow26[i - 1] * 26 % MOD;
    }
    int T,n,Q,x,y;
    char s[2];
    scanf("%d",&T);
    while(T--){
        memset(hash, 0, sizeof(hash));
        scanf("%d",&n);
        init(n);
        for(int i=1;i<n;i++){
            scanf("%d%d%s",&x,&y,s);
            edge[x].PB(MP(y,s[0]-'a'));
            father[y]=MP(x,s[0]-'a');
        }
        rebuild();
        time_stamp=0;
        remark(0);
        height[1]=1;
        time_stamp=0;
        dfs(1);
        sz=0;
        for(int i=1;i<=max_height;i++){
            for(int j=0;j<dep[i].size();j++){
                now[++sz]=dep[i][j];
            }
            num[i]=num[i-1]+dep[i].size();
        }        
        initRMQ(n);
        scanf("%d",&Q);
        while(Q--){
            scanf("%d%d",&x,&y);
            int u=solve(x,y);
            if(u==-1){
                printf("IMPOSSIBLE\n");
            }else{
                int answer = ((hash[u] - (long long)hash[x] * pow26[y]) % MOD + MOD) % MOD;
                // print(u,y);
                printf("%d\n", answer);
            }
        }
    }
    return 0;
}
