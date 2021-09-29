//By ytl 2014-1-9
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 10
#define M 1005
using namespace std;

const int INF=0x7fffffff/3;

int n,m,ans;
int w[N],tot[N],use[N],rec[N][M];
struct bg{
    int id,team,num,begin,end;
}bag[M];
bool cmp(const bg &a,const bg &b){
    return a.team<b.team||(a.team==b.team&&a.begin<b.begin);
}
bool cmpID(const bg &a,const bg &b){
    return a.id<b.id;
}
int getAns(){
    int now=1,memory=0,most=0;
    for (int i=1;i<=n;i++){
        int k=w[i];
        for (int j=1;j<=tot[k];j++){
            if (rec[k][j]){
                memory-=rec[k][j];
                continue;
            }
            if (bag[now].team==k&&bag[now].num==j){
                now++;
                continue;
            }
            while (!(bag[now].team==k&&bag[now].num==j)){
                rec[bag[now].team][bag[now].num]=bag[now].end-bag[now].begin+1;
                memory+=bag[now].end-bag[now].begin+1;
                now++;
            }
            now++;
            most=max(most,memory);
        }
    }
    for (int i=1;i<=m;i++) rec[bag[i].team][bag[i].num]=0;
    return most;
}
void search(int k){
    if (k==n+1){
        ans=min(ans,getAns());
        return;
    }
    for (int i=1;i<=n;i++) if (!use[i]){
        use[i]=1;
        w[k]=i;
        search(k+1);
        use[i]=0;
    }
}
void init(){
    ans=INF;
    for (int i=1;i<=n;i++) tot[i]=0;
    sort(bag+1,bag+m+1,cmp);
    for (int i=1;i<=m;i++){
        if (bag[i].begin==1){
            bag[i].num=1;
            tot[bag[i].team]=1;
        }else{
            bag[i].num=bag[i-1].num+1;
            tot[bag[i].team]++;
        }
    }
    sort(bag+1,bag+m+1,cmpID);
}
int main(){
    freopen("network.in","r",stdin);
    freopen("network.out","w",stdout);
    int cas=0;
    while (scanf("%d%d",&n,&m)!=EOF&&(n||m)){
        if (cas) printf("\n");
        int x;for (int i=1;i<=n;i++) scanf("%d",&x);
        for (int i=1;i<=m;i++){
            scanf("%d%d%d",&bag[i].team,&bag[i].begin,&bag[i].end);
            bag[i].id=i;
        }
        init();
        search(1);
        printf("Case %d: %d\n",++cas,ans);
    }
    return 0;   
}
