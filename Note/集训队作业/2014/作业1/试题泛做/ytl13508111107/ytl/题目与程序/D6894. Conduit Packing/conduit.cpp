//By ytl 2014-1-9
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int s[10],use[10],n,FLAG;
double a[10],f[10],R,MaxR;

const double EPS=1e-8,PI=acos(-1);
int dcmp(const double &a,double b=0){
    if (a-b>EPS) return 1;
    if (b-a>EPS) return -1;
    return 0;
}

double calc(double r1,double r2,double R){
    double a=R-r1,c=R-r2,b=r1+r2;
    return acos((a*a+c*c-b*b)/(2*a*c));
}
void check(){
    s[5]=s[1];
    for (int i=1;i<=5;i++){
        f[i]=0;
        for (int j=1;j<i;j++) if (!(i==5&&j==1)){
            if (dcmp(R-a[s[i]]-a[s[j]])<0) return;
            f[i]=max(f[i],f[j]+calc(a[s[i]],a[s[j]],R));
        }
    }    
    if (dcmp(f[5],2*PI)<=0) FLAG=1;
}
void search(int k){
    if (k==5){
        check();
        return;
    }
    for (int i=2;i<=4;i++) if (!FLAG&&!use[i]){
        use[i]=1;
        s[k]=i;
        search(k+1);
        use[i]=0;
    }
}
bool can(double _R){
    FLAG=0;
    R=_R;
    s[1]=1;
    use[1]=1;
    search(2);
    return FLAG;
}
int main(){
    freopen("conduit.in","r",stdin);
    freopen("conduit.out","w",stdout);
    int cas=0,x;
    while (scanf("%d",&x)!=EOF&&x){
        MaxR=x;
        a[1]=x/2.0;
        for (int i=2;i<=4;i++){
            scanf("%lf",&a[i]);
            MaxR=max(MaxR,a[i]);
            a[i]/=2;
        }
        double l=0,r=MaxR*2,mid;
        while (dcmp(l,r)<0){
            mid=(l+r)/2;
            if (can(mid)) r=mid;else l=mid;
        }
        printf("Case %d: %.lf\n",++cas,l*2+1e-8);
    }
    return 0;
}
