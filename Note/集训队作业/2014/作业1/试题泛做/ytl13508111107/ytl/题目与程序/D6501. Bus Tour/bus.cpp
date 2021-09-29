//By ytl 2013-11-20
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define S ((1<<20)+5)
#define N 21
using namespace std;

const int INF=0x7fffffff/3;

int ans,limit,D,n,m,h;
int type[S],lt[S][N],rt[S][N],dis[N][N];

void getAns(int tot,int now,int s){
	if (tot==limit){
		ans=min(ans,type[s]+type[D-s]);
		return;
	}
	for (int i=now;i<=n-1-limit+tot;i++) getAns(tot+1,i+1,s|(1<<i));
}

void search(int tot,int now,int s){
	if (tot==limit){
		type[s]=INF;
		for (int i=1;i<=n-2;i++) if ((s>>i)&1){
			type[s]=min(type[s],lt[s][i]+rt[D-s+(1<<i)][i]);
		}
		return;
	}
	for (int i=now;i<=n-1-limit+tot;i++) search(tot+1,i+1,s|(1<<i));
}
void searchl(int tot,int now,int s){
	if (tot==limit){
		for (int p=1;p<=n-2;p++) if ((s>>p)&1)
			for (int i=1;i<=n-2;i++) if (!((s>>i)&1)){
				lt[s|(1<<i)][i]=min(lt[s|(1<<i)][i],lt[s][p]+dis[p][i]);
			}
		return;
	}
	for (int i=now;i<=n-1-limit+tot;i++){
		searchl(tot+1,i+1,s|(1<<i));
	}
}
void searchr(int tot,int now,int s){
	if (tot==limit){
		for (int p=1;p<=n-2;p++) if ((s>>p)&1)
			for (int i=1;i<=n-2;i++) if (!((s>>i)&1)){
				rt[s|(1<<i)][i]=min(rt[s|(1<<i)][i],rt[s][p]+dis[p][i]);
			}
		return;
	}
	for (int i=now;i>=limit-tot;i--){
		searchr(tot+1,i-1,s|(1<<i));
	}
}
void Floyd(){
	for (int k=0;k<n;k++)
		for (int i=0;i<n;i++) if (i!=k)
			for (int j=0;j<n;j++) if (j!=i&&j!=k)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
int main(){
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);
	scanf("%d%d",&n,&m);
	h=n-2;
	D=(1<<n)-1-1-(1<<(n-1));
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) if (i!=j)
			dis[i][j]=INF;
	for (int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		dis[a][b]=dis[b][a]=min(dis[a][b],c);
	}
	Floyd();
	if (n==3){
		printf("%d\n",2*(dis[0][1]+dis[1][2]));
		return 0;
	}
	memset(lt,0x2f,sizeof(lt));
	memset(rt,0x2f,sizeof(rt));
	for (int i=1;i<=(n-2);i++){
		lt[1<<(i)][i]=dis[0][i];
		rt[1<<(i)][i]=dis[n-1][i];
	}
	for (int i=1;i<max(h/2,h-h/2);i++){
		limit=i;
		searchl(0,1,0);
	}
	for (int i=1;i<=max(h/2,h-h/2);i++){
		limit=i;
		searchr(0,n-2,0);
	}
	limit=h/2;
	search(0,1,0);
	limit=h-h/2;
	search(0,1,0);
	ans=INF;
	getAns(0,1,0);
	printf("%d\n",ans);
	return 0;
}
