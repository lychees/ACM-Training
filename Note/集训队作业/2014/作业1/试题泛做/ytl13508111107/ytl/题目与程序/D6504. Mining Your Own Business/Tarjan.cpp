#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 50005
using namespace std;
typedef long long LL;

namespace Graph{
	int head[N],p=1;
	struct Rec{int go,nex;}eg[N*2];
	void build(int a,int b){
		eg[++p]=(Rec){b,head[a]};
		head[a]=p;
	}
}
using namespace Graph;

namespace Tarjan{
	struct Edge{int x,y;}stack[N*2];
	vector<int> bcc[N];
	int use[N],dfn[N],low[N],po,pp,root;
	int isCut[N],cutTot,color[N],bccTot;
	void search(int p,int tfa){
		use[p]=1;
		dfn[p]=low[p]=++po;
		int tot=0;
		for (int i=head[p];i;i=eg[i].nex) if (eg[i].go!=tfa){
			if (use[eg[i].go]==1){
				if (dfn[eg[i].go]<dfn[p]){//new
					stack[++pp]=(Edge){p,eg[i].go};//new
					low[p]=min(low[p],dfn[eg[i].go]);
				}
			}
			if (use[eg[i].go]==0){
				stack[++pp]=(Edge){p,eg[i].go};//new
				search(eg[i].go,p);
				low[p]=min(low[p],low[eg[i].go]);
				tot++;
				if ((!isCut[p])&&((p==root&&tot>1)||(p!=root&&low[eg[i].go]>=dfn[p]))) isCut[p]=1,cutTot++;
				if (low[eg[i].go]>=dfn[p]){//new Attention!!!
					bccTot++;
					while (pp){
						Edge a=stack[pp--];
						if (color[a.x]!=bccTot) {bcc[bccTot].push_back(a.x);color[a.x]=bccTot;}
						if (color[a.y]!=bccTot) {bcc[bccTot].push_back(a.y);color[a.y]=bccTot;}
						if (a.x==p&&a.y==eg[i].go) break;
					}
				}
			}
		}
	}
}
using namespace Tarjan;
void init(){
	for (int i=1;i<=bccTot;i++) bcc[i].clear();
	for (int i=1;i<N;i++){
		head[i]=0;
		use[i]=0;
		isCut[i]=0;
		color[i]=0;
		dfn[i]=0;
		low[i]=0;
	}
	p=1;po=1;pp=0;bccTot=0;
	
}
int m,a,b,ans1;
LL ans2;
int main(){
	freopen("Tarjan.in","r",stdin);
	freopen("Tarjan.out","w",stdout);
	int cas=0;
	while (scanf("%d",&m)!=EOF&&m){
		cas++;
		init();
		for (int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);
			build(a,b);
			build(b,a);
		}
		root=1;
		search(root,-1);
		int ans1=0;LL ans2=1LL;
		for (int i=1;i<=bccTot;i++){
			int tot=0;
			for (int j=0;j<bcc[i].size();j++) if (isCut[bcc[i][j]]) tot++;
			if (tot==1){
				ans1++;ans2*=(LL)(bcc[i].size()-tot);
			} 
		}
		if (bccTot==1){
			ans1=2;ans2=bcc[1].size()*(bcc[1].size()-1LL)/2LL;
		}
		printf("Case %d: %d %lld\n",cas,ans1,ans2);
	}
	return 0;	
}
