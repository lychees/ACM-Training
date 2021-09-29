#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

template<class T>
inline void maxi(T &a,const T b){
	if(b>a) a=b;
}

const int N=52,K=4,M=1005,P=10005;

const ll inf=ll(1e18);

int n,k,m,p,W;

namespace dinic{
	const int sizeV=2+M+P*2,sizeE=M+P*6+K;
	typedef ll capType;
	const capType inf=::inf;
	#define nonzero(x) bool(x)
	struct node;
	struct edge{
		node *ed;
		edge *next;
		capType cap;
	} E[sizeE<<1],*newE=E;
	struct node{
		edge *son;
		int lab;
	} S[2],*T=S+1;
	bool layer(){
		static node *q[sizeV];
		static int head=0,tail=0;
		while(tail) q[--tail]->lab=0;
		head=0;
		q[tail++]=S;
		S->lab=1;
		while(head!=tail){
			node *u=q[head++];
			for(edge *e=u->son;e;e=e->next) if(nonzero(e->cap)){
				node *v=e->ed;
				if(v->lab) continue;
				v->lab=u->lab+1;
				q[tail++]=v;
				if(v==T)
					return true;
			}
		}
		return false;
	}
	capType flow(node *u,const capType F){
		if(u==T) return F;
		capType left=F;
		for(edge *e=u->son;e&&nonzero(left);e=e->next) if(nonzero(e->cap)){
			node *v=e->ed;
			if(v->lab!=u->lab+1) continue;
			capType f=flow(v,min(left,e->cap));
			e->cap-=f;
			E[(e-E)^1].cap+=f;
			left-=f;
		}
		if(!nonzero(F-left)) u->lab=0;
		return F-left;
	}
	capType maxflow(){
		capType ans=0,f;
		while(layer())
			while(nonzero((f=flow(S,inf))))
				ans+=f;
		return ans;
	}
	void addedge(node *u,node *v,const capType cap0,const capType cap1=0){
		*newE=(edge){v,u->son,cap0},u->son=newE++;
		*newE=(edge){u,v->son,cap1},v->son=newE++;
	}
	void deledge(){
		newE-=2;
		newE[1].ed->son=newE[0].next;
		newE[0].ed->son=newE[1].next;
	}
}

int c[M];

dinic::node V[M],U[P][2];

bool vis[M];
bool visE[P];

ll cap[dinic::sizeE*2];

struct edge{
	int ed;
	int w;
	edge *next;
} E[P<<1],*son[M];

int id[K][N];
ll f[N][K*N][1<<K];
ll g[1<<K];

ll tot;

int cnt[1<<K];

void dfs(int u){
	if(vis[u]) return;
	vis[u]=true;
	dinic::addedge(dinic::S,&V[u],c[u]);
	for(edge *e=son[u];e;e=e->next) if(!visE[(e-E)>>1]){
		visE[(e-E)>>1]=true;
		int v=e->ed;
		int a=e->w,b=E[(e-E)^1].w;
		if(a<b) swap(a,b);
		tot+=W*(a+b);
		dinic::addedge(dinic::S,&U[(e-E)>>1][0],W*a);
		dinic::addedge(&U[(e-E)>>1][0],&V[u],dinic::inf);
		dinic::addedge(&U[(e-E)>>1][0],&V[v],dinic::inf);
		dinic::addedge(&V[u],&U[(e-E)>>1][1],dinic::inf);
		dinic::addedge(&V[v],&U[(e-E)>>1][1],dinic::inf);
		dinic::addedge(&U[(e-E)>>1][1],dinic::T,W*b);
		dfs(v);
	}
}

ll work(){
	for(int i=1;i<=m;i++) vis[i]=false;
	for(int i=0;i<p;i++) visE[i]=false;
	for(int i=1;i<=m;i++) V[i].son=NULL;
	for(int i=0;i<p;i++) U[i][0].son=U[i][1].son=NULL;
	for(int i=1;i<=n;i++){
		dinic::newE=dinic::E;
		dinic::S->son=NULL;
		dinic::T->son=NULL;
		tot=0;
		for(int j=0;j<k;j++)
			dfs(id[j][i]);
		for(int j=0;j<dinic::newE-dinic::E;j++) cap[j]=dinic::E[j].cap;
		for(int s=0;s<1<<k;s++){
			for(int j=0;j<dinic::newE-dinic::E;j++) dinic::E[j].cap=cap[j];
			for(int j=0;j<k;j++){
				if(!(s>>j&1))
					dinic::addedge(dinic::S,&V[id[j][i]],dinic::inf);
				else
					dinic::addedge(&V[id[j][i]],dinic::T,dinic::inf);
			}
			g[s]=tot-dinic::maxflow();
			for(int j=0;j<k;j++) dinic::deledge();
		}
		
		if(i==1){
			for(int s=0;s<1<<k;s++) f[1][0][s]=g[s];
		}
		else{
			for(int j=0;j<=(i-1)*k;j++)
				for(int t=0;t<1<<k;t++)
					f[i][j][t]=-inf;
			for(int j=0;j<=(i-2)*k;j++)
				for(int s=0;s<1<<k;s++)
					for(int t=0;t<1<<k;t++)
						maxi(f[i][j+cnt[s^t]][t],f[i-1][j][s]+g[t]);
		}
	}
	ll ans=-inf;
	for(int j=0;j<=(n-1)*k;j++) if(int(10*log(1+j)+1e-9)==W)
		for(int s=0;s<1<<k;s++)
			maxi(ans,f[n][j][s]);
	for(int i=0;i<p;i++) if(!visE[i])
		ans+=W*E[i<<1].w;
	return ans;
}

int main(){
	scanf("%d%d%d%d",&n,&k,&m,&p);
	scanf("%*s");
	for(int i=1;i<=m;i++) scanf("%d",&c[i]);
	for(int j=0;j<k;j++)
		for(int i=1;i<=n;i++) scanf("%d",&id[j][i]);
	for(int i=0;i<p;i++){
		int x,y,a,b; db d; scanf("%d%d%d%lf",&x,&y,&a,&d);
		b=int(a*d+1e-9);
		E[i<<1|0]=(edge){y,a,son[x]},son[x]=&E[i<<1|0];
		E[i<<1|1]=(edge){x,b,son[y]},son[y]=&E[i<<1|1];
	}
	for(int i=1;i<1<<k;i++) cnt[i]=cnt[i>>1]+(i&1);
	ll ans=0;
	for(W=0;W<=int(10*log(1+k*(n-1))+1e-9);W++)
		ans=max(ans,work());
	printf("%lld\n",ans);
}