#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
typedef long long ll;
const ll N=205,inf=1LL<<55; map<string,int> H;
string s1[N],s[N],t; int Case,n,m,tmp,a[N],p[N],q[N],L1[N],L[N],c[N][N]; ll d[N][N];
int get(string t,bool flag)
{
	if (H.find(t)==H.end()) if (flag) return -1; else return L1[n]=t.size(),s1[n]=t,H[t]=n++;
	return H[t];
}
bool check(int i,int j,int k)
{
	int x=min(L[i],L[j]);
	return s[i].substr(L[i]-x,L[i]-L[k])==s[j].substr(L[j]-x,L[j]-L[k]);
}
bool cmp(const int i,const int j){return L1[i]<L1[j];}
int main()
{
	freopen("K.in","r",stdin);
	freopen("K.out","w",stdout);
	while (cin>>t,t[0]!='.'){
		H.clear(),n=0,a[0]=get(t,0),cin>>t>>m,a[1]=get(t,0); rep(i,m*2) cin>>t,a[i+2]=get(t,0);
		rep(i,n) rep(j,n) d[i][j]=i==j?0:inf; 
		rep(i,n) p[i]=i; sort(p,p+n,cmp);
		rep(i,n) L[i]=L1[p[i]],s[i]=s1[p[i]],q[p[i]]=i; rep(i,m*2+2) a[i]=q[a[i]];
		rep(i,n) cout<<p[i]<<" "<<s[i]<<endl;
		rep(i,n) rep(j,n) if (L[i]>=L[j]) tmp=get(s[i].substr(L[i]-L[j]),1),c[i][j]=tmp<0?-1:q[tmp];
//		rep(i,m*2+2) printf("%d ",a[i]); puts("");
		rep(i,m) d[a[i*2+2]][a[i*2+3]]=min(d[a[i*2+2]][a[i*2+3]],1ll);
//		rep(i,n){rep(j,n) printf("%2lld ",d[i][j]>99?99:d[i][j]); puts("");}
		rep(k,n) rep(i,n) if (L[i]>=L[k] && c[i][k]>=0)
			rep(j,n) if (L[j]>=L[k] && c[j][k]>=0 && check(i,j,k))
				d[i][j]=min(d[i][j],d[c[i][k]][k]+d[k][c[j][k]]);//,printf("%d %d %d %d\n",k,i,j,d[i][j]);
//		puts("");
		rep(i,n){cout<<s[i]<<" "; rep(j,n) printf("%2lld ",d[i][j]>99?99:d[i][j]); puts("");}
		printf("Case %d: ",++Case);
		if (d[a[0]][a[1]]<inf) cout<<d[a[0]][a[1]]<<endl; else puts("No solution");
	}
	return 0;
}
