#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=305; const double eps=1e-8;
int Case,n,m,x,y,l,son[N],ed[N],next[N]; double w[N][3],a[N][N],g[N][N];
bool solve()
{
    memcpy(g,a,sizeof(g));
    rep(i,n) {
        if (i<m) for (int j=i+1;fabs(g[i][i])<eps && j<n;++j) if (fabs(g[j][i])>eps)
            for (int k=i;k<=m;++k) swap(g[i][k],g[j][k]);
        if (fabs(g[i][i])<eps){if (fabs(g[i][m])>eps) return 0; continue;}
        for (int k=m;k>=i;--k) g[i][k]/=g[i][i];
        if (i<m) rep(j,n) if (i!=j && fabs(g[j][i])>eps)
            for (int k=m;k>=i;--k) g[j][k]-=g[j][i]*g[i][k];
    }
//  rep(i,n){rep(k,m+1) printf("%.2lf ",g[i][k]); puts("");} puts("");
    return 1;
}
int main()
{
    while (scanf("%d%d",&n,&m),n||m){
        rep(i,n){son[i]=-1; rep(j,3) scanf("%lf",w[i]+j);} l=0;
        rep(i,m) scanf("%d%d",&x,&y),--x,--y,
            ed[l]=y,next[l]=son[x],son[x]=l++,
            ed[l]=x,next[l]=son[y],son[y]=l++;
        rep(i,n) rep(j,3){
            x=i*3+j; rep(k,m+1) a[x][k]=0;
            if (w[i][2]>eps){
                if (j==2) a[x][m]=1;
                for (int p=son[i];p>=0;p=next[p]) a[x][p>>1]=w[ed[p]][j]-w[i][j];
            }
        }
        n*=3,printf("Sculpture %d: ",++Case);
        if (!solve()) puts("NON-STATIC");
        else{rep(i,n) if (w[i/3][2]) a[i][m]=sin(i); puts(solve()?"STABLE":"UNSTABLE");}
    }
    return 0;
}
