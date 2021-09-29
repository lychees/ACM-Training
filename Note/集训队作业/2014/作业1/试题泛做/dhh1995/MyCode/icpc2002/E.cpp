#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=55;
int Case,n,sum,x[N],y[N],z[N]; double ans,t,d[N];
double D(int i,int j){return sqrt(0.+(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));}
int main()
{
	while (ans=t=sum=0,scanf("%d",&n),n){
		rep(i,n) scanf("%d%d%d",x+i,y+i,z+i),sum+=z[i]; rep(i,n) d[i]=D(0,i);
		for (;;){
			int i=-1;
			rep(j,n) if (d[j]>=0 && (i<0 || d[j]<d[i])) i=j;
			if (i<0) break; t=max(t,d[i]),ans+=t*z[i]; d[i]=-1;
			rep(j,n) if (d[j]>=0) d[j]=min(d[j],D(i,j));
		}
		printf("Island Group: %d Average %.2lf\n\n",++Case,ans/sum);
	}
	return 0;
}
