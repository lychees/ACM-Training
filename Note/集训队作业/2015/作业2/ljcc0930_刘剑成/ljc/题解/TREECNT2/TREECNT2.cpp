#include<bits/stdc++.h>
#define rep(i,a,n) for(int _tmp=n,i=a;i<=_tmp;++i)
#define dep(i,a,n) for(int _tmp=n,i=a;i>=_tmp;--i)
#define fec(i,a) for(__typeof a.begin() i=a.begin();i!=a.end();++i)
#define For(i,u) for(int i=H[u];i;i=nxt[i])
#define re(i,a,b) for (int i=a;i<b;++i)
#define si(x) (int)x.size()
#define pb push_back
#define mp make_pair
#define X first
#define Y second
using namespace std;
template<class T> inline void read(T&x){char c;bool fu=0;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x*=-1;}
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z) {read(x,y);read(z);}
typedef long long ll;
typedef pair<int,int> pii;
const int LMT=1000000,N=1000005;
vector<pii> E[N];
int f[N];
inline int get(int x) {return f[x]==x?x:f[x]=get(f[x]);}
int p[N],cnt,pre[N],mu[N];
bool he[N];
inline void sieve(int n) {
	he[1]=1;mu[1]=1;
	rep(i,2,n) {
		if (he[i]==0) p[++cnt]=i,pre[i]=i,mu[i]=-1;
		for (int j=1;j<=cnt&&p[j]*i<=n;++j) {
			he[i*p[j]]=1;pre[i*p[j]]=p[j];
			if(i%p[j]==0)break;
			else mu[i*p[j]]=-mu[i];
		}
	}
}
ll ans[N];
int cc,yz[N],U,V,num[N];
inline void dfs(int now,int sum) {
	if(now==cc+1){
		E[sum].pb(mp(U,V));
		return;
	}
	int tmp=1;
	rep(i,0,num[now]){
		dfs(now+1,sum*tmp);
		tmp*=yz[now];
	}
}
ll Ans;
int n,sz[N];
int to[N],len[N],nxt[N],H[N];
inline void ins(int x,int y,int z) {to[++cnt]=y;len[cnt]=z;nxt[cnt]=H[x];H[x]=cnt;}
int d[N],cou[2][N];
inline void find(int u,int fa,int tp) {
	int v;cou[tp][d[u]]++;
	For(i,u)if((v=to[i])!=fa){
		d[v]=__gcd(d[u],len[i]);
		find(v,u,tp);
	}
}
ll res;
int CNT,val[N];
inline void DFS(int now,int sum) {
	if(now==cc+1){
		val[++CNT]=sum;
		return;
	}
	int tmp=1;
	rep(i,0,num[now]){
		DFS(now+1,sum*tmp);
		tmp*=yz[now];
	}
}
ll tmp[N];int gg;
inline void work(int u,int v,int w,int add=0){
	CNT=0;d[u]=d[v]=w;cc=0;
	for(int t=w;t>1;t=t/pre[t]){
		int x=pre[t];if(yz[cc]!=x)yz[++cc]=x,num[cc]=1;
		else ++num[cc];
	}
	DFS(1,1);
	sort(val+1,val+CNT+1);
	res=0;rep(i,1,CNT)tmp[val[i]]=cou[0][val[i]]=cou[1][val[i]]=0;
	//memset(cou,0,sizeof cou);
	find(u,v,0);find(v,u,1);
	
	dep(i,CNT,1){
		int x=val[i],c0=0,c1=0;
		rep(j,i,CNT)if(val[j]%x==0)c0+=cou[0][val[j]],c1+=cou[1][val[j]];
		//for(int j=x;j<=val[CNT];j+=x)c0+=cou[0][j],c1+=cou[1][j];
		tmp[x]=c0*c1;
		rep(j,i+1,CNT)if(val[j]%x==0)tmp[x]-=tmp[val[j]];
		//c0+=cou[0][val[j]],c1+=cou[1][val[j]];
	//	for(int j=x*2;j<=val[CNT];j+=x)
	//	printf("%d %lld\n",x,tmp[x]);
	}
	res=tmp[1];
	//printf("%lld \n",res);
	if(add)Ans+=res;else Ans-=res;
}
int uu[N],vv[N],ww[N];

