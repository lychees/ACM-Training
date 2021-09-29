#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
double f[256]; int Case,n,m,s,x[9],y[9];
bool check(double t)
{
	rep(i,1<<n) f[i]=1e9; f[0]=0;
	rep(i,1<<n) rep(j,n) if (!(i>>j&1))
		if (f[i]<=y[j]) f[i|1<<j]=min(f[i|1<<j],max(f[i],x[j]+0.)+t);
	return f[(1<<n)-1]<1e9;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) scanf("%d%d",x+i,y+i),x[i]*=60,y[i]*=60; double l=0,r=1440*60,mid;
		while (l+1e-3<r) mid=(l+r)/2,check(mid)?l=mid:r=mid;
		m=int(l+.5),s=m%60,m/=60; printf("Case %d: %d:%02d\n",++Case,m,s);
	}
	return 0;
}
