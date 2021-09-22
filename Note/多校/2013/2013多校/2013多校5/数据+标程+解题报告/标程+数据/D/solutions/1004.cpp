#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,p[100],e[100],tot,N,ans,_;
void dfs(int dep,int d,int mu) {
    if (dep==tot) {
        int c=(d%3)*(n%3)%3*d;
        if ((n+3)/2<c) return;
        int r=(n+3)/2-c;
        ans+=mu*(r/3/d+1);
    } else {
        dfs(dep+1,d,mu);
        dfs(dep+1,d*p[dep],-mu);
    }
}
int main() {
//	freopen("1004.in","r",stdin);
//	freopen("10040.out","w",stdout);
    for (scanf("%d",&_);_;_--) {
        scanf("%d",&n);
        if (n%2==0||n%3==0) { puts("0");continue;}
        tot=0;
        N=n;n=(n+3)/2;
        for (int i=2;i*i<=n;i++) if (n%i==0) {
            p[tot]=i;
            e[tot]=0;
            while (n%i==0) n/=i,e[tot]++;
            ++tot;
        }
        if (n!=1) { p[tot]=n,e[tot]=1;tot++;}
        n=N;
        ans=0;
        dfs(0,1,1);
        printf("%d\n",ans);
    }
}