int tmpp[N],size;
void divide(vector<int>&V,int w){
	for(int t=w;t>1;){
		int x=pre[t];V.pb(x);
		while(t%x==0)t/=x;
	}
}
void div(int w){
	size=0;
	for(int t=w;t>1;){
		int x=pre[t];tmpp[++size]=x;
		while(t%x==0)t/=x;
	}
}
int sc[2];
inline void dfs(int u,int fa,int st,int tp) {
	int v;
	For(i,u)if((v=to[i])!=fa){
		if(len[i]%st==0)sc[tp]++,dfs(v,u,st,tp);
	}
}
void conquer(int u,int v,int pp,int add=-1) {
	div(pp);int all=1<<size;
	re(S,0,all){
	//	printf(" ::: %d\n",tmp.size());
		int sum=1;
		rep(i,1,size)if(S>>(i-1)&1)sum*=tmpp[i];
		if(sum==1)continue;
		sc[0]=sc[1]=1;
		dfs(v,u,sum,0);
		dfs(u,v,sum,1);
		int tt=sc[0]*sc[1]*add;
		ans[sum]+=tt;
		Ans+=tt*mu[sum];
	}
}
int main() {
//	int t=clock();
	sieve(LMT);cnt=0;int tt=0;
	read(n);rep(i,1,n-1)read(uu[i],vv[i],ww[i]),tt=max(ww[i],tt);
	rep(i,1,n-1){
		int u=uu[i],v=vv[i],w=ww[i];
		cc=0;U=u,V=v;
		for(int t=w;t>1;t=t/pre[t]){
			int x=pre[t];if(yz[cc]!=x)yz[++cc]=x,num[cc]=1;
			else ++num[cc];
		}
		ins(u,v,w);ins(v,u,w);
		dfs(1,1);tt=max(tt,w);
	//	e[i].x=u,e[i].y=v;e[i].len=w;
	}
	rep(i,1,n)f[i]=i,sz[i]=1;
	dep(i,tt,1)if(si(E[i])){
		re(j,0,si(E[i])){
			int x=E[i][j].X,y=E[i][j].Y;
			int p=get(x),q=get(y);
			if(p==q)continue;
			ans[i]+=sz[p]*sz[q];
			f[p]=q;sz[q]+=sz[p];
			//ans[i]+=(ll)sz[q]*(sz[q]-1)/2;
		}
		for(int j=i+i;j<=tt;j+=i)ans[i]-=ans[j];
		re(j,0,si(E[i])){int x=E[i][j].X,y=E[i][j].Y;f[x]=x;f[y]=y;sz[x]=sz[y]=1;}
	}
	//int t=clock();
	Ans=ans[1];
	//	printf("%d\n",clock()-t);
	printf("%lld\n",Ans);
	if(tt<=800000){
		int Q;read(Q);rep(_,1,Q){
			int i,dis;read(i,dis);
			int u=to[i<<1],v=to[(i<<1)-1];
			gg=__gcd(dis,len[i<<1]);int tmp=dis;
			//dis/=gg,len[i<<1]/=gg,len[(i<<1)-1]/=gg;
			
			work(u,v,len[i<<1]);
			work(u,v,dis,1);
			len[i<<1]=len[(i<<1)-1]=tmp;
			printf("%lld\n",Ans);
		}
	} else {
		int Q;read(Q);rep(_,1,Q){
			int i,dis;read(i,dis);
			int u=to[i<<1],v=to[(i<<1)-1];int pp=len[i<<1];
			div(dis);
			int nd=1;
			rep(j,1,size)nd*=tmpp[j];
			dis=nd;
			conquer(u,v,pp);
			conquer(u,v,dis,1);
			len[i<<1]=len[(i<<1)-1]=dis;
			printf("%lld\n",Ans);
		}
	}
		
	return 0;
}
