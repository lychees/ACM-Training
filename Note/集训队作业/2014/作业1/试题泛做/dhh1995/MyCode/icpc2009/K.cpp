#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
typedef long long ll;
const ll N=205,inf=1LL<<55;
string s[N],a[25][N],*A;
int Case,L,m,T,n[25]; ll d[25][N][N];
void add(string s){int L=s.size(); rep(i,L) a[L-i][n[L-i]++]=s,s.erase(0,1);}
int get(string s){return lower_bound(A,A+T,s)-A;}
inline void Min(ll &x,ll y){if (y<x) x=y;}
int main()
{
	while (cin>>s[0],s[0][0]!='.'){
		L=s[0].size(),cin>>s[1]>>m,m*=2; rep(i,m) cin>>s[i+2]; m+=2;
		rep(i,21) n[i]=0; rep(i,m) add(s[i]);
		for (int i=L;i;--i) sort(a[i],a[i]+n[i]),n[i]=unique(a[i],a[i]+n[i])-a[i];
		for (L=0;L<s[0].size();){
			A=a[L],T=n[L++];
			rep(i,n[L]) rep(j,n[L])
				d[L][i][j]=a[L][i][0]==a[L][j][0]?d[L-1][get(a[L][i].substr(1))][get(a[L][j].substr(1))]:inf;
			A=a[L],T=n[L];
			rep(i,m) if (i && !(i&1) && s[i].size()==L) Min(d[L][get(s[i])][get(s[i+1])],1);
			rep(k,T) rep(i,T) rep(j,T) Min(d[L][i][j],d[L][i][k]+d[L][k][j]);
		}
		printf("Case %d: ",++Case);
		if (d[L][get(s[0])][get(s[1])]<inf) cout<<d[L][get(s[0])][get(s[1])]<<endl;
		else puts("No solution");
	}
	return 0;
}
