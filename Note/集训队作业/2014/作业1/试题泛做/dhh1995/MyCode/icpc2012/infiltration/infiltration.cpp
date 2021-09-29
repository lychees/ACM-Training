#include<cstdio>
#include<vector>
#include<bitset>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define each(i,a) for (i=a.begin();i!=a.end();++i)
const int N=80;
bitset<N> a[N],A,z; char s[N]; int T,Case,n,m,ans,b[N],p[N],o[N];
void dfs(int c,int x,bitset<N> y)
{
	if (c>=ans) return; if (y.count()==n){ans=c; rep(i,c) o[i]=p[i]; return;}
	for (int i=x;i<m;++i){z=y|a[b[i]]; if (y!=z) p[c]=b[i],dfs(c+1,i+1,z);}
}
void greedy()
{
	z.reset();
	while (++ans){
		int x,res=0;
		rep(i,m) if ((z|a[b[i]]).count()>res) res=(z|a[b[i]]).count(),x=b[i];
		z|=a[x],o[ans-1]=x; if (z.count()==n) return;
	}
}
int main()
{
	freopen("infiltration.in","r",stdin);
	freopen("infiltration.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		rep(i,n){a[i].reset(); scanf("%s",s); rep(j,n) a[i][j]=s[j]=='1' || i==j;} m=0;
		rep(i,n){int flag=1; rep(j,n) if (a[i]==a[j]?i>j:(a[i]&a[j])==a[i]) flag=0; if (flag) b[m++]=i;}
		greedy(); dfs(0,0,A); printf("Case %d: %d",++Case,ans);
		rep(i,ans) printf(" %d",o[i]+1); puts("");
	}
	return 0;
}
