//By ytl 2013-11-18
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 55
#define M (N*N)
using namespace std;

const int INF=0x7fffffff/3;

struct data{int a,b,c;}edge[M];
int n,m,k,ans,recTot,S;
int use[N],ff[N],rec[N],fa[N],must[N];

void print(int a[],int n){
	for (int i=1;i<=n;i++) printf("%d ",a[i]);
	printf("\n");
}

namespace Graph{
	int head[N],gt=1;
	struct Rec{int go,nex;}eg[M*2];
	void build(int a,int b){
		eg[++gt]=(Rec){b,head[a]};
		head[a]=gt;
	}
}
using namespace Graph;

bool cmp(const data &a,const data &b){
	return a.c<b.c;
}

int find(int a){
	if (ff[a]==a) return a;
	ff[a]=find(ff[a]);
	return ff[a];
}
void check(){
	int all=0,x=0,tot=0;
	for (int i=1;i<=n;i++) if (use[i]) all++,ff[i]=i;
	for (int i=1;i<=m;i++){
		int a=edge[i].a,b=edge[i].b,c=edge[i].c;
		if (use[a]&&use[b]&&find(a)!=find(b)){
			ff[find(a)]=find(b);
			x+=c;
			tot++;
			if (tot==all-1) break;
		}
	}
	if (tot==all-1){
		if (x<ans||(x==ans&&tot<recTot)){
			ans=x;
			recTot=tot;
			memcpy(rec,use,sizeof(use));
		}
		return;
	}
}
void deal(){
	for (int i=1;i<=n;i++) ff[i]=i;
	for (int i=1;i<=m;i++){
		int a=edge[i].a,b=edge[i].b;
		if (rec[a]&&rec[b]&&find(a)!=find(b)){
			ff[find(a)]=find(b);
			build(a,b);
			build(b,a);
		}
	}
}

void search(int now){
	if (now==n+1){
		check();
		return;
	}
	if (use[now]==2){
		search(now+1);
		return;
	}
	use[now]=1;
	search(now+1);
	use[now]=0;
	search(now+1);
}
void dfs(int p){
	use[p]=1;
	for (int i=head[p];i;i=eg[i].nex) if (rec[eg[i].go]&&!use[eg[i].go]){
		dfs(eg[i].go);
		fa[eg[i].go]=p;
	}
}
int main(){
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	scanf("%d%d%d",&n,&S,&m);
	for (int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		edge[i].a=a;edge[i].b=b;edge[i].c=c;	
	}
	scanf("%d",&k);
	for (int i=1;i<=k;i++){
		scanf("%d",&must[i]);
	}
	sort(edge+1,edge+m+1,cmp);
	for (int i=1;i<=k;i++) use[must[i]]=2;
	use[S]=2;
	ans=INF;
	search(1);
	deal();
	for (int i=1;i<=n;i++) use[i]=0;
	dfs(S);
	printf("distance = %d\n",ans);
	for (int i=1;i<=k;i++){
		printf("%d",must[i]);
		for (int j=fa[must[i]];j;j=fa[j]) printf("-%d",j);
		printf("\n");
	}
	return 0;
}
