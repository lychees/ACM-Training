#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0,_=n;i<_;++i)
#define pb push_back
#define mk make_pair
const int N=52*52;
int Case,n,m,u,v,X,Y,now,o,x[N],y[N],h[N],d[N],id[N],ans[N]; bool b[N];
priority_queue<pair<int,int> > H; vector<int> e[N]; char st[5];
int C(char x){return x<'a'?x-65:x-71;}
int get(){scanf("%s",st); int v=C(st[0])*52+C(st[1]); if (id[v]<0) id[v]=now++; return id[v];}
bool cmp(const int i,const int j){return atan2(y[i]-Y,x[i]-X)<atan2(y[j]-Y,x[j]-X);}
void dfs(int i){if (!b[i] || d[i]<=h[i]) return; b[i]=0; rep(k,e[i].size()) dfs(e[i][k]);}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		rep(i,N) b[i]=1,id[i]=-1,e[i].clear(),d[i]=1<<20; now=0,o=0;
		rep(i,n){u=get(),scanf("%d%d%d",x+u,y+u,h+u); if (x[u]<x[o]) o=u;}
		rep(i,m) u=get(),v=get(),e[u].pb(v),e[v].pb(u);
		rep(i,n) X=x[i],Y=y[i],sort(e[i].begin(),e[i].end(),cmp);
		d[o]=h[o],H.push(mk(-d[o],o));
		for (int j=o,i=e[o][0];;j=i,i=e[i][u]){
			rep(k,e[i].size()) if (e[i][k]==j){u=k; break;}
			if (++u==e[i].size()) u=0; d[i]=h[i],H.push(mk(-d[i],i));
			if (i==o && !u) break;
		}
		while (!H.empty()){
			pair<int,int> t=H.top(); H.pop(); int i=t.second;
			if (-t.first==d[i]) rep(k,e[i].size()){
				int j=e[i][k];
				if (max(d[i],h[j])<d[j]) d[j]=max(d[i],h[j]),H.push(mk(-d[j],j));
			}
		}
		int L=0; rep(i,n) if (b[i] && d[i]>h[i]) ans[L++]=d[i],dfs(i);
		printf("Case %d:\n",++Case);
		if (!L) puts("  0"); sort(ans,ans+L); rep(i,L) printf("  %d\n",ans[i]);
	}
	return 0;
}
