#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=51,M=N*N*N*N/4;
int n,m,ans,tot,l,Case,dep[N],fa[N],L[N],R[N],a[M],b[M],c[M],d[M],id[M];
int next[N*2],to[N*2],son[N],st[N],ed[N];
double D[N],t[M]; bool e[N][N];
struct vec{
	double x,y,z; vec(){}
	vec(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	vec operator -(const vec &A){return vec(x-A.x,y-A.y,z-A.z);}
	vec operator *(double A){return vec(x*A,y*A,z*A);}
	double operator *(const vec &A){return x*A.x+y*A.y+z*A.z;}
	double abs(){return sqrt(x*x+y*y+z*z);}
	void read(){scanf("%lf%lf%lf",&x,&y,&z);}
}p[N],v[N];
bool cmp(const int i,const int j){return t[i]<t[j];}
void dfs(int x,int fa,int d)
{
	L[x]=++tot,dep[x]=d;
	for (int p=son[x];p;p=next[p]) if (to[p]!=fa) dfs(to[p],x,d+1);
	R[x]=tot;
}
void addedge()
{
	rep(i,n) son[i]=0; l=0;
	rep(i,n-1){
		int x=st[i],y=ed[i];
		to[++l]=y,next[l]=son[x],son[x]=l;
		to[++l]=x,next[l]=son[y],son[y]=l;
		}
}
void prim(double t)
{
	rep(i,n) D[i]=(p[0]-p[i]).abs(),fa[i]=0; D[0]=-1;
	rep(i,n) rep(j,n) e[i][j]=0;
	rep(j,n-1){
		double opt=1e20; int k;
		rep(i,n) if (D[i]>=0 && D[i]<opt) opt=D[i],k=i;
		D[k]=-1; st[j]=k,ed[j]=fa[k]; if (st[j]>ed[j]) swap(st[j],ed[j]); e[st[j]][ed[j]]=1;
		rep(i,n) if (D[i]>=0)
			if ((p[k]-p[i]).abs()<D[i])
				D[i]=(p[k]-p[i]).abs(),fa[i]=k;
		}
	addedge(),tot=0,dfs(0,-1,0);
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
			rep(l,n) for (int k=0;k<l && k<=i;++k) if (k<i || l<j){
				V=v[k]-v[l],P=p[k]-p[l],g=f-vec(V*V,V*P*2,P*P);//g(A)=A.x*t^2+A.y*t+A.z	<0
				if (abs(g.x)<1e-8){
					if (g.y>0) a[m]=i,b[m]=j,c[m]=k,d[m]=l,t[m++]=-g.z/g.y;
					else if (g.y<0) a[m]=k,b[m]=l,c[m]=i,d[m]=j,t[m++]=-g.z/g.y;
					if (m && t[m-1]<1e-8) --m;
				}else{
					double delta=g.y*g.y-4.*g.x*g.z; if (delta<0) continue; delta=sqrt(delta);
					if ((-g.y+delta)/2/g.x>1e-8) a[m]=i,b[m]=j,c[m]=k,d[m]=l,t[m++]=(-g.y+delta)/2/g.x;
					if ((-g.y-delta)/2/g.x>1e-8) a[m]=k,b[m]=l,c[m]=i,d[m]=j,t[m++]=(-g.y-delta)/2/g.x;
				}
			}
		}
		prim(0); rep(i,m) id[i]=i; sort(id,id+m,cmp);
		rep(k,m) if (t[id[k]]>1e-8){
			int i=id[k];	//c[i],d[i] try to replace a[i],b[i]
			if (e[a[i]][b[i]] && onPath(a[i],b[i],c[i],d[i])){
				swap(e[a[i]][b[i]],e[c[i]][d[i]]); 
				rep(j,n-1) if (a[i]==st[j] && b[i]==ed[j]){st[j]=c[i],ed[j]=d[i]; break;}
				addedge(),tot=0,dfs(0,-1,0),++ans;
			}
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
