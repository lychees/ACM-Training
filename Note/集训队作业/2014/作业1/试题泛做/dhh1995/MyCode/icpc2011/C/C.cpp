#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const string o="WAKJSD";
int n,m,t,Case,near,c[40005],v[205][205]; bool b[205][205]; char s[55];
void dfs(int x,int y,int t)
{
	if (x<0 || x>n || y<0 || y>m) return;
	if (v[x][y]>=0){if (v[x][y]) near=v[x][y]; return;}
	if ((!!t)!=b[x][y]) return; v[x][y]=t;
	dfs(x+1,y,t),dfs(x-1,y,t),dfs(x,y+1,t),dfs(x,y-1,t);
}
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	while (scanf("%d%d",&n,&m),n||m){
		t=0; memset(b,0,sizeof(b)),memset(v,-1,sizeof(v));
		rep(i,n){
			scanf("%s",s+1);
			rep(j,m){
				int x=s[j]<='9'?s[j]-48:s[j]-87;
				rep(k,4) b[i][j*4+1-k]=x>>k-1&1;
			}
		}
		++n,m=m*4+1,dfs(0,0,0);
		rep(i,n) rep(j,m) if (b[i][j] && v[i][j]<0) dfs(i,j,++t);
		rep(i,n) rep(j,m) if (!b[i][j] && v[i][j]<0) dfs(i,j,0),++c[near];
		string ans=""; rep(i,t) if (i && c[i]<6) ans+=o[c[i]];
		sort(ans.begin(),ans.end());
		cout<<"Case "<<++Case<<": "<<ans<<endl;
		rep(i,t) c[i]=0;
	}
	return 0;
}
