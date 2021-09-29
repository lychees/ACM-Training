//By ytl 2013-11-21
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 105
#define NN (N*N)
#define M 1005
using namespace std;

const int INF=0x7fffffff/3;

int n,m,po,w[N][N],num[N][N];

namespace Graph{
	int head[NN],head1[N],head2[N],gt=1,gt1=1,gt2=1;
	struct Rec{int go,nex,c;}eg[N*N+2*N*M],eg1[M],eg2[M];
	void build(int a,int b,int c){
		if (a==b) return;
		eg[++gt]=(Rec){b,head[a],c};
		head[a]=gt;
	}
	void build1(int a,int b,int c){
		eg1[++gt1]=(Rec){b,head1[a],c};
		head1[a]=gt1;
	}
	void build2(int a,int b,int c){
		eg2[++gt2]=(Rec){b,head2[a],c};
		head2[a]=gt2;
	}
	void initGraph(){
		memset(head,0,sizeof(head));
		memset(head1,0,sizeof(head1));
		memset(head2,0,sizeof(head2));
		gt=gt1=gt2=1;
	}
}
using namespace Graph;

int dis[NN],Q[NN],use[NN];

void spfa(int S){
	for (int i=1;i<=po;i++) dis[i]=INF;
	dis[S]=0;
	Q[1]=S;
	for (int p1=1,p2=1;p1<=p2;p1++){
		int u=Q[p1%po];
		if (rand()%2||(p1&1)) {Q[(++p2)%po]=u;continue;}
		use[u]=0;
		for (int i=head[u];i;i=eg[i].nex){
			int v=eg[i].go;
			if (dis[u]+eg[i].c<dis[v]){
				dis[v]=dis[u]+eg[i].c;
				if (!use[v]){
					use[v]= 1;
					Q[(++p2)%po]=v;
				}
			}
		}
	}
	
}

void Floyd(){
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++) if (i!=k)
			for (int j=1;j<=n;j++) if (j!=i&&j!=k)
				w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
}
void buildEdge(){
	po=0;
	for (int i=1;i<=n;i++) 
		for (int j=1;j<=n;j++)
			num[i][j]=++po;
	if (!po) po++;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			for (int k=head1[i];k;k=eg1[k].nex) 
				if (eg1[k].go!=j) build(num[i][j],num[eg1[k].go][j],1);
				else build(num[i][j],num[eg1[k].go][j],0);
			for (int k=head2[j];k;k=eg2[k].nex)
				if (eg2[k].go!=i) build(num[i][j],num[i][eg2[k].go],1);
				else build(num[i][j],num[i][eg2[k].go],0);			
			build(num[i][j],num[j][i],w[i][j]-1);
		}
}
void init(){
	initGraph();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) 
			w[i][j]=INF;
	for (int i=1;i<=n;i++) w[i][i]=0;
}
int main(){
	freopen("routing.in","r",stdin);
	freopen("routing.out","w",stdout);
	int cas=0;
	while (scanf("%d%d",&n,&m)!=EOF&&(n||m)){
		init();
		for (int i=1;i<=m;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			w[a][b]=1;
			build1(a,b,1);
			build2(b,a,1);
		}
		Floyd();
		buildEdge();
		spfa(num[1][1]);
		printf("Network %d\n",++cas);
 		if (dis[num[2][2]]!=INF) printf("Minimum number of nodes = %d\n",dis[num[2][2]]+1);
		else printf("Impossible\n");
		printf("\n");
	}
	return 0;
}
