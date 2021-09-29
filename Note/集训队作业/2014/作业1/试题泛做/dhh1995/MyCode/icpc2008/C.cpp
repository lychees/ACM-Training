#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double pi=acos(-1.),eps=1e-10;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A) const{return node(x+A.x,y+A.y);}
	node operator -(const node &A) const{return node(x-A.x,y-A.y);}
	node operator *(const double &A) const{return node(x*A,y*A);}
	node operator /(const double &A) const{return node(x/A,y/A);}
	node operator *(const node &A) const{return node(x*A.x-y*A.y,x*A.y+y*A.x);}
	double operator &(const node &A) const{return x*A.x+y*A.y;}
	double operator ^(const node &A) const{return x*A.y-y*A.x;}
	double len(){return sqrt(x*x+y*y);}
	double angle(){return atan2(y,x);}
	void read(){scanf("%lf%lf",&x,&y);}
	void prt() const{printf("%lf %lf\n",x,y);}
}u[25][25],v[25][25];
char st[5];
struct shaft{
	node P; double r; bool C;
	void read(){P.read(),scanf("%lf%s",&r,st),C=strlen(st)<2;}
}a[25];
int Case,n,S,T,e[25]; bool b[25]; double d[25][25],D,ans;
bool cross(const shaft &A,const node &B,const node &C)
{return fabs((A.P-B)^(C-B))/(C-B).len()<A.r+eps && (((A.P-B)&(C-B))>-eps) && ((A.P-C)&(B-C))>-eps;}
bool cross(const node &A,const node &B,const node &C,const node &D)
{return ((C-A)^(B-A))*((D-A)^(B-A))<-eps && ((B-C)^(D-C))*((A-C)^(D-C))<-eps;}
bool check(int m,const node &A,const node &B)
{rep(i,m) if (cross(u[e[i]][e[i+1]],v[e[i]][e[i+1]],A,B)) return 0; return 1;}
double vaild(double a){return fabs(a-pi)<eps?-pi:a;}
double get(const shaft &A,const node &B,const node &C)
{
	double a0=vaild((B-A.P).angle())-vaild((C-A.P).angle());
	if (!A.C) a0=-a0; if (a0<-eps) a0+=2*pi; return A.r*a0;
}
void dfs(int m,int i,double S)
{
	if (S>=ans) return; if (i==T){ans=S; return;} e[m]=i;
	rep(j,n) if (!b[j] && d[i][j]<D+eps && check(m,u[i][j],v[i][j]))
		b[j]=1,dfs(m+1,j,S+d[i][j]+(m?get(a[i],v[e[m-1]][i],u[i][j]):0)),b[j]=0;
}
double com(const shaft &A,const shaft &B,node &U,node &V,node &U1,node &V1)
{
	U=B.P-A.P,V=A.P-B.P; double D=U.len(),a0; U=U/D*A.r,V=V/D*B.r;
	if (A.C==B.C){
		a0=acos((A.r-B.r)/D);
		U1=A.P+U*node(cos(a0),sin(a0));
		V1=B.P+V*node(cos(a0-pi),sin(a0-pi));
		a0*=-1;
		U=A.P+U*node(cos(a0),sin(a0));
		V=B.P+V*node(cos(a0-pi),sin(a0-pi));
		if (A.C) swap(U,U1),swap(V,V1); swap(U1,V1);
	}else{
		a0=acos((A.r+B.r)/D);
		U1=A.P+U*node(cos(a0),sin(a0));
		V1=B.P+V*node(cos(a0),sin(a0));
		a0*=-1;
		U=A.P+U*node(cos(a0),sin(a0));
		V=B.P+V*node(cos(a0),sin(a0));
		if (A.C) swap(U,U1),swap(V,V1); swap(U1,V1);
	}
	return (V-U).len();
}
void prt()
{
	printf("Case %d: ",++Case);
	if (ans>1e8){puts("Cannot reach destination shaft"); return;}
	if (int(ans*100+0.5)%10) printf("length = %.2lf\n",ans);  
	else if (int(ans*100+0.5)%100) printf("length = %.1lf\n",ans);  
		else printf("length = %.0lf\n",ans);
}
int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	while (scanf("%d",&n),n){
		rep(i,n) a[i].read(); scanf("%d%d%lf",&S,&T,&D);
		rep(i,n) rep(j,i){
			d[i][j]=d[j][i]=com(a[i],a[j],u[i][j],v[i][j],u[j][i],v[j][i]);
			rep(k,n) if (k!=i && k!=j){
				if (cross(a[k],u[i][j],v[i][j])) d[i][j]=1e9;
				if (cross(a[k],u[j][i],v[j][i])) d[j][i]=1e9;
			}
		}
		ans=1e9,b[S]=1,dfs(0,S,0),b[S]=0,prt();
	}
	return 0;
}
