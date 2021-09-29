//By ytl 2013-12-17
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 105
#define H 50
using namespace std;

const double 
    VCRUSITE=400,
    AOPT=30,
    GPHOPT=2000,
    GPHEXTRA=10,
    CLIMBCOST=50;

const double EPS=1e-6;
int dcmp(const double &a,double b=0){
    if (a-b>EPS) return 1;
    if (b-a>EPS) return -1;
    return 0;
}
const double MAXV=1e100;
double f[N][H],w[N][H],A[N],B[N],C[N];
int an[N],g[N][H];
double calc(double A,double B,double C,double h){
    double v=VCRUSITE+B+(C-B)/20*(h-20);
    if (dcmp(v)>0){
        return (GPHOPT+fabs(AOPT-h)*GPHEXTRA)*(A/v);
    }else{
        return MAXV;
    }
}
void work(int cas){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lf%lf%lf",&A[i],&B[i],&C[i]);
    for (int i=1;i<=n;i++)
        for (int h=20;h<=40;h++){
            w[i][h]=calc(A[i],B[i],C[i],h);
        }
    for (int i=1;i<n;i++)
        for (int h=20;h<=40;h++)
            f[i][h]=MAXV;
    for (int h=20;h<=40;h++) f[n][h]=w[n][h];
    for (int i=n-1;i>=1;i--)
        for (int h1=20;h1<=40;h1++)
            for (int h2=20;h2<=40;h2++){
                double oil=w[i][h1]+CLIMBCOST*max(0,h2-h1)+f[i+1][h2];
                if (dcmp(oil,f[i][h1])<0){
                    f[i][h1]=oil;
                    g[i][h1]=h2;
                }
            }
    for (int i=20;i<=40;i++) f[1][i]+=i*CLIMBCOST;
    double ans=MAXV;int p=0;
    for (int i=20;i<=40;i++){
        if (dcmp(f[1][i],ans)<0){
            ans=f[1][i];
            p=i;
        }
    }    
    printf("Flight %d:",cas);
    for (int i=1;i<=n;i++){
        printf(" %d",p);
        p=g[i][p];
    }
    printf(" %.lf\n",ceil(ans));
}
int main(){
    freopen("flight.in","r",stdin);
    freopen("flight.out","w",stdout);
    int tt=0;
    scanf("%d",&tt);
    for (int cas=1;cas<=tt;cas++) work(cas);
    return 0;
}
