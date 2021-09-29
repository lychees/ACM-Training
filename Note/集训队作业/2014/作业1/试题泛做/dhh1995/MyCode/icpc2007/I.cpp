#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double e=0.097;
int Case,n; double ans,sum,H,h[15],d[15],s[15];
double get(double a,double b,double c){double d=b*b-4*a*c; return (-b-sqrt(d))/2/a;}
double solve(double sum,double V){return get(e,-e*(H+V)-1,V+e*H*V-sum);}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) scanf("%lf",h+i); s[n]=0;
		for (int i=n-1;i>=0;--i) s[i]=s[i+1]+h[i];
		rep(i,n-1) scanf("%lf",d+i); ans=H=*h,sum=s[1]-*d;
		rep(i,n) if (i){
			if (i>1){
				if (sum/(s[i-1]-d[i-1]*2)>1+(H-d[i-1])*e){
					ans+=s[i-1]-sum/((H-d[i-1])*e+1); break;
				}
				double x=sum*(h[i-1]-d[i-1])/(s[i-1]-d[i-1]*2);
				ans+=solve(x,h[i-1]),sum-=x;
			}
			if (i+1==n || sum/(s[i]-d[i])>1+(H-d[i])*e){
				ans+=solve(sum,s[i]); break;
			}
		}
		printf("Case %d: %.3lf\n\n",++Case,ans);
	}
	return 0;
}
