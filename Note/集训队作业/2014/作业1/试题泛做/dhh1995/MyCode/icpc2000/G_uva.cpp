#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0,_=n;i<_;++i)
int Case,n,m,x,y,flag,k,c[22],s[22],t[22],d[22],id[6],p[6];
long long f[6],g[6],w[22],E,T,ans; vector<int> a[6]; map<int,int> H;
bool cmp(const int i,const int j){return f[i]==f[j]?g[i]==g[j]?i<j:g[i]<g[j]:f[i]<f[j];}
int main()
{
	while (scanf("%d",&n),n){
		H.clear();
		rep(i,n) scanf("%d%d%d%d%d",&x,c+i,s+i,t+i,d+i),w[i]=0,H[x]=i;
		scanf("%d",&m);
		rep(i,m){
			scanf("%d%d",id+i,&y),a[i].clear(),p[i]=i,f[i]=g[i]=0;
			while (y--) scanf("%d",&x),a[i].push_back(H[x]);
		}
		rep(i,m) rep(j,m-1) if (id[j]>id[j+1]) swap(id[j],id[j+1]),swap(a[j],a[j+1]);
		while (m){
			x=p[0],flag=1,k=-1,E=1LL<<60,ans=f[x];
			rep(i,a[x].size()){
				y=a[x][i],T=1LL*w[y]*d[y]+s[y];
				if (w[y]<c[y])
					if (T<=f[x]){g[x]=f[x],f[x]+=t[y],++w[y],flag=0; break;}
					else if (T<E) E=T,k=y;
			}
			if (flag) if (k<0) swap(p[0],p[m-1]),--m; else f[x]=E;
			sort(p,p+m,cmp);
		}
		printf("Scenario %d: All requests are serviced within %lld minutes.\n",++Case,ans);
	}
	return 0;
}
