#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;i++)
int n,m,k,c,l,r,d,a[1000005],f[1000005];
void read(int &x)
{
	#define CH getchar()
	char ch; x=0; for (ch=CH;ch<'0' || ch>'9';ch=CH);
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH);
}
int main()
{
	freopen("low.in","r",stdin);
	freopen("low.out","w",stdout);
	read(n),read(k),m=n*k*2; rep(i,m) read(a[i]); sort(a,a+m);
	for (l=a[1]-a[0],r=1e9;l<r;){
		d=l+r>>1; rep(i,m+1) f[i]=0;
		rep(i,m) if (2*f[i]*k>=i){
			c=0; if (f[i]>=n){f[m]=n; break;} if (f[i]>f[i+1]) f[i+1]=f[i];
			if (a[i+1]-a[i]<=d && f[i]+1>f[i+2]) f[i+2]=f[i]+1;
		}else if (++c>1) break;
		f[m]>=n?r=d:l=d+1;
	}
	printf("%d\n",l);
}
