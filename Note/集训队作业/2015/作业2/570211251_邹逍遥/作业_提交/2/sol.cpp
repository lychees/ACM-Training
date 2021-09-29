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
const int mod=1000000007;
template<class T> inline void read(T&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
template<class T> inline void read(T&x,T&y,T&z,T&q){read(x);read(y);read(z);read(q);}
const int DX[]={1,0,-1,0},DY[]={0,1,0,-1};
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//*******************************************
 
const int N=111111,M=2222222;
int l,m,n,t,C,xtot,tot,nn;
int fa[N],dep[N],bz[N][22],dfsx[N];
struct zcc{int x,y,z,f;
zcc(){}
zcc(int _x,int _y,int _z,int _f):x(_x),y(_y),z(_z),f(_f){}
}Q[M];
vector<int>df[N];
inline bool cmpy(const int &a,const int &b){return Q[a].y<Q[b].y;}
vector<int>a[N],ask[N];
void dfs(int x,int f){
	fa[x]=f;dep[x]=dep[f]+1;dfsx[x]=++xtot;
	rep(i,0,SZ(a[x])-1)if(a[x][i]!=f)dfs(a[x][i],x);
}
int lca(int x,int y){
    if(dep[x]>dep[y])swap(x,y);
    dep(i,20,0)if(dep[y]-(1<<i)>=dep[x])y=bz[y][i];
    if(x==y)return x;
    dep(i,20,0)if(bz[x][i]!=bz[y][i])x=bz[x][i],y=bz[y][i];
    return fa[y];
}
int syb[N],tmp[N],TMP[N],inq[N],now;
inline bool cmpdfsx(const int &a,const int &b){return dfsx[a]<dfsx[b];}
inline bool cmpsyb(const int &a,const int &b){return syb[a]<syb[b];}
vector<int>vec[N];
stack<int>S;
queue<int>q;
void add(int x,int y){if(x==y)return;vec[x].pb(y);vec[y].pb(x);}
void adask(int p,int x,int y,int z,int f){if(y<=0)return;Q[++tot]=zcc(x,y,z,f);ask[p].pb(tot);}
void DFS(int x,int f){
	adask(now,x,syb[x],0,1);
	rep(i,0,SZ(vec[x])-1)if(vec[x][i]!=f){
		int y=vec[x][i],len=abs(dep[x]-dep[y]);
		if(syb[x]-len>syb[y]){
			adask(now,y,syb[y],0,-1);
			syb[y]=syb[x]-len;
		}else if(syb[x]+syb[y]-len>0){
			int p=((dep[x]>dep[y]?syb[x]-syb[y]:syb[y]-syb[x])+len)/2,t=dep[x]>dep[y]?x:y;
			dep(i,20,0)if(p&(1<<i))t=bz[t][i];
			adask(now,t,(syb[x]+syb[y]-len)/2,0,-1);
		}
		DFS(y,x);
	}
}
void work(int x){
	int m=SZ(ask[x]),tot;
	now=x;
	rep(i,0,m-1)tmp[i+1]=Q[ask[x][i]].x,syb[Q[ask[x][i]].x]=Q[ask[x][i]].y;
	sort(tmp+1,tmp+1+m,cmpdfsx);
	tot=m;rep(i,1,m-1){
		int p=lca(tmp[i],tmp[i+1]);
		if(!syb[p])tmp[++tot]=p;
	}m=tot;
	sort(tmp+1,tmp+1+m,cmpdfsx);
	m=unique(tmp+1,tmp+1+m)-tmp-1;
	rep(i,1,m)vec[tmp[i]].clear();
	while(!S.empty())S.pop();S.push(tmp[1]);int lst=tmp[1];
	rep(i,2,m){
		while(!S.empty()&&lca(S.top(),tmp[i])!=S.top())lst=S.top(),S.pop();
		if(S.empty())add(tmp[i],lst);
		else add(tmp[i],S.top());
		S.push(tmp[i]);
	}
	rep(i,1,m)TMP[i]=tmp[i];sort(TMP+1,TMP+1+m,cmpsyb);
	dep(i,m,1)q.push(tmp[i]),inq[tmp[i]]=1;
	while(q.size()){
		int k=q.front();q.pop();inq[k]=0;
		rep(i,0,SZ(vec[k])-1)if(syb[k]-abs(dep[k]-dep[vec[k][i]])>syb[vec[k][i]]){
			syb[vec[k][i]]=syb[k]-abs(dep[k]-dep[vec[k][i]]);
			if(!inq[vec[k][i]])q.push(vec[k][i]);
		}
	}
	DFS(tmp[1],0);
	rep(i,0,SZ(ask[x])-1)syb[Q[ask[x][i]].x]=0;
}
int icnt;
int sz[N],msz[N],ini[N],b[N],num[N],pdep[N],ndep[N];
vector<vector<int> >ans;
void dafs(int x,int f){
    sz[x]=1;msz[x]=0;ini[++icnt]=x;
    rep(i,0,a[x].size()-1){
        if(b[a[x][i]]||a[x][i]==f)continue;
        dafs(a[x][i],x);sz[x]+=sz[a[x][i]];msz[x]=max(msz[x],sz[a[x][i]]);
    }
}
int find(int x){
    icnt=0;dafs(x,0);if(icnt==0)return 0;
    int min1=n,min2;rep(i,1,icnt){
        msz[ini[i]]=max(msz[ini[i]],icnt-1-sz[ini[i]]);
        if(msz[ini[i]]<min1)min1=msz[ini[i]],min2=i;
    }return ini[min2];
}
void dfs1(int x,int f,int p){
	num[x]=p;pdep[x]=pdep[f]+1;if(x<=nn)
	ndep[pdep[x]]++;
	rep(i,0,SZ(a[x])-1)if(a[x][i]!=f&&!b[a[x][i]])dfs1(a[x][i],x,p);
}
void dfs2(int x,int f){
	rep(i,0,SZ(df[x])-1)if(Q[df[x][i]].y>pdep[x])Q[df[x][i]].z+=ans[num[x]][min(Q[df[x][i]].y-pdep[x]-1,icnt)];
	rep(i,0,SZ(a[x])-1)if(a[x][i]!=f&&!b[a[x][i]])dfs2(a[x][i],x);
}
void cut(int x){
	/*
	printf("====================%d=======================\n",x);
	rep(i,1,m){
		printf("%d\n",i);
		rep(j,0,SZ(ask[i])-1)printf("%d %d %d %d\n",Q[ask[i][j]].x,Q[ask[i][j]].y,Q[ask[i][j]].z,Q[ask[i][j]].f);
	}
	*/
    b[x]=1;pdep[x]=0;ans.clear();rep(i,0,SZ(a[x]))ans.pb(vector<int>());
    rep(i,0,SZ(a[x])-1)if(!b[a[x][i]]){
    	rep(_,1,icnt)ndep[_]=0;
		dfs1(a[x][i],x,i);
		rep(j,0,icnt){
			ans[i].pb(-ndep[j]);
			if(SZ(ans[SZ(a[x])])<=icnt)ans[SZ(a[x])].pb(ndep[j]);
			else ans[SZ(a[x])][j]+=ndep[j];
		}
	}if(!SZ(ans[SZ(a[x])])){if(x<=nn)rep(i,0,SZ(df[x])-1)Q[df[x][i]].z++;return;}
	ans[SZ(a[x])][0]=(x<=nn);
	rep(i,0,SZ(a[x])-1)if(!b[a[x][i]])rep(j,0,icnt)ans[i][j]+=ans[SZ(a[x])][j];
	rep(i,0,SZ(a[x]))if(i==SZ(a[x])||!b[a[x][i]])rep(j,1,icnt)ans[i][j]+=ans[i][j-1];
	num[x]=SZ(a[x]);dfs2(x,0);
    rep(i,0,SZ(a[x])-1)if(!b[a[x][i]])cut(find(a[x][i]));
}
int main()
{
	scanf("%d",&n);rep(i,1,n-1)scanf("%d%d",&l,&t),a[l].pb(i+n),a[t].pb(i+n),a[i+n].pb(l),a[i+n].pb(t);
	nn=n;n=n+n-1;
	dfs(1,0);rep(i,1,n)bz[i][0]=fa[i];rep(i,1,20)rep(j,1,n)bz[j][i]=bz[bz[j][i-1]][i-1];
	scanf("%d",&m);rep(i,1,m){
		scanf("%d",&t);
		rep(j,1,t){
			++tot;scanf("%d%d",&Q[tot].x,&Q[tot].y);Q[tot].y=Q[tot].y*2+1;Q[tot].f=0;
			ask[i].pb(tot);
		}
		work(i);
		//printf("%d\n",i);
		//rep(j,0,SZ(ask[i])-1)printf("%d %d %d %d\n",Q[ask[i][j]].x,Q[ask[i][j]].y,Q[ask[i][j]].z,Q[ask[i][j]].f);
		rep(j,0,SZ(ask[i])-1)df[Q[ask[i][j]].x].pb(ask[i][j]);
	}
	rep(i,1,n)sort(df[i].begin(),df[i].end(),cmpy);
	cut(find(1));
	/*
	puts("=============================================");
	rep(i,1,m){
		printf("%d\n",i);
		rep(j,0,SZ(ask[i])-1)printf("%d %d %d %d\n",Q[ask[i][j]].x,Q[ask[i][j]].y,Q[ask[i][j]].z,Q[ask[i][j]].f);
	}
	*/
	rep(i,1,m){
		int ans=0;
		rep(j,0,SZ(ask[i])-1)ans+=Q[ask[i][j]].z*Q[ask[i][j]].f;
		printf("%d\n",ans);
		//printf("%d\n",(ans+1)/2);
	}
	return 0;
} 
