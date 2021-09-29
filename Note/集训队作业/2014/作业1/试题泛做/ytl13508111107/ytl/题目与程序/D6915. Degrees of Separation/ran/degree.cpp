#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#define N 105
using namespace std;

const int inf=0x2f2f2f2f;

map<string,int> my;
int dis[N][N],n,m,po;
string str1,str2;
void init(){
	memset(dis,0x2f,sizeof(dis));
	my.clear();
	po=0;
}
void print(int dis[N][N]){
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (dis[i][j]!=inf) printf("%d %d %d\n",i,j,dis[i][j]);

} 
int main(){
	freopen("degree.in","r",stdin);
	freopen("degree.out","w",stdout);
	int cas=0;
	while (scanf("%d%d",&n,&m)!=EOF&&(n||m)){
		cas++;
		init();
		for (int i=1;i<=m;i++){
			cin>>str1>>str2;
			if (my.find(str1)==my.end()) my[str1]=++po;
			if (my.find(str2)==my.end()) my[str2]=++po;
			int a=my[str1],b=my[str2];
			dis[a][b]=1;
			dis[b][a]=1;
		}
		for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++) if (i!=k)
				for (int j=1;j<=n;j++) if (j!=k&&j!=i)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		int ans=0;
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				ans=max(ans,dis[i][j]);
		printf("Network %d: ",cas);
		if (ans==inf) printf("DISCONNECTED\n");else printf("%d\n",ans);
		printf("\n");
	}
	return 0;
}
