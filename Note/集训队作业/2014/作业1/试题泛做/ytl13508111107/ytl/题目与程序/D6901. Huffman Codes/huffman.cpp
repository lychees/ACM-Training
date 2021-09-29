//By ytl 2014-1-9
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 105
using namespace std;

int n,po,root=1;
int ls[N],rs[N],fa[N],ff[N],ys[N],Q[N],val[2][30005][N];

char str[N];
void build(char str[],int len){
    int p=root;
    for (int i=0;i<len;i++){
        if (str[i]=='0'){
            if (!ls[p]) {ls[p]=++po;fa[po]=p;}
            p=ls[p];
        }else{
            if (!rs[p]) {rs[p]=++po;fa[po]=p;}
            p=rs[p];
        }
    }
}
void init(){
    for (int i=1;i<=po;i++) ls[i]=rs[i]=0;
    po=1;
}
void bfs(){
    Q[1]=root;
    for (int p1=1,p2=1;p1<=p2;p1++){
        int u=Q[p1];
        if (rs[u]) Q[++p2]=rs[u];
        if (ls[u]) Q[++p2]=ls[u];
    }
    for (int i=1;i<=po;i++) ys[Q[i]]=i;
    for (int i=1;i<=po;i++){
        ff[ys[i]]=ys[fa[i]];
    }
    for (int i=1;i<=po;i++) fa[i]=ff[i];
}
int main(){
    freopen("huffman.in","r",stdin);
    freopen("huffman.out","w",stdout);
    int cas=0;
    while (scanf("%d",&n)!=EOF&&n){
        init();
        for (int i=1;i<=n;i++){
            scanf("%s",str);
            int len=strlen(str);
            build(str,len);
        }
        bfs();
        val[0][1][1]=100;int tot=1;int x=0;
        for (int i=2;i+1<=po;i+=2){
            x^=1;
            int a=i,b=i+1;
            int u=fa[a];
            int tt=tot;tot=0;
            for (int j=1;j<=tt;j++){
                int lim=val[x^1][j][u]-val[x^1][j][u]/2;
                for (int k=val[x^1][j][i-1];k>=lim;k--) if (val[x^1][j][u]-k>0){
                    tot++;
                    for (int y=1;y<i;y++) val[x][tot][y]=val[x^1][j][y];
                    val[x][tot][a]=k;
                    val[x][tot][b]=val[x^1][j][u]-k;
                }
            }
        }
        printf("Case %d: %d\n",++cas,tot);
    }
    return 0;
}
