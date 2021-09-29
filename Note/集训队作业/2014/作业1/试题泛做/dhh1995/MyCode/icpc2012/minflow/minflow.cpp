#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1,_=n;i<=_;++i)
const int N=405,M=50005;
int Case,n,m,st,x[N],y[N],z[N],c[N],p[N],g[N],son[N],ed[M],next[M],f[M];
vector<int> q; double D[N][N],d[N],ans; bool b[N];
bool cmp(const int i,const int j){return z[i]==z[j]?i<j:z[i]<z[j];}
int sqr(int x){return x*x;}
int get(int x){return g[x]?g[x]=get(g[x]):x;}
int main()
{
	freopen("minflow.in","r",stdin);
	freopen("minflow.out","w",stdout);
	while (scanf("%d%d",&n,&m)!=EOF){
		ans=1e8,q.clear();
		rep(i,n) scanf("%d%d%d%d",x+i,y+i,z+i,c+i),p[i]=i,g[i]=son[i]=0,q.push_back(i);
		rep(i,n) rep(j,n) D[i][j]=c[i]&&c[j]?sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j])+0.):1e9;
		rep(i,m){scanf("%d%d",&st,ed+i); if (cmp(st,ed[i])) swap(st,ed[i]); next[i]=son[st],son[st]=i;}
		sort(p+1,p+n+1,cmp);
		rep(k,n+1){
			int i=p[k];
			if (z[i]>z[1] && z[i]>z[n] && z[p[k-1]]!=z[i] || k>n){
				int h=0,t=1; rep(j,n) d[j]=1e9; d[f[1]=get(1)]=c[get(1)]*.5;
				while (h<t){
					int x=f[++h]; b[x]=0; if (x==get(n)) continue;
					rep(j,q.size()){
						int y=q[j-1];
						if (c[y]+(get(n)==y)>1 && d[x]+D[x][y]+c[y]*.5-1<d[y]){
							d[y]=d[x]+D[x][y]+c[y]*.5-1;
							if (!b[y]) b[y]=1,f[++t]=y;
						}
					}
				}
				ans=min(ans,d[get(n)]);
			}
			if (k<=n) for (int p=son[i];p;p=next[p]){
				int j=get(ed[p]);
				if (j!=i){
					g[j]=i,c[i]+=c[j],q.erase(find(q.begin(),q.end(),j));
					rep(k,n) D[i][k]=D[k][i]=min(D[i][k],D[j][k]);
				}
			}
		}
		printf("Case %d: ",++Case); if (ans<1e8) printf("%.4lf\n",ans); else puts("impossible");
	}
	return 0;
}
