#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int n,m,x,y,T,flag,a[13],t[13],d[13],c[1<<13];
int main()
{
	c[0]=0; rep(i,1<<12) if (i) c[i]=c[i-(i&-i)]+1;
	while (scanf("%d%d",&n,&m)!=EOF){
		rep(i,n) a[i]=1<<i,d[i]=t[i]=0; T=0,flag=1;
		rep(i,m){
			scanf("%d%d",&x,&y),--x,--y; if (c[a[x]]>c[a[y]]) swap(a[x],a[y]); a[y]|=a[x];
			t[x]=t[y]=max(t[x],t[y])+1;
		}
		rep(i,n){T=max(T,t[i]); if (d[c[a[i]]-1]++) flag=0;}
		printf("%s\n%d\n",flag?"YES":"NO",T);
	}
	return 0;
}
