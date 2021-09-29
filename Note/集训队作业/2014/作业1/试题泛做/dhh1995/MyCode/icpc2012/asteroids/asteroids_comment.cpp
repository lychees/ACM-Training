#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=51,M=N*N*N*N/4;
int n,m,ans,tot,Case,dep[N],fa[N],L[N],R[N],a[M],b[M],c[M],d[M],id[M];
double D[N],t[M]; bool e[N][N];
struct vec{
	double x,y,z; vec(){}
	vec(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	vec operator -(const vec &A){return vec(x-A.x,y-A.y,z-A.z);}
	vec operator *(double A){return vec(x*A,y*A,z*A);}
	double operator *(const vec &A){return x*A.x+y*A.y+z*A.z;}
	double abs(){return sqrt(x*x+y*y+z*z);}
	void read(){scanf("%lf%lf%lf",&x,&y,&z);}
	void prt(){printf("%lf %lf %lf\n",x,y,z);}
}p[N],v[N];
bool cmp(const int i,const int j){return t[i]<t[j];}
void dfs(int x,int fa,int d)
{
	L[x]=++tot,dep[x]=d;
	rep(y,n) if (e[x][y] && y!=fa) dfs(y,x,d+1);
	R[x]=tot;
}
void prim(double t)
{
	t+=1e-8;
	rep(i,n) D[i]=(p[0]-p[i]-(v[i]-v[0])*t).abs(),fa[i]=0; D[0]=-1;
	rep(i,n) rep(j,n) e[i][j]=0;
	rep(j,n-1){
		double opt=1e20; int k;
		rep(i,n) if (D[i]>=0 && D[i]<opt) opt=D[i],k=i;
//		printf("%d %d\n",j,k);
		D[k]=-1; e[k][fa[k]]=e[fa[k]][k]=1;
		rep(i,n) if (D[i]>=0)
			if ((p[k]-p[i]-(v[i]-v[k])*t).abs()<D[i])
				D[i]=(p[k]-p[i]-(v[i]-v[k])*t).abs(),fa[i]=k;
		}
//	printf("%lf\n",t);
//	rep(i,n){rep(j,n) printf("%d",e[i][j]); puts("");} puts("");
	tot=0,dfs(0,-1,0);
}
bool onPath(int a,int b,int c,int d)
{
	if (dep[a]<dep[b]) swap(a,b);
	return (L[a]<=L[c] && L[c]<=R[a])!=(L[a]<=L[d] && L[d]<=R[a]);
}
int main()
{
	freopen("asteroids.in","r",stdin);
	freopen("asteroids.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		rep(i,n) p[i].read(),v[i].read(); m=0,ans=1;
		rep(j,n) rep(i,j){
			vec V=v[i]-v[j],P=p[i]-p[j],f=vec(V*V,V*P*2,P*P),g;
//			puts("f");f.prt();
			rep(l,n) for (int k=0;k<l && k<=i;++k) if (k<i || l<j){
				V=v[k]-v[l],P=p[k]-p[l],g=f-vec(V*V,V*P*2,P*P);//g(A)=A.x*t^2+A.y*t+A.z
//				puts("g"),g.prt();
				if (abs(g.x)<1e-8){
					if (g.y>0) a[m]=i,b[m]=j,c[m]=k,d[m]=l,t[m++]=-g.z/g.y;
//					printf("%d %d %d %d %lf\n",i,j,k,l,t[m-1]);
					else if (g.y<0) a[m]=k,b[m]=l,c[m]=i,d[m]=j,t[m++]=-g.z/g.y;
//					printf("%d %d %d %d %lf\n",k,l,i,j,t[m-1]);
				}else{
					double delta=g.y*g.y-4.*g.x*g.z; if (delta<0) continue; delta=sqrt(delta);
					a[m]=i,b[m]=j,c[m]=k,d[m]=l,t[m++]=(-g.y+delta)/2/g.x;
					a[m]=k,b[m]=l,c[m]=i,d[m]=j,t[m++]=(-g.y-delta)/2/g.x;
					//if (g.x>0) swap(t[m-2],t[m-1]);
//					printf("%d %d %d %d %lf %lf\n",i,j,k,l,t[m-2],t[m-1]);
				}
			}
		}
		prim(0); rep(i,m) id[i]=i; sort(id,id+m,cmp);
		rep(k,m) if (t[id[k]]>1e-8){
			int i=id[k];	//c[i],d[i] try to replace a[i],b[i]
//			printf("%lf %d %d %d %d  %d\n",t[i],a[i],b[i],c[i],d[i],e[a[i]][b[i]]);
			if (e[a[i]][b[i]] && onPath(a[i],b[i],c[i],d[i])) prim(t[i]),++ans;
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
