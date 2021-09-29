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
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y+0.);}
	void read(){scanf("%d%d",&x,&y);}
	void prt(){printf("%d %d\n",x,y);}
}a[10],b[10],q[25],A,B;
bool cmp(const node &A,const node &B){return (A-a[0]).angle()<(B-a[0]).angle();}
double work(int s)
{
	int L=0,t=0; rep(i,n) if (s>>i&1) a[L++]=b[i]; if (L<2) return m*pi*2*L;
	rep(i,L) if (a[i].x<a[0].x) swap(a[i],a[0]); sort(a+1,a+L,cmp); a[L]=a[0];
	rep(i,L+1){
		while (t>1 && (a[i]-q[t-1])%(q[t]-q[t-1])>0) --t;
		q[++t]=a[i];
	}
	A=(q[t]-q[t-1]),B=(q[2]-q[1]); double arc=acos(A*B/A.len()/B.len()),len=0;
//	printf("%d\n",t); for (int i=1;i<=t;++i) q[i].prt();
	for (int i=1;i<t;++i){
		len+=(q[i]-q[i+1]).len();
		if (i>1){
			A=q[i]-q[i-1],B=q[i+1]-q[i];
			if (A%B!=0) arc+=acos(A*B/A.len()/B.len()); else if (A*B<0) arc+=pi;
		}
		//,printf("arc=%lf\n",arc);
	}
	return len+arc*m;
}
int main()
{
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	while (scanf("%d%d",&n,&m),n){
		rep(i,n){b[i].read(); rep(j,i) if (b[j]==b[i]){--i,--n; break;} }
		printf("%d\n",n);
		rep(i,1<<n) d[i]=work(i),f[i]=1e9,printf("%d %lf\n",i,d[i]); f[0]=0;
		rep(i,1<<n) rep(j,1<<n) if (!(i&j)) f[i|j]=min(f[i|j],f[i]+d[j]);
		printf("Case %d: length = %.2lf\n",++Case,f[(1<<n)-1]);
	}
	return 0;
}
