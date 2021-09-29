#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int n,m,Case; double d[1<<10],f[1<<10],pi=acos(-1.);
struct node{
	int x,y; node(){} node(int _x,int _y):x(_x),y(_y){}
	node operator -(const node &A) const{return node(x-A.x,y-A.y);}
	int operator *(const node &A){return x*A.x+y*A.y;}
	int operator %(const node &A){return x*A.y-y*A.x;}
	bool operator ==(const node &A){return x==A.x && y==A.y;}
	bool operator <(const node &A) const{
		return fabs(angle()-A.angle())<1e-8?len()<A.len():angle()<A.angle();
	}
	double angle() const{return atan2(y,x);}
	double len() const{return sqrt(x*x+y*y+0.);}
	void read(){scanf("%d%d",&x,&y);}
}a[10],b[10],q[25],A,B;
double work(int s)
{
	int L=0,t=0; rep(i,n) if (s>>i&1) a[L++]=b[i]; if (!L) return 0;
	rep(i,L) if (a[i].x<a[0].x) swap(a[i],a[0]);
	for (int i=L-1;i>=0;--i) a[i]=a[i]-*a; sort(a+1,a+L); a[L]=*a;
	rep(i,L+1){
		while (t>1 && (a[i]-q[t-1])%(q[t]-q[t-1])>0) --t;
		q[++t]=a[i];
	}
	double len=2*pi*m;
	for (int i=1;i<t;++i) len+=(q[i]-q[i+1]).len();
	return len;
}
int main()
{
	while (scanf("%d%d",&n,&m),n){
		rep(i,n) b[i].read(); rep(i,1<<n) d[i]=work(i),f[i]=1e9; f[0]=0;
		rep(i,1<<n) rep(j,1<<n) if (!(i&j)) f[i|j]=min(f[i|j],f[i]+d[j]);
		printf("Case %d: length = %.2lf\n",++Case,f[(1<<n)-1]);
	}
	return 0;
}
