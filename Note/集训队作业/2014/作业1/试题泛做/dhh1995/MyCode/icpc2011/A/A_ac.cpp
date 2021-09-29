#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int a,m,l,r,x,y,Case,ans,lim,n,p[55],o[55];
bool small(){rep(i,min(lim,n)+1) if (p[lim-i]!=o[n-i]) return p[lim-i]>o[n-i]; return 0;}
void work(int c,int k)
{
	while (c && k<lim) p[k++]=c%m,c/=m; if (k<=lim) p[k++]=c; while (k<=lim) p[k++]=0;
	int res=lim; rep(i,k) res+=p[i];
	if (res<ans){ans=res,n=lim; rep(i,k) o[i]=p[i];}
	else if (res==ans) if (small()){n=lim; rep(i,k) o[i]=p[i];}
}
void dfs(int c,int d,int k)
{if (c<=d) work(c,k); if (c<d && m>1 && k<lim) p[k]=d/m*m<c?c%m:0,dfs((c-1)/m+1,d/m,k+1);}
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
				if (c<=d/a*a && d>=0) dfs(c>0?(c-1)/a+1:0,d/a,0);
				if (y>r/m) break; x*=m,y*=m;
			}
			prt();
		}
	}
	return 0;
}
