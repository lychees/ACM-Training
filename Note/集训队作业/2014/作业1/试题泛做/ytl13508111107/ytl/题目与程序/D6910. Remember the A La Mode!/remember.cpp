//By ytl 2013-11-21
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define NN 55
#define N (NN*2)
#define M (NN*NN+NN*2)
using namespace std;

int n,m,p[NN];


const double EPS=1e-6;
int dcmp(const double &a,double b=0){
	if (a-b>EPS) return 1;
	if (b-a>EPS) return -1;
	return 0;
}

namespace CostFlow{
	namespace Graph{
		int head[N],gt=1;
		struct Rec{int go,nex,c;double w;}eg[M*2];
		void build(int a,int b,int c,double w){
			eg[++gt]=(Rec){b,head[a],-c,w};
			head[a]=gt;
			eg[++gt]=(Rec){a,head[b],0,-w};
			head[b]=gt;
		}
	}
	using namespace Graph;
	const int inf=0x7fffffff/3;
	double dis[N],cost;
	
	int use[N],pre[N],rec[N],Q[N],K,S,T,flow; 
	bool spfa(){
		for (int i=1;i<=K;i++) dis[i]=inf;
		dis[S]=0;
		Q[1]=S;
		for (int p1=1,p2=1;p1<=p2;p1++){
			int u=Q[p1%K];
			use[u]=0;
			//if (u==T) continue;
			for (int i=head[u];i;i=eg[i].nex){
				int v=eg[i].go;
				if (eg[i].c<0&&dcmp(dis[u]+eg[i].w,dis[v])<0){
					dis[v]=dis[u]+eg[i].w;
					pre[v]=u;
					rec[v]=i;
					if (!use[v]){
						use[v]=1;
						Q[(++p2)%K]=v;
					}
				}
			} 
		}	
		if (dcmp(dis[T],inf)==0) return false;
		return true;
	}
	void run(){
		int x=inf;
		for (int i=T;i!=S;i=pre[i]) if (-eg[rec[i]].c<x) x=-eg[rec[i]].c;
		for (int i=T;i!=S;i=pre[i]) eg[rec[i]].c+=x,eg[rec[i]^1].c-=x;
		flow+=x;
		cost+=x*dis[T];
	}
	double ask(){
		cost=0;flow=0;
		while (spfa()) run();	
		return cost;
	}
	void initCF(int SS,int TT,int KK){
		S=SS;T=TT;K=KK;
	}
}
using namespace CostFlow;
int main(){
	freopen("remember.in","r",stdin);
	freopen("remember.out","w",stdout);
	scanf("%d%d",&n,&m);
	initCF(n+m+1,n+m+2,n+m+2);
	for (int i=1;i<=n;i++){
		scanf("%d",&p[i]);
		build(S,i,p[i],0);
	}
	for (int i=1;i<=m;i++){
		int x;
		scanf("%d",&x);
		build(i+n,T,x,0);
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			double x;
			scanf("%lf",&x);
			if (x!=-1) build(i,j+n,p[i],x);
		}
	double ansMin=ask();
	for (int i=2;i<=gt;i+=2){
		eg[i].c+=eg[i^1].c;
		eg[i^1].c=0;
		eg[i].w=-eg[i].w;
		eg[i^1].w=-eg[i^1].w;
	}
	double ansMax=ask();
	printf("%.2lf to %.2lf\n",ansMin,-ansMax);
	return 0;
}
