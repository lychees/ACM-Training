#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#define X first
#define Y second
#define mp make_pair
#define ph push
#define pb push_back
#define rep(i,a,n) for(int _tmp=n,i=a;i<=_tmp;++i)
#define dep(i,a,n) for(int _tmp=n,i=a;i>=_tmp;--i)
#define ALL(x,S) for(__typeof((S).end()) x=S.begin();x!=S.end();x++)
#define eps 1e-8
#define pi 3.1415926535897
#define sqr(x) ((x)*(x))
#define MAX(a,b) a=max(a,b)
#define MIN(a,b) a=min(a,b)
#define SZ(x) ((int)(x).size())
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define CLR(a) memset(a,0,sizeof(a))
#define POSIN(x,y) (1<=(x)&&(x)<=n&&1<=(y)&&(y)<=m)
#define all(x) (x).begin(),(x).end()
#define COUT(S,x) cout<<fixed<<setprecision(x)<<S<<endl
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<lf,lf> pff;
typedef complex<double> CD;
const int inf=0x20202020;
const int mod=1000000009;
template<class T> inline void read(T&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
template<class T> inline void read(T&x,T&y,T&z,T&q){read(x);read(y);read(z);read(q);}
const int DX[]={1,0,-1,0},DY[]={0,1,0,-1};
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//*******************************************
 
const int N=111111,M=31111111;
int l,m,n,t,tot,x,lastans,y,ver,tver;
int fa[N],dep[N],hson[N],top[N],dfn[N],lend[N],zend[N],bz[N][22],sz[N],root[N];
ll FIBO[N*2],*f=FIBO+N;
vector<int>a[N];
char s[9];
struct Node{int l,r,v[3],V[3],ver;}T[M];
int query(int x,int ty,int p,int L=0,int R=n+1){
	if(!x)return 0;if(L==R)return T[x].v[ty];int mid=L+R>>1;
	if(p<=mid)return query(T[x].l,ty,p,L,mid);
	else return (query(T[x].r,ty,p,mid+1,R)+T[T[x].l].v[ty])%mod;
}
	int query2(int x,int ty,int p,int L=0,int R=n+1){
		if(!x)return 0;if(L==R)return T[x].V[ty];int mid=L+R>>1;
		if(p<=mid)return query2(T[x].l,ty,p,L,mid);
		else return (query2(T[x].r,ty,p,mid+1,R)+T[T[x].l].V[ty])%mod;
	}
int query(int ro,int x){
	ll res=f[x+4]*query(ro,0,x)+f[x+3]*query(ro,1,x)+query(ro,2,x);
	res%=mod;if(res<0)res+=mod;return res;
}
	int query2(int ro,int x){
		ll res=f[x+4]*query2(ro,0,x)+f[x+3]*query2(ro,1,x)+query2(ro,2,x);
		res%=mod;if(res<0)res+=mod;return res;
	}
int que(int ro,int l,int r){
	int res=query(ro,r)-query(ro,l-1);if(res<0)res+=mod;
	res=(res+query2(ro,n-l+2)-query2(ro,n-r+1))%mod;if(res<0)res+=mod;
	return res;
}
void add(int x,int ty,int p,int v,int L=0,int R=n+1){
	//if(L==1&&R==n)printf("%d %d %d %d\n",x,ty,p,v);
	T[x].v[ty]=(T[x].v[ty]+v)%mod;if(L==R)return;int mid=L+R>>1;
	if(p<=mid){
		if(T[T[x].l].ver!=T[x].ver)T[++tot]=T[T[x].l],T[x].l=tot,T[T[x].l].ver=T[x].ver;
		add(T[x].l,ty,p,v,L,mid);
	}else{
		if(T[T[x].r].ver!=T[x].ver)T[++tot]=T[T[x].r],T[x].r=tot,T[T[x].r].ver=T[x].ver;
		add(T[x].r,ty,p,v,mid+1,R);
	}
}
	void add2(int x,int ty,int p,int v,int L=0,int R=n+1){
		//if(L==1&&R==n)printf("%d %d %d %d\n",x,ty,p,v);
		T[x].V[ty]=(T[x].V[ty]+v)%mod;if(L==R)return;int mid=L+R>>1;
		if(p<=mid){
			if(T[T[x].l].ver!=T[x].ver)T[++tot]=T[T[x].l],T[x].l=tot,T[T[x].l].ver=T[x].ver;
			add2(T[x].l,ty,p,v,L,mid);
		}else{
			if(T[T[x].r].ver!=T[x].ver)T[++tot]=T[T[x].r],T[x].r=tot,T[T[x].r].ver=T[x].ver;
			add2(T[x].r,ty,p,v,mid+1,R);
		}
	}
/*void modi(int l,int r){
	a.add(l,(l&1)?f[l]:-f[l]);b.add(l,(l&1)?-f[l+1]:f[l+1]);c.add(l,-1);
	a.add(r,(l&1)?-f[l]:f[l]);b.add(r,(l&1)?f[l+1]:-f[l+1]);c.add(r,f[r-l+3]);
}*/
void modi(int ro,int L,int R,int st){
	//printf("%d %d %d\n",L,R,st);
	int l=L-st+1,r=R;
	add(ro,0,r,(l&1)?-f[l]:f[l]);add(ro,1,r,(l&1)?f[l+1]:-f[l+1]);add(ro,2,r,f[r-l+3]);
	r=L-1;
	add(ro,0,r,(l&1)?f[l]:-f[l]);add(ro,1,r,(l&1)?-f[l+1]:f[l+1]);add(ro,2,r,-f[r-l+3]);
}
	void modi2(int ro,int L,int R,int st){
		//printf("%d %d %d\n",L,R,st);
		L=n-L+2;R=n-R+2;swap(L,R);
		int l=L-st+1,r=R;
		add2(ro,0,r,(l&1)?-f[l]:f[l]);add2(ro,1,r,(l&1)?f[l+1]:-f[l+1]);add2(ro,2,r,f[r-l+3]);
		r=L-1;
		add2(ro,0,r,(l&1)?f[l]:-f[l]);add2(ro,1,r,(l&1)?-f[l+1]:f[l+1]);add2(ro,2,r,-f[r-l+3]);
	}
void dfs(int x,int f){
	sz[x]=1;fa[x]=f;dep[x]=dep[f]+1;
	rep(i,0,SZ(a[x])-1)if(a[x][i]!=f){
		dfs(a[x][i],x);sz[x]+=sz[a[x][i]];if(sz[a[x][i]]>sz[hson[x]])hson[x]=a[x][i];
	}
}
void DFS(int x,int f){
	top[x]=f;dfn[x]=++tot;zend[x]=tot;if(!hson[x]){lend[f]=tot;return;}
	DFS(hson[x],f);rep(i,0,SZ(a[x])-1)if(a[x][i]!=fa[x]&&a[x][i]!=hson[x])DFS(a[x][i],a[x][i]);
	zend[x]=tot;
}
int lca(int x,int y){
	if(dep[x]>dep[y])swap(x,y);dep(i,20,0)if(bz[y][i]&&dep[bz[y][i]]>=dep[x])y=bz[y][i];
	if(x==y)return x;
	dep(i,20,0)if(bz[x][i]!=bz[y][i])x=bz[x][i],y=bz[y][i];return fa[x];
}
int main()
{
	scanf("%d%d",&n,&m);
	f[1]=f[2]=1;rep(i,3,n+10)f[i]=(f[i-1]+f[i-2])%mod;
	dep(i,0,-n-10)f[i]=(f[i+2]-f[i+1]+mod)%mod;
	//rep(i,1,n+10)swap(f[i],f[-i]);
	rep(i,1,n-1)scanf("%d%d",&l,&t),a[l].pb(t),a[t].pb(l);
	dep[1]=1;dfs(1,0);DFS(1,1);
	rep(i,1,n)bz[i][0]=fa[i];rep(i,1,20)rep(j,1,n)bz[j][i]=bz[bz[j][i-1]][i-1];
	//rep(i,1,n)printf("%d %d %d %d\n",i,dfn[i],lend[i],zend[i]);
	//modi2(root[ver],2,5,1);rep(i,0,6)printf("%d %d\n",i,que(root[ver],i,i));return 0;
	rep(_,1,m){
		T[++tot]=T[root[_-1]];root[_]=tot;T[root[_]].ver=_;ver=_;
		scanf("%s%d",s,&x);x^=lastans;
		if(s[0]=='A'){
			scanf("%d",&y);int p=lca(x,y),t2=dep[x]+dep[y]-dep[p]*2+1,t1=1;
			while(top[x]!=top[y]){
				int _x=top[x],_y=top[y];
				if(dep[_x]>dep[_y]){
					modi2(root[ver],dfn[_x],dfn[x],t1);t1+=dep[x]-dep[_x]+1;x=fa[top[x]];
				}else{
					t2-=dep[y]-dep[_y];modi(root[ver],dfn[_y],dfn[y],t2);t2--;y=fa[top[y]];
				}
			}if(dep[x]<dep[y])modi(root[ver],dfn[x],dfn[y],t1);
			else modi2(root[ver],dfn[y],dfn[x],t1);
		}else if(s[0]=='R'){
			T[tot]=T[root[x]];T[root[_]].ver=_;
		}else if(s[1]=='S'){
			scanf("%d",&y);
			if(x==y)printf("%d\n",lastans=que(root[ver],dfn[1],zend[1]));
			else if(lca(x,y)==y){
				int p=x;dep(i,20,0)if(bz[p][i]&&dep[bz[p][i]]>dep[y])p=bz[p][i];
				printf("%d\n",lastans=(que(root[ver],dfn[1],zend[1])-que(root[ver],dfn[p],zend[p])+mod)%mod);
			}else printf("%d\n",lastans=que(root[ver],dfn[y],zend[y]));
		}else{
			scanf("%d",&y);int ans=0;
			while(top[x]!=top[y]){
				int _x=top[x],_y=top[y];if(dep[_x]<dep[_y])swap(x,y),swap(_x,_y);
				ans=(ans+que(root[ver],dfn[_x],dfn[x]))%mod;
				x=fa[top[x]];
			}if(dep[x]<dep[y])swap(x,y);ans=(ans+que(root[ver],dfn[y],dfn[x]))%mod;
			printf("%d\n",lastans=ans);
		}
	}
	//rep(i,1,n)printf("%d\n",que(root[ver],dfn[i],dfn[i]));
	return 0;
} 
