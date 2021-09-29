#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n; double a[25],b[25],c,f1,f2,f3;
double G(double x)
{
	double z=x,ans=0;
	rep(i,2*n) ans+=z*b[i]/(i+1),z*=x;
	return ans;
}
double F(double y,double k,int side)
{
	rep(i,2*n) b[i]=0; y-=k*c;
	a[1]-=k,a[0]-=y; rep(i,n) rep(j,n) b[i+j]+=a[i]*a[j]; a[1]+=k,a[0]+=y;
	if (side>0) return G(1)-G(c); return G(c)-G(-1);
}
double K(double y,int side)
{
	double g1=F(y,-0.5,side),g2=F(y,0.5,side),g3=F(y,1.5,side);
	return (g2-g1)/(g2-g1-g3+g2);
}
double Y()
{
	f1=F(-0.5,K(-0.5,-1),-1)+F(-0.5,K(-0.5,1),1),
	f2=F( 0.5,K( 0.5,-1),-1)+F( 0.5,K( 0.5,1),1),
	f3=F( 1.5,K( 1.5,-1),-1)+F( 1.5,K( 1.5,1),1);
	return (f2-f1)/(f2-f1-f3+f2);
}
int main()
{
	while (scanf("%d",&n),n++){
		rep(i,n) scanf("%lf",a+n-1-i); scanf("%lf",&c);
		double y=Y(),k1=K(y,-1),k2=K(y,1);
		printf("Case %d: %.3lf %.3lf %.3lf %.3lf\n",++Case,k1,y-k1*c+1e-8,k2,y-k2*c+1e-8);
	}
	return 0;
}
