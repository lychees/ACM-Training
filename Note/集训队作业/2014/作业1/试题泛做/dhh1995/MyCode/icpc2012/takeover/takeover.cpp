#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=100005;
int Case,n,m; long long a[N],b[N],A,B;
bool work()
{
	int i=1,j=1; A=a[0],B=b[0];
	while (i<n || j<m){
		if (i<n && A+a[i]>B+b[j]) A+=a[i++];
		else if (A>B) B=b[j++];
			else if (i<n) A+=a[i++];
		if (j<m && B+b[j]>A+a[i]) B+=b[j++];
		else if (B>A) A=a[i++];
			else if (j<m) B+=b[j++];
	}
	return A>B;
}
int main()
{
	freopen("takeover.in","r",stdin);
	freopen("takeover.out","w",stdout);
	while (scanf("%d%d",&n,&m)!=EOF){
		rep(i,n) scanf("%lld",a+i); sort(a,a+n),reverse(a,a+n); a[n]=0;
		rep(i,m) scanf("%lld",b+i); sort(b,b+m),reverse(b,b+m); b[m]=0;
		printf("Case %d: ",++Case),puts(work()?"Takeover Incorporated":"Buyout Limited");
	}
	return 0;
}
