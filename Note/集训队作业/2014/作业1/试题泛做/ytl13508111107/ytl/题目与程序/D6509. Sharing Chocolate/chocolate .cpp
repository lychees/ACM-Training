//By ytl 2014-1-14
#include <iostream>
#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 105
#define L (1<<16)
using namespace std;

int d,n,x,y;
int a[N],area[L],f[N][L];

namespace Graph{
    int head[N*N],nex[L],gt=1;
    void build(int a,int b){
        nex[b]=head[a];
        head[a]=b;
    }
}
using namespace Graph;

void preDeal(){
    d=(1<<n)-1;
    for (int i=1;i<=d;i++)
        for (int j=0;j<n;j++) if ((i>>j)&1){
            area[i]=area[i-(1<<j)]+a[j];
            build(area[i],i);
            break;
        }
}
void init(){
    for (int i=1;i<=x;i++)
        for (int j=0;j<(1<<n);j++)
            f[i][j]=2;
    for (int i=1;i<(1<<n);i++) nex[i]=0;
    for (int i=1;i<=x*y;i++) head[i]=0;
}
int dfs(int i,int k){
    if (f[i][k]!=2) return f[i][k];
    int j=area[k]/i;
    for (int l=1;l<=(i>>1);l++){
        for (int e=head[l*j];e;e=nex[e])
            if ((k|e)==k){
                if (dfs(l,e)&&dfs(i-l,k-e)){
                    f[i][k]=1;
                    return 1;
                }
            }
    }  
    for (int l=1;l<=(j>>1);l++){
        for (int e=head[i*l];e;e=nex[e])
            if ((k|e)==k){
                if (dfs(i,e)&&dfs(i,k-e)){
                    f[i][k]=1;
                    return 1;
                }
            }
        }
    f[i][k]=0;
    return 0;
}
void work(int cas){
    int sum=0;
    for (int i=0;i<n;i++) sum+=a[i];
    if (sum!=x*y){
        printf("Case %d: No\n",cas);
        return;
    }
    init();
    preDeal();
    for (int k=0;k<n;k++)
        for (int i=1;i<=x;i++)
            if (a[k]%i==0)
                f[i][1<<k]=1;
    printf("Case %d: %s\n",cas,dfs(x,d)?"Yes":"No");
}
int main(){
    freopen("chocolate.in","r",stdin);
    freopen("chocolate.out","w",stdout);
    int cas=0;
    while (scanf("%d",&n)!=EOF&&n){
        scanf("%d%d",&x,&y);
        for (int i=0;i<n;i++) scanf("%d",&a[i]);
        work(++cas);
    }
    return 0;
}
