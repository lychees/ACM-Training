//By ytl 2014-1-6
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define N 205
#define M 25
using namespace std;

const int INF=0x7fffffff/3;

int n,m,po,lineTot,p1,p2;
int line[M],dis[N][M],use[N][M],fa[N][M],fb[N][M],choose[N][M];
map<int,int> my;
vector<int> start[N];

struct data{
    int a,b;
    data(int a=0,int b=0):a(a),b(b){};
}Q[N*M];
struct tic{
    int tot,cost;
    int a[M];    
}ticket[M];
void spfa(){
    Q[1]=data(line[1],1);
    for (int i=1;i<=po;i++)
        for (int j=1;j<=lineTot;j++)
            dis[i][j]=INF;
    dis[line[1]][1]=0;
    for (p1=1,p2=1;p1<=p2;p1++){
        int a=Q[p1].a,b=Q[p1].b;
        use[a][b]=0;
        for (int i=0;i<(int)start[a].size();i++){
            int k=start[a][i];
            int nb=b;
            for (int j=2;j<=ticket[k].tot;j++){
                int na=ticket[k].a[j];
                if (line[nb+1]==na) nb++;
                if (dis[a][b]+ticket[k].cost<dis[na][nb]){
                    dis[na][nb]=dis[a][b]+ticket[k].cost;
                    choose[na][nb]=k;
                    fa[na][nb]=a;
                    fb[na][nb]=b;
                    if (!use[na][nb]){
                        use[na][nb]=1;
                        Q[++p2]=data(na,nb);
                    }
                }
            }
        }    
    }
}
void printWay(int a,int b){
    if (a==line[1]&&b==1) return;
    printWay(fa[a][b],fb[a][b]);
    printf(" %d",choose[a][b]);
}
void output(int cas,int a){
    printf("Case %d, Trip %d: Cost = %d\n",cas,a,dis[line[lineTot]][lineTot]);
    printf("  Tickets used:");
    printWay(line[lineTot],lineTot);
    printf("\n");
}
void work(int cas,int a){
    spfa();
    output(cas,a);
}
void init(){
    for (int i=1;i<=po;i++) start[i].clear();
    po=0;
    my.clear();
}
int getID(int x){
    if (my.find(x)!=my.end()) return my[x];
    my[x]=++po;
    return po;
}
int main(){
    freopen("low.in","r",stdin);
    freopen("low.out","w",stdout);
    int cas=0;
    while (scanf("%d",&n)!=EOF&&n){
        cas++;
        init();
        for (int i=1;i<=n;i++){
            scanf("%d%d",&ticket[i].cost,&ticket[i].tot);
            for (int j=1;j<=ticket[i].tot;j++){
                int x;
                scanf("%d",&x);
                ticket[i].a[j]=getID(x);
            }
            start[ticket[i].a[1]].push_back(i);
        }
        scanf("%d",&m);
        for (int i=1;i<=m;i++){
            scanf("%d",&lineTot);
            for (int j=1;j<=lineTot;j++){
                scanf("%d",&line[j]);
                line[j]=getID(line[j]);
            }
            work(cas,i);
        }
    }
    return 0;
}

