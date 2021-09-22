#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long ll;
using namespace std;
const int N = 100010;
const int M = 200100;

struct Edg {
    int v,nxt,id;
} edg[M];
int tote,head[N];
void init() {
    tote = 0;
    memset(head,-1,sizeof(head));
}
inline void addedg(int u,int v,int id) {
    edg[tote].id = id;
    edg[tote].v = v;
    edg[tote].nxt=head[u];
    head[u]=tote++;
};
int f[N],p[N],h[N],mxf[N],fa[N],id[N],len[N];
bool vis[N];
struct DP {
    int id,dis;
    DP(int i,int d):id(i),dis(d) {}
    DP() {}
} dp[N][3];
void sw(DP &a,DP &b) {
    DP t = a;
    a = b;
    b = t;
}
void up(int u) {
    if(dp[u][2].dis > dp[u][1].dis) {
        sw(dp[u][2],dp[u][1]);
        if(dp[u][1].dis > dp[u][0].dis) {
            sw(dp[u][1], dp[u][0]);
        }
    }
}
void dfs1(int u) {
    int v;
    vis[u] = 1;
    for(int i = head[u]; ~i ; i =edg[i].nxt) {
        v = edg[i].v;
        if(vis[v]) continue;
        fa[v] = u;
        id[v] = edg[i].id;
        dfs1(v);
        int w = dp[v][0].dis + 1;
        if(dp[u][2].dis < w) {
            dp[u][2] = DP(v,w);
            up(u);
        }
        mxf[u] = max(mxf[u] , f[v]);
    }
    if(dp[u][0].id == 0) f[u] = 0;
    else if(dp[u][1].id != 0) {
        f[u] = max(mxf[u] , dp[dp[u][0].id][0].dis + dp[dp[u][1].id][0].dis + 2);
    }
    else {
        f[u] = max(mxf[u] , dp[dp[u][0].id][0].dis + 1);
    }
}
void dfs2(int u) {
    int v;
    vis[u] = 1;
    for(int i = head[u]; ~i ; i  = edg[i].nxt) {
        v = edg[i].v;
        if(vis[v]) continue;
        if(v == dp[u][0].id) {
            if(dp[u][1].id != 0) p[v] = max(dp[dp[u][1].id][0].dis + 2 , p[u]+1);
            else p[v] = p[u]+1;
        } else {
            if( dp[u][0].id != 0) p[v] = max( dp[dp[u][0].id][0].dis + 2 , p[u]+1);
            else p[v] = p[u] + 1;
        }
        if(v == dp[u][0].id) {
            if( dp[u][1].id == 0) {
                h[v] = max(h[u] , p[u]);
            } else {
                h[v] = max(f[dp[u][1].id] ,h[u]);
                h[v] = max(h[v] , dp[dp[u][1].id][0].dis + p[u] + 1);
                if(dp[u][2].id != 0) {
                    h[v] = max(h[v] , dp[dp[u][1].id][0].dis + dp[dp[u][2].id][0].dis + 2 );
                }
            }
        } else if(v == dp[u][1].id) {
            h[v] = max(f[dp[u][0].id] , h[u]);
            h[v] = max(h[v] , dp[dp[u][0].id][0].dis + p[u] + 1);
            if(dp[u][2].id != 0) {
                h[v] = max(h[v] , dp[dp[u][0].id][0].dis +dp[dp[u][2].id][0].dis+ 2 );
            }
        } else{
            h[v] = max(f[dp[u][0].id] , h[u]);
            h[v] = max(h[v] , dp[dp[u][0].id][0].dis + dp[dp[u][1].id][0].dis + 2 );
            h[v] = max(h[v] , dp[dp[u][0].id][0].dis + p[u] + 1);
        }
        dfs2(v);
    }
}
void sol() {
    int t,cas = 0;
    scanf("%d",&t);
    while(t--) {
        init();
        int n,u,v,w;
        scanf("%d",&n);
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d",&u,&v,&w);
            len[i] = w;
            addedg(u,v,i);
            addedg(v,u,i);
        }
        memset(f, 0 ,sizeof(int)*(n + 1));
        memset(h, 0 ,sizeof(int)*(n + 1));
        memset(p, 0 ,sizeof(int)*(n + 1));
        memset(mxf, 0,sizeof(int)*(n + 1));
        memset(dp, 0, sizeof(dp[0]) * (n + 1));
        memset(vis , 0 , sizeof(bool)*(n + 1));dfs1(1);
        memset(vis , 0 , sizeof(bool)*(n + 1));dfs2(1);
        int mn = 0x7fffffff;
        int ans=0;
        for(int i = 2; i <= n ; ++i){
            int tmp = max(f[i],h[i]);
            tmp = tmp * len[ id[i] ];
            if(mn > tmp){
                mn = tmp;
                ans = id[i];
            }
            else if( mn == tmp) {
                if(ans > id[i]) ans = id[i];
            }
        }
        printf("Case #%d: %d\n",++cas,ans);
    }
    return;
}
int main() {
    sol();
    return 0;
}

