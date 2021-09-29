#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <algorithm>
#define N 20
using namespace std;

int map[N][N],use[N],n,ans,rec[N],vis[N]; 

namespace Graph{
	int head[N],gt=1;
	struct Rec{int go,nex;}eg[N*N];
	void build(int a,int b){
		eg[++gt]=(Rec){b,head[a]};
		head[a]=gt;
	}	
}
using namespace Graph;

bool dfs(int p,int tfa){
	vis[p]=1;
	int tot=0;
	for (int i=head[p];i;i=eg[i].nex) if (eg[i].go!=tfa&&!use[eg[i].go]){
		if (vis[eg[i].go]) return false;
		if (!dfs(eg[i].go,p)) return false;
		tot++;
	}
	return (tot<=1)||(tfa==-1&&tot==2);
}
void check(int open){
	int set=0;
	for (int i=1;i<=n;i++) vis[i]=0;
	for (int i=1;i<=n;i++) if (!use[i]&&!vis[i]){
		if (!dfs(i,-1)) return;
		set++;
	}
	if (set-1<=open&&ans>open) memcpy(rec,use,sizeof(use));
	if (set-1<=open) ans=min(ans,open);
}
void search(int k,int open){
	if (open>=ans) return;
	if (k==n+1){
		check(open);
		return;
	}
	use[k]=0;
	search(k+1,open);
	use[k]=1;
	search(k+1,open+1);
}
void init(){
	memset(head,0,sizeof(head));
	gt=1;
	ans=0x7fffffff;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) map[i][j]=0; 
}
int main(){
	freopen("cutting.in","r",stdin);
	freopen("cutting.out","w",stdout);
	int cas=0;
	while (scanf("%d",&n)!=EOF&&n){
		cas++;
		init();
		int a,b;
		while (scanf("%d%d",&a,&b)!=EOF&&(a!=-1||b!=-1)){
			if (map[a][b]) continue;
			map[a][b]=map[b][a]=1;
			build(a,b);
			build(b,a);
		}
		search(1,0);
		printf("Set %d: Minimum links to open is %d\n",cas,ans);
	}
	return 0;
}
