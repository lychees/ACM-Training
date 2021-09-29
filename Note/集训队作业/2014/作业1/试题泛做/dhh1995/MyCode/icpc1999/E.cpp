#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define each(i,a) for (i=a.begin();i!=a.end();++i)
int Case,n,m,ans,a[25]; set<int> f,g; set<int>::iterator k;
int main()
{
	while (scanf("%d",&n),n){
		ans=0,f.clear(); f.insert(0);
		rep(i,n){
			scanf("%d",&m); g.clear(); int s=0,c=0;
			rep(j,m) scanf("%d",a+j+1),a[j+1]=10-a[j+1]+a[j];
			rep(j,m+1) s=max(s,a[j]); ans+=s;
			rep(j,m+1) if (a[j]==s) each(k,f) g.insert(*k+j);
			if (g.size()>10){each(k,g) if (++c>10) break; g.erase(k,g.end());} f=g;
		}
		if (Case) puts("");
		printf("Workyards %d\nMaximum profit is %d.\nNumber of pruls to buy:",++Case,ans);
		each(k,f) printf(" %d",*k); puts("");
	}
	return 0;
}
