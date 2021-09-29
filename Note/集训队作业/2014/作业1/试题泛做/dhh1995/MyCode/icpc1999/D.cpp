#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,t,o,v[25],l[25]; double L,V,res,ans,eps=1e-8;
struct node{
	double x,y,a; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	bool operator <(const node &A) const{
		return fabs(a-A.a)<eps?len()<A.len():a<A.a;
	}
	double angle() const{return atan2(y,x);}
	double len() const{return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
}a[25],b[25],h[25];
int main()
{
	while (scanf("%d",&n),n){
		ans=res=0; rep(i,n) a[i].read(),scanf("%d%d",v+i,l+i),res+=v[i]+.01;
		rep(k,1<<n){
			L=V=m=t=0;
			rep(i,n) if (k>>i&1) b[m++]=a[i]; else L+=l[i],V+=v[i]+.01;
			if (!m || V>res) continue;
			rep(i,m) if (b[i].x<b->x) swap(b[0],b[i]);
			b[m++]=b[0]; rep(i,m) b[i]=b[i]-b[m-1],b[i].a=b[i].angle(); sort(b+1,b+m-1);
			rep(i,m){while (t>1 && (h[t]-h[t-1])%(b[i]-h[t-1])<0) --t; h[++t]=b[i];}
			rep(i,t) L-=(h[i+1]-h[i]).len();
			if (L>-eps) ans=L,res=V,o=k;
		}
		if (Case) puts(""); printf("Forest %d\nCut these trees:",++Case);
		rep(i,n) if (!(o>>i&1)) printf(" %d",i+1); printf("\nExtra wood: %.2lf\n",ans);
	}
	return 0;
}
