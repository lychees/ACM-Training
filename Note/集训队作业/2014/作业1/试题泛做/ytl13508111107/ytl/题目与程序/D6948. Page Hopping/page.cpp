#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define N 105
using namespace std;

const int inf=0x2f2f2f2f;

int dis[N][N],du[N];
void init(){
	memset(dis,0x2f,sizeof(dis));
	memset(du,0,sizeof(du));
}
#define n 100
int main(){
	freopen("page.in","r",stdin);
	freopen("page.out","w",stdout);
	int cas=0;
	int a,b;
	while (scanf("%d%d",&a,&b)!=EOF&&(a||b)){
		cas++;
		init();
		dis[a][b]=1;
		du[a]++,du[b]++;	
		while (scanf("%d%d",&a,&b)!=EOF&&(a||b)){
			dis[a][b]=1;
			du[a]++,du[b]++;	
		}
		for (int k=1;k<=n;k++) if (du[k])
			for (int i=1;i<=n;i++) if (du[i]&&i!=k)
				for (int j=1;j<=n;j++) if (du[j]&&j!=i&&j!=k)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		int tot=0;
		for (int i=1;i<=n;i++) if (du[i]) tot++;
		double ans=0;
		for (int i=1;i<=n;i++) if (du[i])
			for (int j=1;j<=n;j++) if (du[j]&&i!=j){
				if (dis[i][j]==inf) {printf("ERROR: %d %d!\n",i,j);exit(0);}
				ans+=dis[i][j];
			}
		printf("Case %d: average length between pages = %.3lf clicks\n",cas,ans/tot/(tot-1));
	}
	return 0;
}
