#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double pi=acos(-1.); const int N=1005;
int Case,n,m,ans,flag,p[N],b[N]; double f[N],r[N],h[N],L[N],u[N];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
}A,B,T,a[N];
bool cmp(const int i,const int j){return f[i]<f[j];}
bool ok()
{
	rep(i,m) p[i]=i; sort(p,p+m,cmp); int c=0,j;
	rep(i,m){j=p[i]; if (!c && i && f[j]-f[p[i-1]]>1e-8) return 1; c+=j&1?1:-1;}
	return !m || f[p[0]]>-pi || f[p[m-1]]<pi;
}
void add(double x,double y)
{
	if (x<-pi) f[m++]=x+2*pi,f[m++]=pi,f[m++]=-pi,f[m++]=y;
	else if (y>pi) f[m++]=x,f[m++]=pi,f[m++]=-pi,f[m++]=y-2*pi;
		else f[m++]=x,f[m++]=y;
}
void work(int i,node A)
{
	A=A-a[i]; double D=fabs(A.x),e=A.x<0?pi:0,v;
	if (D<L[i]) v=acos(D/L[i])+u[i],add(e-v,e+v);
	D=fabs(A.y),e=A.y<0?-pi/2:pi/2;
	if (D<L[i]) v=acos(D/L[i])+u[i],add(e-v,e+v);
}
void work(int i,int j)
{
	node A=a[j]-a[i]; double D=A.len(),e=A.angle(),v,R=r[i]+r[j],Q=sqrt(D*D-R*R);
	if (h[i]>Q) v=acos(Q/D),add(e-v,e+v);
	else if (L[i]+r[j]>D){
		v=acos((D*D+L[i]*L[i]-r[j]*r[j])/(2*D*L[i]))+u[i]; double P=h[i]+r[j],v0;
		if (P>D) add(e-v,e+v); else v0=acos(P/D),add(e-v,e-v0),add(e+v0,e+v);
	}
}
int main()
{
	while (ans=0,A.read(),B.read(),scanf("%d",&n),n){
		rep(i,n) b[i]=1,a[i].read(),T.read(),T.x/=2,
			r[i]=T.x,h[i]=T.y,L[i]=T.len(),u[i]=acos(h[i]/L[i]);
		do{
			flag=0;
			rep(i,n) if (b[i]){
				m=0; work(i,A),work(i,B); rep(j,n) if (i!=j && b[j]) work(i,j);
				if (ok()) ++ans,b[i]=0,flag=1;
			}
		}while (flag);
		printf("Forest %d\n%d tree(s) can be cut\n\n",++Case,ans);
	}
	return 0;
}
