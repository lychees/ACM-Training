#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-8,pi=acos(-1.),H=5*sqrt(3.);
int Case,f[3],g[3],B[3][3];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator *(const node &A){return node(x*A.x-y*A.y,x*A.y+y*A.x);}
	double len(){return sqrt(x*x+y*y);}
}a[3],A[3][3],p[15];
node polar(double a){return node(cos(a),sin(a));}
bool change(int t)
{
	int p,q,r; double l,d,h,s; scanf("%d%d",&p,&q); if (p<0) return 0;
	rep(i,4) if (p<i*90+90){
		f[t]=i,p-=i*90,r=180-45-p;
		l=5/sin(r*pi/180),d=l*sin(p*pi/180)*sqrt(2.); break;
	}
	h=5*sqrt(2.),s=sqrt(h*h+l*l),g[t]=0; if (q>90) g[t]=1,q=180-q;
	double v=h*sin(q*pi/180)/sin(pi-q*pi/180-asin(l/s));
	a[t]=node(5-d,H)*(1-v/s)+node(d,0); return 1;
}
void get(node &A,node V,int f,int g)
{if (f%4==0) A=V; else A=p[f]*10+node(5,H)+p[f+2]*V; if (g) A.y*=-1;}
void work()
{
	double ans=1e9;
	rep(i,4){
		rep(t,2){
			int j=(f[t]-i+4)%4,k=j+4;
			get(A[t][0],a[t],B[t][0]=j,g[t]),get(A[t][1],a[t],B[t][1]=k,g[t]);
		}
		rep(j,2) rep(k,2) if (abs(B[0][j]-B[1][k])<4) ans=min(ans,(A[0][j]-A[1][k]).len());
	}
	printf("Case %d: %.3lf\n",++Case,ans);
}
int main(){rep(i,10) p[i]=polar(i*pi/3); while (change(0)) change(1),work(); return 0;}
