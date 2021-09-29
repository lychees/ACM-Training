#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-8,S=.005; const int N=55;
int Case,n,m,flag; double scale;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	bool operator <(const node &A) const{return fabs(x-A.x)<eps?y<A.y:x<A.x;}
	bool operator ==(const node &A) const{return fabs(x-A.x)<eps && fabs(y-A.y)<eps;}
	void read(){scanf("%lf%lf",&x,&y);}
};
struct line{
	node A,B; bool v;
	void init(){A=node(1e9,1e9),B=node(-1e9,-1e9);}
	void frame(line &L,bool f){
		if ((A.x>L.A.x)^f) L.A.x=A.x; if ((A.y>L.A.y)^f) L.A.y=A.y;
		if ((B.x<L.B.x)^f) L.B.x=B.x; if ((B.y<L.B.y)^f) L.B.y=B.y;
	}
	void read(){A.read(),B.read(); if (B<A) swap(A,B); v=fabs(A.x-B.x)<eps;}
	void move(node &C,node &D,double scale){A=(A-C)*scale+D,B=(B-C)*scale+D;}
	bool inside(line &C,line &D){
		if (C.B.x<A.x-S || C.B.y<A.y-S || C.A.x>B.x+S || C.A.y>B.y+S) return 0; D=C;
		frame(D,0); return D.A.x<D.B.x && D.A.y<D.B.y?1:-1;
	}
	bool online(node &C){return v?
		fabs(C.x-A.x)<eps && A.y<C.y+eps && C.y-eps<B.y:
		fabs(C.y-A.y)<eps && A.x<C.x+eps && C.x-eps<B.x;
	}
	double len(){return v?B.y-A.y:B.x-A.x;}
}a[N],b[N],c[N],E;
bool inA(line &L){rep(i,m) if (a[i].v==L.v && a[i].online(L.A) && a[i].online(L.B)) return 1; return 0;}
bool inC(line &L){rep(i,n) if (c[i].v==L.v && c[i].A==L.A && c[i].B==L.B) return 1; return 0;}
bool check(node &P,node &Q)
{
	E.init(); rep(i,n) c[i]=b[i],c[i].move(P,Q,scale),c[i].frame(E,1);
	rep(i,n) if (!inA(c[i])) return 0; line F; int tmp;
	rep(i,m) if (tmp=E.inside(a[i],F)) if (tmp<0 || !inC(F)) return 0; return 1;
}
bool work(node &P,node &Q)
{
	int j=0; while (j<n && b[j].online(P)) ++j;
	if (j>=n){
		scale=S/b[0].len(); if (j>1) scale=max(scale,S/b[1].len());
		return scale>1?0:check(P,Q);
	}
	rep(i,m) if (a[i].v==b[j].v){
		if (a[i].v)
			if (fabs(b[j].A.x-P.x)<eps){
				if (fabs(a[i].A.x-Q.x)<eps) scale=(a[i].A.y-Q.y)/(b[j].A.y-P.y);
			}else scale=(a[i].A.x-Q.x)/(b[j].A.x-P.x);
		else
			if (fabs(b[j].A.y-P.y)<eps){
				if (fabs(a[i].A.y-Q.y)<eps) scale=(a[i].A.x-Q.x)/(b[j].A.x-P.x);
			}else scale=(a[i].A.y-Q.y)/(b[j].A.y-P.y);
		if (scale<eps || scale>1?0:check(P,Q)) return 1;
	}
	return 0;
}
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF && (n||m)){
		rep(i,n) b[i].read(); rep(j,m) a[j].read(); flag=0;
		rep(i,n) rep(j,m) if (b[i].v==a[j].v && !flag)
			flag=work(b[i].A,a[j].A) || work(b[i].B,a[j].B);
		puts(flag?"valid puzzle":"impossible");
		//printf("Case %d: %s\n\n",++Case,flag?"valid puzzle":"impossible");
	}
	return 0;
}
