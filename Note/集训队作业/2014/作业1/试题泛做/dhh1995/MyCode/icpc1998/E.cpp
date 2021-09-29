#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int Case,n,m,T,x,c[105],a[105][105],b[105][105];
int trans(int i)
{
	int res=1<<20;
	rep(j,n)
		if (c[j]<a[i][j]) return 0;
		else if (a[i][j]) res=min(res,c[j]/a[i][j]);
	return res;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) scanf("%d",c+i); scanf("%d",&m);
		rep(i,m){rep(j,n) a[i][j]=b[i][j]=0; while (scanf("%d",&x),x) x<0?++a[i][-x]:++b[i][x];}
		scanf("%d",&T); int t=T,flag=1;
		while (t && flag){
			flag=0;
			rep(i,m) if (x=min(t,trans(i))){
				rep(j,n) c[j]-=(a[i][j]-b[i][j])*x;
				t-=x,flag=1;
			}
		}
		printf("Case %d: ",++Case);
		if (flag) printf("still live after %d transitions\n",T);
		else printf("dead after %d transitions\n",T-t);
		printf("Places with tokens:");
		rep(i,n) if (c[i]) printf(" %d (%d)",i,c[i]);
		puts(""),puts("");
	}
	return 0;
}
