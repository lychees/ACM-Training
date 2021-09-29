#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-7; const int N=10005;
int Case,n,c,y,x[N],z[N],t[N][66]; char type[9];
double cal(double v)
{
	double T=0;
	rep(i,n) if (z[i]) T=ceil(T),T+=x[i]+t[i][int(T)%60]; else T+=x[i]/v*60;
	return T;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n){
			scanf("%*s%*s%s%d",type,x+i);
			if (z[i]=*type=='f'){
				scanf("%d",&c); rep(j,61) t[i][j]=1<<9;
				while (c--){scanf("%d",&y),y%=60; rep(j,y+1) t[i][j]=min(t[i][j],y);}
				rep(j,61) t[i][j]=min(t[i][j],t[i][0]+60),t[i][j]-=j;
			}
		}
		double t=cal(80),l=0,r=80,m; while (l+eps<r) m=(l+r)/2,(cal(m)<t+eps?r:l)=m;
		printf("Test Case %d: %02d:%02d:%02d %.2lf\n\n",++Case,int(t/60+eps),int(t+eps)%60,int(t*60+eps)%60,l);
	}
	return 0;
}
