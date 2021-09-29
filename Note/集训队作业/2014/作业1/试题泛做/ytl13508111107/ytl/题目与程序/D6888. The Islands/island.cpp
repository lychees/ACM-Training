//By ytl 2014-1-13
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#define N 105
using namespace std;

const double MAXV=1e100;

int n;
double f[N][N],w[N][N],ans1,ans2;
int reca[N],recb[N],an1[N],an2[N],g[N][N];

inline double sqr(double a){return a*a;}
struct Point{
    double x,y;int id;
    void read(){
        scanf("%lf%lf",&x,&y);
    }
    double dis(const Point &A){
        return sqrt(sqr(A.x-x)+sqr(A.y-y));
    }
}p[N];
void getWay(int ans[]){
    int a=n,b=n+1,tot1=0,tot2=0;
    while (!(a==2&&b==1)){
        int x=g[a][b];
        if (x>0){
            reca[++tot1]=a;
            a=x;
        }else{
            recb[++tot2]=b;
            b=-x;
        }
    }
    reca[++tot1]=2;   
    ans[0]=0;
    ans[++ans[0]]=0;
    for (int i=tot1;i>=1;i--) ans[++ans[0]]=reca[i]-1;
    for (int i=2;i<=tot2;i++) ans[++ans[0]]=recb[i]-1;
    ans[++ans[0]]=0;
}
void DP(double &ans,int an[]){
    for (int i=1;i<=n+1;i++)
        for (int j=1;j<=n+1;j++)
            f[i][j]=MAXV;
    if (p[2].id!=2) f[2][1]=w[1][2];else return;
    for (int i=1;i<=n+1;i++)
        for (int j=1;j<=n+1;j++){
            int a=max(i,j)+1;
            if (p[a].id!=2){
                double x=f[i][j]+w[i][a];
                if (x<f[a][j]){
                    f[a][j]=x;
                    g[a][j]=i;
                }
            }
            if (p[a].id!=3){
                double x=f[i][j]+w[j][a];
                if (x<f[i][a]){
                    f[i][a]=x;
                    g[i][a]=-j;
                }
            }
        }    
    ans=f[n][n+1];
    //exit(0);
    getWay(an);
}
void print(int a[],int n){
    for (int i=1;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
}
int main(){
    freopen("island.in","r",stdin);
    freopen("island.out","w",stdout);
    int cas=0,b1,b2;
    while (scanf("%d%d%d",&n,&b1,&b2)!=EOF&&(n||b1||b2)){
        b1++;b2++;
        for (int i=1;i<=n;i++) p[i].read();
        p[n+1]=p[n];
        for (int i=1;i<=n+1;i++) p[i].id=1;
        for (int i=1;i<=n+1;i++)
            for (int j=i+1;j<=n+1;j++)
                w[i][j]=p[i].dis(p[j]);
        p[b1].id=2;
        p[b2].id=3;
        ans1=ans2=MAXV;
        DP(ans1,an1);
        p[b1].id=3;
        p[b2].id=2;
        DP(ans2,an2);
        printf("Case %d: %.2lf\n",++cas,min(ans1,ans2));
        if (ans1<ans2){
            print(an1,an1[0]);
        }else{
            print(an2,an2[0]);
        }
    }
    return 0;
}
