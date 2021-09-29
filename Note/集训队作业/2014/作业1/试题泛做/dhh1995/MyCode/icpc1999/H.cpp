#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,a[905]; double V,H;
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		n*=m,H=m=0; rep(i,n) scanf("%d",a+i); sort(a,a+n); scanf("%lf",&V),V/=100;
		rep(i,n){m=i+1,H=a[i]+V/m; if (H<a[i+1]+1e-8) break; V-=m*(a[i+1]-a[i]);}
		printf("Region %d\nWater level is %.2lf meters.\n%.2lf percent of the region is under water.\n\n",++Case,H,m*100./n);
	}
	return 0;
}
