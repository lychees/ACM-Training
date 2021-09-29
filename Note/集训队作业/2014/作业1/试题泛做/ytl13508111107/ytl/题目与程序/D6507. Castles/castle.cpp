//By ytl 2014-1-14
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 105
using namespace std;

const int INF=0x7fffffff/3;

int n,tot;
int f[N],g[N],ys[N],w[N],v[N];

bool cmp(int a,int b){
    return f[a]-g[a]<f[b]-g[b];
}
namespace Graph{
    int head[N],gt=1;
    struct Rec{int go,nex;}eg[N*2];
    void build(int a,int b){ 
        eg[++gt]=(Rec){b,head[a]};
        head[a]=gt;
    }
}
using namespace Graph;


void search(int p,int tfa){
    g[p]=v[p];
    for (int i=head[p];i;i=eg[i].nex) if (eg[i].go!=tfa){
        search(eg[i].go,p);
        g[p]+=g[eg[i].go];     
    }
    tot=0;
    for (int i=head[p];i;i=eg[i].nex) if (eg[i].go!=tfa)
        ys[++tot]=eg[i].go;
    sort(ys+1,ys+tot+1,cmp);
    f[p]=0;
    for (int i=1;i<=tot;i++){
        f[p]=max(f[ys[i]],f[p]+g[ys[i]]);
    }
    f[p]=max(w[p],f[p]+v[p]);
}
void print(int a[],int n){
    for (int i=1;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
}
int main(){
    freopen("castle.in","r",stdin);
    freopen("castle.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        w[i]=a;v[i]=b+c;
    }
    for (int i=1;i<=n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        build(a,b);
        build(b,a);
    }
    int ans=INF;
    for (int root=1;root<=n;root++){
        search(root,-1);
        ans=min(ans,f[root]);
    }
    printf("%d\n",ans);
    return 0;
}
