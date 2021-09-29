#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define rep2(i,n) for (int i=0;i<n;i+=2)
const int N=405; const double eps=1e-8;
int Case,n,D,U,H,T,x[N],y[N],z[N],p[N],m[N],id[N][N],f[N*N];
double ans,k[N],b[N],u[N][N],d[N][N]; bool g[N*N];
bool cmp(const int i,const int j){return y[i]<y[j];}
bool in(int y1,int y2,double h){if (y1>y2) swap(y1,y2); return y1<h && h<y2;}
int get(int x){return f[x]?f[x]=get(f[x]):x;}
void work(int h1,int h2)
{
	++H,D=U=0;
	rep(i,n) if (y[i+1]!=y[i] && in(y[i],y[i+1],(h1+h2)/2.))
		d[H][D++]=k[i]*h1+b[i],u[H][U++]=k[i]*h2+b[i];
	sort(d[H],d[H]+D),sort(u[H],u[H]+U),m[H]=D;
	rep2(i,D) id[H][i]=id[H][i^1]=++T,f[T]=g[T]=0;
	rep(i,n) if (y[i]==h1 && z[i])
		rep2(j,D) if (d[H][j]<x[i]+eps && x[i]<d[H][j^1]+eps) g[id[H][j]]=1;
	rep2(i,m[H]) rep2(j,m[H-1]) if (u[H-1][j]<d[H][i^1] && d[H][i]<u[H-1][j^1]){
		int x=id[H][i],y=get(id[H-1][j]); g[get(x)]|=g[x],x=get(x),g[y]|=g[x],f[x]=y;
	}
	rep2(i,D) if (!g[get(id[H][i])])
		ans+=(d[H][i^1]-d[H][i]+u[H][i^1]-u[H][i])*(h2-h1);
	rep(i,n) if (y[i]==h2 && z[i])
		rep2(j,U) if (u[H][j]<x[i]+eps && x[i]<u[H][j^1]+eps) g[get(id[H][j])]=1;
}
int main()
{
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	while (scanf("%d",&n)!=EOF && n){
		rep(i,n) scanf("%d%d%d",x+i,y+i,z+i),p[i]=i; x[n]=*x,y[n]=*y,ans=T=H=0; sort(p,p+n,cmp);
		rep(i,n) if (y[i+1]!=y[i]) k[i]=(x[i+1]-x[i])/(0.+y[i+1]-y[i]),b[i]=x[i]-k[i]*y[i];
		rep(i,n) if (i && y[p[i]]!=y[p[i-1]]) work(y[p[i-1]],y[p[i]]);
		printf("Cave %d: Oil capacity = %.0lf\n\n",++Case,ans/2+eps);
	}
	return 0;
}
