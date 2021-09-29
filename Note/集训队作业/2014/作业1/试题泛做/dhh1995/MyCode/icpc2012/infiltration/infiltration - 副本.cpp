#include<cstdio>
#include<vector>
#include<bitset>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define each(i,a) for (i=a.begin();i!=a.end();++i)
const int N=80;
bitset<N> a[N]; char s[N]; int Case,n,ans,p[N],o[N];
bool cmp(const int i,const int j){return a[i].count()>a[j].count();}
void dfs(vector<int> f,int c)
{
	if (c>=ans) return; vector<int> g; vector<int>::iterator i,j;
	g.clear(),sort(f.begin(),f.end(),cmp);
//	rep(k,c) printf("%d ",p[k]); puts("");
//	each(i,f) printf("%d ",*i+1); puts("f");
	each(i,f){
		each(j,g) if ((a[*j]&a[*i])==a[*i]) break;
		if (j==g.end()) g.push_back(*i);
	}
//	each(i,g) printf("%d ",*i+1); puts("g");
//	each(i,g){rep(j,n) printf("%d",a[*i].test(j)); puts("");}
	if (g.size()==1 && !a[*g.begin()].any()){ans=c; rep(i,c) o[i]=p[i]; return;}
	bitset<N> b[N],A; each(j,g) b[*j]=a[*j];
	each(i,g){A=a[*i]; each(j,g) a[*j]^=a[*j]&A; p[c]=*i,dfs(g,c+1); each(j,g) a[*j]=b[*j];}
}
int main()
{
	freopen("infiltration.in","r",stdin);
	freopen("infiltration.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		vector<int> f; f.clear();
		rep(i,n){a[i].reset(); f.push_back(i); scanf("%s",s); rep(j,n) a[i][j]=s[j]=='1' || i==j;}
		ans=6; dfs(f,0); printf("Case %d: %d",++Case,ans);
		rep(i,ans) printf(" %d",o[i]+1); puts("");
	}
	return 0;
}
