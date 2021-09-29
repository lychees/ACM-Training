#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;i++)
int n,m,k,l,r,d,a[1000005],f[1000005];
int main()
{
	freopen("low.in","r",stdin);
	freopen("low.out","w",stdout);
	while (scanf("%d%d",&n,&k)!=EOF){
		m=n*k*2; rep(i,m) scanf("%d",a+i); sort(a,a+m);
		for (l=a[1]-a[0],r=1e9;l<r;){
			d=l+r>>1; rep(i,m+1) f[i]=0;
			rep(i,m) if (2LL*f[i]*k>=i){
				f[i+1]=max(f[i+1],f[i]);
				if (a[i+1]-a[i]<=d) f[i+2]=max(f[i+2],f[i]+1);
			}
			f[m]>=n?r=d:l=d+1;
		}
		printf("%d\n",l);
	}
	return 0;
}
