#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const double eps=1e-8;
int Case,e[6]; double r[6];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator /(const double &A){return node(x/A,y/A);}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const node &A){return node(x*A.x-y*A.y,x*A.y+y*A.x);}
	double len(){return sqrt(x*x+y*y);}
}a[6];
bool cross(node &A,double r1,node &B,double r2,node &C,node &D)
{
	double d=(A-B).len(); if (d>r1+r2+eps) return 0;
	double Cos=(r1*r1+d*d-r2*r2)/2/r1/d,Sin=sqrt(1-Cos*Cos);
	return C=A+(B-A)*node(Cos,Sin)/(d/r1),D=A+(B-A)*node(Cos,-Sin)/(d/r1),1;
}
bool dfs(int t,int b)
{
	rep(i,1,t-1) if ((a[t]-a[i]).len()+eps<r[i]+r[t]) return 0;
	if (++t==5) return 1; node A,B;
	rep(i,1,4) if (b>>i&1){
		b^=1<<i;
		rep(j,0,t-1) rep(k,j+1,t-1){
			if (cross(a[j],r[j]+(j?e[i]:-e[i]),a[k],r[k]+e[i],A,B)){
				a[t]=A,r[t]=e[i]; if (A.len()+e[i]<*r+eps && dfs(t,b)) return 1;
				a[t]=B,r[t]=e[i]; if (B.len()+e[i]<*r+eps && dfs(t,b)) return 1;
			}
		}
		b^=1<<i;
	}
	return 0;
}
int main()
{
	while (scanf("%d",e+1),e[1]>0){
		rep(i,2,4) scanf("%d",e+i); double L=e[1]/2,R=0; rep(i,1,4) R+=e[i]; r[1]=e[1];
		while (L+1e-5<R) *r=(L+R)/2,a[1]=node(*r-r[1],0),dfs(1,28)?R=*r:L=*r;
		printf("Case %d: %.0lf\n",++Case,R);
	}
	return 0;
}
