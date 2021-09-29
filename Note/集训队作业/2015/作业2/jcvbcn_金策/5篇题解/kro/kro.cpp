#include<cstring> 
#include<cstdlib> 
#include<algorithm> 
#include<cstdio> 
#include<iostream> 
using namespace std; 
int n,m; 
struct edge{ 
    int v,next,vis; 
}e[1000005];int g[500005],etot; 
void ae(int u,int v){ 
    e[etot].v=v;e[etot].next=g[u];g[u]=etot++; 
} 
int U[250005],V[250005],val[250005]={0}; 
int stk[500005],cur[500005],ine[500005];int top; 
int seq[250005],vis[250005]={0},ind;int lab[250005]={0}; 
void dfs1(int rt){ 
    top=0;ind=0; 
    stk[++top]=rt;cur[top]=g[rt];ine[rt]=-1; 
    while(top){ 
        int u=stk[top]; 
        if(cur[top]==g[u])seq[++ind]=u,vis[u]=1; 
        while(~cur[top] && (cur[top]==(ine[u]^1) || vis[e[cur[top]].v]))cur[top]=e[cur[top]].next; 
        if(~cur[top]){ 
            int v=e[cur[top]].v;             
            stk[top+1]=v;cur[top+1]=g[v];ine[v]=cur[top]; 
            cur[top]=e[cur[top]].next; 
            ++top; 
        }else top--; 
    } 
} 
int ans[1000005];int anslen=0; 
int deg[250005]={0}; 
void dfs2(int rt){ 
    top=0; 
    stk[++top]=rt;ine[top]=-1; 
    while(top){ 
        int u=stk[top]; 
        while(~g[u] && e[g[u]].vis)g[u]=e[g[u]].next; 
        if(~g[u]){ 
            e[g[u]].vis=e[g[u]^1].vis=1; 
            int v=e[g[u]].v; 
            ine[top+1]=g[u]; 
            g[u]=e[g[u]].next; 
            stk[++top]=v; 
        }else{ 
            if(~ine[top]){ 
                ans[++anslen]=ine[top]; 
            } 
            top--; 
        } 
    } 
} 
int tmpans[250005];int tmplen=0; 
int main() 
{ 
    scanf("%d%d",&n,&m); 
    for (int i=1;i<=m;i++)scanf("%d%d",&U[i],&V[i]),deg[U[i]]++,deg[V[i]]++; 
    etot=0;memset(g,-1,sizeof(g)); 
    for (int i=1;i<=m;i++)ae(U[i],V[i]),ae(V[i],U[i]); 
    dfs1(1); 
    for (int i=n;i>=2;i--){ 
        int u=seq[i];vis[u]=2; 
        for (int i=g[u];~i;i=e[i].next){ 
            if(vis[e[i].v]!=2 && i!=(ine[u]^1)){ 
                lab[e[i].v]^=1; 
                val[1+(i>>1)]=i&1; 
            } 
        } 
        int ei=ine[u]^1; 
        if(lab[u])val[1+(ei>>1)]=(ei&1)^1; 
        else lab[e[ei].v]^=1,val[1+(ei>>1)]=ei&1; 
    } 
    etot=0;memset(g,-1,sizeof(g)); 
    for (int i=1;i<=m;i++){ 
        if(val[i])ae(U[i]+n,V[i]),ae(V[i],U[i]+n); 
        else ae(V[i]+n,U[i]),ae(U[i],V[i]+n); 
    } 
    for (int i=1;i<=n;i++)if(deg[i]&1){ 
        ae(2*n+1,i);ae(i,2*n+1); 
    } 
    dfs2(2*n+1); 
    int u=2*n+1; 
    int st,ed; 
    for (int i=anslen;i>=1;i--){ 
        if(e[ans[i]^1].v==2*n+1){ 
            st=e[ans[i]].v; 
            tmplen=0; 
        }else if(e[ans[i]].v==2*n+1){ 
            ed=e[ans[i]^1].v; 
            printf("%d %d %d\n",st>n?st-n:st,ed>n?ed-n:ed,tmplen); 
            for (int j=1;j<=tmplen;j++){ 
                if(j!=1)printf(" "); 
                printf("%d",1+(tmpans[j]>>1)); 
            } 
            printf("\n"); 
        }else tmpans[++tmplen]=ans[i];       
    } 
    return 0; 
}