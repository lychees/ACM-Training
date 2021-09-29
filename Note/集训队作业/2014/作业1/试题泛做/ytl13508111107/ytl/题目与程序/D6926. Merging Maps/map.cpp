//By ytl 2014-1-14
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 205
#define M 25
using namespace std;

int n,tot;
int use[M];
char str[2000];
struct data{
    int n,m;
    char a[N][N];
    void input(){
        scanf("%d%d\n",&n,&m);
        for (int i=1;i<=n;i++){
            gets(str+1);
           // printf("%s\n",str+1);
            for (int j=1;j<=m;j++)
                a[i][j]=str[j];
        }
    }
    void print(){
        printf("    +");for (int i=1;i<=m;i++) printf("-");printf("+\n");
        for (int i=1;i<=n;i++){
            printf("    |");
            for (int j=1;j<=m;j++) printf("%c",a[i][j]);
            printf("|\n");
        }
        printf("    +");for (int i=1;i<=m;i++) printf("-");printf("+\n");
    }
}map[M],temp;

struct dat{
    int score,r,c;
    dat(int score=0,int r=0,int c=0):score(score),r(r),c(c){};
}my[M][M];

void init(){
    memset(my,0,sizeof(my));
    memset(use,0,sizeof(use));
}
void print(int a[],int tot){
    for (int i=1;i<=tot;i++) printf("%d ",a[i]);
    printf("\n");
}
int join(const data &a,const data &b,int R,int C,data &c){
    int score=0,xa,xb,ya,yb;
    if (R<0) c.n=max(a.n-R,b.n);else c.n=max(a.n,R+b.n);
    if (C<0) c.m=max(a.m-C,b.m);else c.m=max(a.m,C+b.m);
    if (R<0){
        xb=1;
        xa=xb-R;
    }else{
        xa=1;
        xb=xa+R;
    }
    if (C<0){
        yb=1;
        ya=yb-C;
    }else{
        ya=1;
        yb=ya+C;
    }
    for (int i=1;i<=c.n;i++)
        for (int j=1;j<=c.m;j++)
            c.a[i][j]='-';
    for (int i=1,i1=xa;i<=a.n;i++,i1++)
        for (int j=1,j1=ya;j<=a.m;j++,j1++)
            c.a[i1][j1]=a.a[i][j];
    for (int i=1,i1=xb;i<=b.n;i++,i1++)
        for (int j=1,j1=yb;j<=b.m;j++,j1++)
            if (b.a[i][j]!='-'){
                if (c.a[i1][j1]=='-'){
                    c.a[i1][j1]=b.a[i][j];
                }else{
                    if (c.a[i1][j1]!=b.a[i][j]){
                        return 0;
                    }else score++;
                }
            }
    return score;
}
dat join(const data &a,const data &b,data &c){
    dat best(0,0,0);
    for (int r=-b.n+1;r<=a.n-1;r++)
        for (int c=-b.m+1;c<=a.m-1;c++){
            int score=join(a,b,r,c,temp);
            if (score>best.score) best=dat(score,r,c);
        }
    if (best.score) join(a,b,best.r,best.c,c);
    return best;
}
void updata(int i,int j,dat &bt,int &bi,int &bj){
    if (my[i][j].score>bt.score){
        bt=my[i][j];
        bi=i;
        bj=j;
    }
}
void choose(dat &bt,int &bi,int &bj){
    bt=dat(0,0,0);bi=bj=0;
    for (int i=1;i<=tot;i++) if (!use[i])
        for (int j=i+1;j<=tot;j++) if (!use[j])
            updata(i,j,bt,bi,bj);
}
void DEBUG(int a,int b,int c,int R,int C,int score){
    map[a].print();
    printf("and\n");
    map[b].print();
    printf("==>\n");
    map[c].print();
    printf(":%d %d %d\n",R,C,score);
    printf("\n");
}

void work(int cas){
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            my[i][j]=join(map[i],map[j],temp);
    tot=n;
    dat bt;int bi,bj;
    for (int k=1;k<n;k++){
        choose(bt,bi,bj);
        if (bt.score==0) break;
        use[bi]=1;use[bj]=1;
        join(map[bi],map[bj],bt.r,bt.c,map[++tot]);
        for (int i=1;i<tot;i++) if (!use[i])
            my[i][tot]=join(map[i],map[tot],temp);
    }
    printf("Case %d\n",cas);
    int t=0;
    for (int i=1;i<=tot;i++) if (!use[i]){
        if (t) printf("\n");
        printf("    MAP %d:\n",i);
        map[i].print();
        t=1;
    }
}
int main(){
    freopen("map.in","r",stdin);
    freopen("map.out","w",stdout);
    int cas=0;
    while (scanf("%d\n",&n)!=EOF&&n){
        if (cas) printf("\n");
        for (int i=1;i<=n;i++) map[i].input();
        init();
        work(++cas);
    }
    return 0;
}
