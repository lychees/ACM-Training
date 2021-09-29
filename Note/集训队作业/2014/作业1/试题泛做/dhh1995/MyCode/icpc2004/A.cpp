#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=105,u[]={1,0,-1,0},v[]={0,1,0,-1};
int Case,_,E,T,n,m,w,D,h,t,x,y,tx,ty,r[N*2][N*2],d[N*2][N*2],f[N],o[N],b[N*2][N*2];
struct ant{
	int x,y,L,D,R,W;
	void init(){x=y=N,L=W=0,D=d[x][y],R=r[x+u[D]][y+v[D]],b[x][y]|=1<<D;}
	void move(){
		if (b[x+u[D]][y+v[D]]>>d[x+u[D]][y+v[D]]&1) ++W;
		else b[x][y]^=1<<D,x+=u[D],y+=v[D],++L,W=0,D=d[x][y],R=r[x+u[D]][y+v[D]],b[x][y]^=1<<D;
	}
	bool operator <(const ant &A) const{return R==A.R?W==A.W?L>A.L:W>A.W:R>A.R;}
}a[N];
bool cmp(const int i,const int j){return a[i]<a[j];}
void work(bool flag)
{
	if (h<t) sort(f+h,f+t,cmp); for (int i=h;i<t;++i) a[f[i]].move();
	if (!b[N][N] && T>t*w && t<m) f[t]=t,a[t++].init();
	if (h<t && flag && b[x][y]){b[x][y]=0; if (f[h]) o[++*o]=f[h]; ++h;}
}
int main()
{
	for (scanf("%d",&_);_--;){
		scanf("%d%d%d",&n,&m,&w),h=t=T=*o=0,x=y=N,r[x][y]=0;
		rep(k,n){
			scanf("%d%d",&tx,&ty),tx+=N,ty+=N,D=x==tx?y<ty?1:3:x<tx?0:2;
			while (x+y!=tx+ty) d[x][y]=D,x+=u[D],y+=v[D],r[x][y]=++T,work(0);
		}
		if (Case) puts(""); printf("Case %d:\n",++Case);
		printf("Carl finished the path at time %d\n",T+1);
		while (h<m) ++T,work(1);
		printf("The ants finished in the following order:\n0");
		rep(i,*o) printf(" %d",o[i]);
		printf("\nThe last ant finished the path at time %d\n",T);
	}
	return 0;
}
