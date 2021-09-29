#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int n,m,x[155],y[155],a[13],t[13],T,flag;
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF){
		rep(i,n) t[i]=0; T=0,flag=1;
		rep(i,m){
			scanf("%d%d",x+i,y+i),--x[i],--y[i];
			t[x[i]]=t[y[i]]=max(t[x[i]],t[y[i]])+1;
		}
		rep(i,n) T=max(T,t[i]);
		rep(i,1<<n){
			rep(j,n) a[j]=i>>j&1;
			rep(j,m) if (a[x[j]]>a[y[j]]) swap(a[x[j]],a[y[j]]);
			rep(j,n-1) if (a[j]>a[j+1]) flag=0; if (!flag) break;
		}
		printf("%s\n%d\n",flag?"YES":"NO",T);
	}
	return 0;
}
