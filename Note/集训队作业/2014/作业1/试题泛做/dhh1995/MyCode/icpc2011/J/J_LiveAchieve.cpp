#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=1000005;
int Case,n=N-5,m,ans,f[N][8],a[1005],A[1005];
int main()
{
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	memset(f,6,sizeof(f)),f[0][0]=0,a[1]=1;
	for (m=2;a[m-1]<=n;++m) a[m]=a[m-1]+m*m;
	int w=m-2,*b=a+w; b[1]=1,b[2]=4;
	for (m=3;b[m-1]<=n;++m) b[m]=b[m-2]+m*m; m+=w-2;
	rep(i,m) A[i]=a[i]; sort(A+1,A+m+1);
	rep(i,m) if (A[i]>4) for (int j=n;j>=A[i];--j) for (int k=1;k<=6 && f[j][k]>N;++k)
		if (f[j-A[i]][k-1]<=N){f[j][k]=A[i]; break;}
	while (scanf("%d",&n),n){
		printf("Case %d:",++Case);
		int k; for (k=0;k<=6;++k) if (f[n][k]<=N) break;
		if (k>6) puts(" impossible");
		else{
			int last=n+1,res=0,x=0;
			for (;res=0,k;--k){
				rep(i,m) if (a[i]>4 && a[i]<=n && a[i]<last && f[n-a[i]][k-1]<a[i])
					if (a[i]>res) res=a[i],x=i;
				if (x<=w) printf(" %dH",x); else printf(" %dL",x-w); n-=last=res;
			}
			puts("");
		}
	}
	return 0;
}
