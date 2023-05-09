#include<bits/stdc++.h>
using namespace std;
const int N=2e5+4;
int n,m,st[20][N+N],cnt,dfn[N+N],d[N+N];
vector<int>g[N+N];int a[N];
bool cmp(int x,int y){return dfn[x]>dfn[y];}
void dfs(int x,int f){
	st[0][cnt++]=f,dfn[x]=cnt;
	for(auto y:g[x])if(y!=f)d[y]=d[x]+1,dfs(y,x);
}
int lca(int u,int v){
	if(u==v)return u;u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);int t=__lg(v-u);v-=1<<t;
	return cmp(st[t][u],st[t][v])?st[t][v]:st[t][u];
}
int dis(int u,int v){return d[u]+d[v]-d[lca(u,v)]*2;}
void built(int n){
	dfs(1,0);if(n>1)for(int t=1;t<=__lg(n-1);t++)
		for(int i=1,j=1+(1<<t-1),k=1<<t;k<n;i++,j++,k++)
			st[t][i]=cmp(st[t-1][i],st[t-1][j])?st[t-1][j]:st[t-1][i];
}
int A[1<<19],B[1<<19];
void pushup(int i){
	int ls=i<<1,rs=i<<1|1,val=0;
	vector<int>v{A[ls],B[ls],A[rs],B[rs]};
	for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){
		int t=dis(v[a],v[b]);
		if(t>val)val=t,A[i]=v[a],B[i]=v[b];
	}
}
void init(int i,int l,int r){
	if(l!=r){
		int m=l+r>>1;
		init(i<<1,l,m),init(i<<1|1,m+1,r);
		pushup(i);
	}else A[i]=l,B[i]=l+n;
}
void upd(int i,int l,int r,int p){
	if(l!=r){
		int m=l+r>>1;
		if(p<=m)upd(i<<1,l,m,p);
		else upd(i<<1|1,m+1,r,p);
		pushup(i);
	}
}
int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif

	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),g[i].push_back(n+i);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		g[u].push_back(v),g[v].push_back(u);
	}
	built(n+n);
	for(int i=1;i<=n;i++)d[n+i]=d[i]+a[i];
	init(1,1,n);
	scanf("%d",&m);while(m--){
		int x,w;scanf("%d%d",&x,&w);
		d[n+x]-=a[x],d[n+x]+=w,a[x]=w;
		upd(1,1,n,x);int ans;
		int u=A[1],v=B[1],z=dis(u,v);
		if(u>n)u-=n;if(v>n)v-=n;
		if(a[u]*2>=z||a[v]*2>=z)ans=max(a[u],a[v]);
		else{
			if(z%2==0)ans=z/2;
			else ans=(z+1)/2;
		}
		printf("%d\n",ans);
	}
}
