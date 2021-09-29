#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
double tmp;
#define double long double
const int N=205,M=50005; const double pi=acos(-1.),eps=1e-8;
int Case,n,e,next[M],ed[M],son[N],q[N][N],g[N],id[N]; double R,x,ans,v[M],w[N];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double operator /(const node &A){return fabs(A.x)<eps?y/A.y:x/A.x;}
	double angle(){return atan2(x,y);}//flip along y=x
	double len(){return sqrt(x*x+y*y);}
	void prt(){printf("%lf %lf\n",x,y);}
}a[N],b[N],d[N],U,V,A,B,C;
bool cmp(const int i,const int j){return w[i]>w[j];}
bool cross(node &A,node &B,int dir,double &C)
{
	double L=(B-A).len(); if (2*R<L) return 0;
	C=(B-A).angle()+acos(L/2/R)*dir; return 1;
}
void add(int x,int y,double z){q[x][y]=++e,ed[e]=y,v[e]=z,next[e]=son[x],son[x]=e;}
int main()
{
//	freopen("I.in","r",stdin);
//	freopen("I.out","w",stdout);
	while (scanf("%lf%d",&tmp,&n),R=tmp,ans=0,n*=2){
		e=0,--n; rep(i,n*2+1){son[i]=0; rep(j,2*n+1) q[i][j]=0;}
//					if (Case==605){printf("%lf %d\n",tmp=R,(n+1)/2);}
		rep(i,n){
			scanf("%lf",&tmp),x=tmp;
//					if (Case==605){printf("%lf\n",tmp);}
			if (i&1) d[i]=node(0,x),b[i]=a[i]+node(x>0?-R:R,0);
			else d[i]=node(x,0),b[i]=a[i]+node(0,R);
			a[i+1]=a[i]+d[i];
		}
		scanf("%*lf"),R+=1e-16;
//		if (n>9){++Case; continue;}
		rep(i,n){
			int t=0;
			rep(j,n) if ((i&1)!=(j&1)){
				node O(b[i&1?i:j].x,b[i&1?j:i].y); w[t]=(O-b[i])/d[i],g[t]=j;
				if (w[t]>-eps && w[t]<1+eps && (O-b[j])/d[j]>-eps && (O-b[j])/d[j]<1+eps) t++;
			}
			rep(j,n+1) if (i&1){
				double L=fabs(b[i].x-a[j].x); if (L>R) continue; L=sqrt(R*R-L*L)*((j>i)==(d[i].y>0)?-1:1);
				w[t]=(node(b[i].x,a[j].y+L)-b[i])/d[i],g[t]=n+j; if (w[t]>-eps && w[t]<1+eps) t++;
//				printf("%d %d %lf\n",i,j,L);
			}else{
				double L=fabs(b[i].y-a[j].y); if (L>R) continue; L=sqrt(R*R-L*L)*(j>i?-1:1);
				w[t]=(node(a[j].x+L,b[i].y)-b[i])/d[i],g[t]=n+j; if (w[t]>-eps && w[t]<1+eps) t++;
			}
			rep(j,t) id[j]=j; sort(id,id+t,cmp); rep(j,t) add(i,g[id[j]],w[id[j]]);
//			printf("i=%d	",i); rep(j,t) printf("%d ",g[id[j]]); puts("");
//			printf("i=%d	",i); rep(j,t) printf("%.2lf ",tmp=w[id[j]]); puts("");
		}
		rep(i,n+1){
			int t=0;
			rep(j,n) if (j&1){
				double L=b[j].x-a[i].x; if (fabs(L)>R) continue;
				w[t]=pi/2+acos(L/R)*((j<i)==(d[j].y<0)?-1:1),g[t]=j; if (q[j][n+i]) t++;
//				printf("%d %d %lf %d %d\n",i,j,tmp=acos(L/R)*((j<i)==(d[j].y<0)?-1:1),j<i,d[j].y<0);
			}else{
				double L=b[j].y-a[i].y; if (fabs(L)>R) continue;
				w[t]=acos(L/R)*(j<i?-1:1),g[t]=j; if (q[j][n+i]) t++;
			}
			rep(j,n+1) if (i!=j) if (cross(a[i],a[j],i<j?-1:1,w[t])) g[t++]=n+j;
			rep(j,t){id[j]=j; if (w[j]>pi) w[j]-=2*pi; if (w[j]<-pi) w[j]+=2*pi;}
			sort(id,id+t,cmp); rep(j,t) add(n+i,g[id[j]],w[id[j]]);
//			printf("i=%d	",n+i); rep(j,t) printf("%d ",g[id[j]]); puts("");
//			printf("i=%d	",n+i); rep(j,t) printf("%.2lf ",tmp=w[id[j]]); puts("");
		}
		int S=0,T,p=q[0][n];
		while (S!=2*n){
//			printf("%d %d\n",S%n,S/n);
			x=v[p]; while (v[p]-x<eps) p=next[p];
			T=ed[p],ans+=(v[p]-x)*(S<n?d[S].len():(R-1e-16)),p=q[T][S],S=T;
		}
		printf("Case %d: Distance = %.3lf\n\n",++Case,tmp=ans);
	}
	return 0;
}
