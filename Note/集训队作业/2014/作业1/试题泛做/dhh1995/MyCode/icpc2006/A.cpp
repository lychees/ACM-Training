#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=205,inf=1<<28;
int Case,p,Q,n,z,c[25],a[25][15],e[15],f[15][N],g[15][N],h[15][N]; bool b[N]; map<int,int> H;
int get(){scanf("%d",&z); if (H.find(z)==H.end()) H[z]=++n; return H[z];}
void prt(int i,int j){if (i>1 || j!=e[1]) prt(h[i][j],a[g[i][j]][1]),printf(" %d",g[i][j]);}
int main()
{
	while (++Case,n=0,H.clear(),scanf("%d",&p),p){
		rep(i,p){scanf("%d%d",c+i,a[i]); rep(j,*a[i]) a[i][j]=get();}
		scanf("%d",&Q);
		rep(q,Q){
			scanf("%d",e); rep(j,*e) e[j]=get();
			rep(i,*e) rep(j,n) f[i][j]=inf; f[1][e[1]]=0;
			rep(i,*e-1){
				rep(j,n) b[j]=1;
				rep(t,n){
					int j=-1,D=inf;
					rep(k,n) if (b[k] && f[i][k]<D) D=f[i][k],j=k;
					if (j<0) break; b[j]=0;
					rep(l,p) if (a[l][1]==j){
						int w=i;
						rep(k,*a[l]){
							int x=a[l][k]; if (w<*e && x==e[w+1]) ++w;
							if (D+c[l]<f[w][x]) f[w][x]=D+c[l],g[w][x]=l,h[w][x]=i;
						}
					}
				}
			}
			printf("Case %d, Trip %d: Cost = %d\n  Tickets used:",Case,q,f[*e][e[*e]]);
			prt(*e,e[*e]),puts("");
		}
	}
	return 0;
}
