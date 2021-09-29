#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define mk make_pair
const int N=205;
int Case,n,m,x[N],y[N],z[N]; bool b[N]; double ans; pair<double,int> a[N];
double work(double &ans,int i,double x1,double y1,double vx,double vy)
{
	int m=0,c=0; double L=sqrt(vx*vx+vy*vy),s1,s2,s3,last=ans; a[m++]=mk(0,0),a[m++]=mk(1,0);
	rep(j,n) if (j!=i && b[j]){
		s1=(x[j]-x1)*vy-(y[j]-y1)*vx,s2=(x[j]-z[j]/2.-x1)*vy+y1*vx,s3=(x[j]+z[j]/2.-x1)*vy+y1*vx;
		if (fabs(s2)<1e-6) a[m++]=mk(1e20,1);
		else a[m++]=mk((s2*(y[j]-y1)-s1*y1)/(s1+s2)/vy,1);
		if (fabs(s3)<1e-6) a[m++]=mk(-1e20,-1);
		else a[m++]=mk((s3*(y[j]-y1)-s1*y1)/(s1+s3)/vy,-1);
	}
	sort(a,a+m);
	rep(i,m){
		if (!c && i && a[i].first>0 && a[i-1].first<1)
			ans+=(a[i].first-a[i-1].first)*L;
		c+=a[i].second;
		}
	printf("%lf\n",ans-last);
}
int main()
{
	while (scanf("%d",&n),ans=0,n){
		rep(i,n) scanf("%d%d%d",x+i,y+i,z+i),b[i]=1;
		rep(i,n) rep(j,n) if (j!=i && x[i]*2-z[i]>=x[j]*2-z[j] && x[i]*2+z[i]<=x[j]*2+z[j])
			if (x[i]<x[j]?2LL*(x[i]-x[j])*-y[j]+1LL*(y[i]-y[j])*z[j]<=0:2LL*(x[i]-x[j])*-y[j]-1LL*(y[i]-y[j])*z[j]>=0) b[i]=0;
		rep(i,n) if (b[i]) work(ans,i,x[i],y[i],-z[i]/2.,y[i]),work(ans,i,x[i],y[i],z[i]/2.,y[i]);
		printf("Case %d: %.0lf\n",++Case,ans);
	}
	return 0;
}
