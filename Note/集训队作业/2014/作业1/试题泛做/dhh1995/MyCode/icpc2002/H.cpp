#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=1005;
int Case,n,m,ans,a[N],p[N]; bool b[N];
bool cmp(const int i,const int j){return a[i]<a[j];}
int main()
{
	while (ans=0,scanf("%d",&n),n){
		rep(i,n) scanf("%d",a+i),p[i]=i,b[i]=1,ans+=a[i]; sort(p,p+n,cmp); m=a[*p];
		rep(i,n) if (b[i]){
			int c=0,d=1<<20; for (int j=i;b[j];j=p[j]) b[j]=0,++c,d=min(d,a[j]);
			ans+=min((c-2)*d,m*c+m+d);
		}
		printf("Case %d: %d\n\n",++Case,ans);
	}
	return 0;
}
