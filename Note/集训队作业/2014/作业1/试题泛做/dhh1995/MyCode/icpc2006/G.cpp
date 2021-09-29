#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0,_=n;i<_;++i)
int n; char s[9]; vector<int> f,g;
int main()
{
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	while (scanf("%d",&n),n){
		bool flag=1,bo=0; int x,m=1,c=0,p=0; 
		rep(k,n){
			scanf("%s%d",s,&x);
			if (s[0]=='P') p+=x;
			else if (s[0]!='C'){
				if (bo && p)
					if (flag){
						flag=0,f.clear();
						for (int i=1;i*i<=p;++i) if (p%i==0){
							if (i>c) f.push_back(i-c);
							if (i*i!=p && p/i>c) f.push_back(p/i-c);
						}
					}else{
						g.clear();
						rep(i,f.size()) if (f[i]+c>0 && p%(f[i]+c)==0) g.push_back(f[i]);
						f=g;
					}
				c+=s[0]=='I'?x:-x,m=max(m,1-c),p=0,bo=1;
			}
		}
		sort(f.begin(),f.end());
		g.clear(); rep(i,f.size()) if (f[i]>=m) g.push_back(f[i]);
		if (flag) printf("SIZE >= %d\n",m);
		else if (!g.size()) puts("IMPOSSIBLE");
		else rep(i,g.size()) printf("%d%s",g[i],i+1<_?" ":"\n");
	}
	return 0;
}
