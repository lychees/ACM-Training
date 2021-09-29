#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
typedef long long ll;
const ll N=205,inf=1LL<<55; map<string,int> H;
string s[N],t; int Case,n,m,a[N],L[N],c[N][N]; ll d[N][N];
int get(string t,bool flag)
{
	if (H.find(t)==H.end()) if (flag) return -1; else return L[n]=t.size(),s[n]=t,H[t]=n++;
	return H[t];
}
bool check(int i,int j,int k)
{
	int x=min(L[i],L[j]);
	return s[i].substr(L[i]-x,L[i]-L[k])==s[j].substr(L[j]-x,L[j]-L[k]);
}
int main()
{
	while (cin>>t,t[0]!='.'){
		H.clear(),n=0,a[0]=get(t,0),cin>>t>>m,a[1]=get(t,0); rep(i,m*2) cin>>t,a[i+2]=get(t,0);
		rep(i,n) rep(j,n) d[i][j]=i==j?0:inf; rep(i,m) d[a[i*2+2]][a[i*2+3]]=1;
		rep(i,n) rep(j,n) if (L[i]>=L[j]) c[i][j]=get(s[i].substr(L[i]-L[j]),1);
//		rep(i,n){rep(j,n) printf("%lld ",d[i][j]); puts("");}
		rep(k,n) rep(i,n) if (L[i]>=L[k] && c[i][k]>=0)
			rep(j,n) if (L[j]>=L[k] && c[j][k]>=0 && check(i,j,k))
				d[i][j]=min(d[i][j],d[c[i][k]][k]+d[k][c[j][k]]);
//		puts("");
//		rep(i,n){cout<<s[i]<<" "; rep(j,n) printf("%lld ",d[i][j]); puts("");}
		printf("Case %d: ",++Case);
		if (d[a[0]][a[1]]<inf) cout<<d[a[0]][a[1]]<<endl; else puts("No solution");
	}
	return 0;
}
