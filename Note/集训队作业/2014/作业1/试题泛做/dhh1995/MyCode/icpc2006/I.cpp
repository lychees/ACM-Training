#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int Case,n,m,ans,t,x,y,d[55][55]; string a,b; map<string,int> H;
int get(string s){if (H.find(s)==H.end()){H[s]=++t; return t;} return H[s];}
int main()
{
	while (scanf("%d%d",&n,&m),n&&m){
		rep(i,n) rep(j,n) d[i][j]=(i!=j)<<10; ans=t=0; H.clear();
		rep(i,m) cin>>a>>b,x=get(a),y=get(b),d[x][y]=d[y][x]=1;
		rep(k,n) rep(i,n) rep(j,n) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		rep(i,n) rep(j,n) ans=max(ans,d[i][j]);
		printf("Network %d: ",++Case);
		if (ans<1<<10) printf("%d\n",ans); else puts("DISCONNECTED");
		puts("");
	}
	return 0;
}
