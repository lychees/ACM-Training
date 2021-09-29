#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int a,m,l,r,x,y,Case,ans,lim,n,p[55],o[55];
bool small(){rep(i,min(lim,n)+1) if (p[lim-i]!=o[n-i]) return p[lim-i]>o[n-i]; return 0;}
void work(int u,int v)
{
	int x=0,S=1,res=lim; rep(i,lim) p[i]=0,S*=m; p[lim]=0;
	for (int i=lim;i>=0 && x<u;--i) res+=p[i]=min((u-x-1)/S+1,(v-x)/S),x+=p[i]*S,S/=m;
	if (res<ans || res==ans && small()){ans=res; n=lim; rep(i,n+1) o[i]=p[i];}
}
void prt()
{
	if (ans==1<<30){puts(" impossible"); return;}
	int last=n;
	for (int i=n;i>=0;--i) if (o[i] || !i){
		if (i<last) printf(" %dM",last-i);
		if (o[i]) printf(" %dA",o[i]),last=i;
	}
	puts("");
}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	while (scanf("%d%d%d%d%d%d",&a,&m,&x,&y,&l,&r),a){
		printf("Case %d:",++Case);
		if (l<=x && y<=r) puts(" empty");
		else{
			ans=1<<30; rep(i,35) o[i]=0;
			for (lim=0;lim<35;++lim){
				int c=l-x,d=r-y;
				if (c<=d/a*a && d>=0) work(c>0?(c-1)/a+1:0,d/a);
				if (y>r/m) break; x*=m,y*=m;
			}
			prt();
		}
	}
	return 0;
}
