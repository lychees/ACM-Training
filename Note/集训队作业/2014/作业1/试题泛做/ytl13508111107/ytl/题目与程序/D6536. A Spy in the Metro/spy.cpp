//By ytl 2013-11-15
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 55
#define M 55
#define T 250
using namespace std;

const int INF=0x7fffffff/3;

int n,K,m1,m2;
int f[T][N],start1[N][M],start2[N][M],now1[N],now2[N],tot1[N],tot2[N],tt[N],d[M],e[M];
void inPut(){
	scanf("%d",&K);
	for (int i=1;i<=n-1;i++) scanf("%d",&tt[i]);
	scanf("%d",&m1);
	for (int i=1;i<=m1;i++) scanf("%d",&d[i]);
	scanf("%d",&m2);
	for (int i=1;i<=m2;i++) scanf("%d",&e[i]);
}
void preDeal(){
	for (int i=1;i<=m1;i++){
		int t=d[i];
		start1[1][++tot1[1]]=t;
		for (int j=1;j<=n-1;j++){
			t+=tt[j];
			if (t<=K) start1[j+1][++tot1[j+1]]=t;
		}
	}
	for (int i=1;i<=m2;i++){
		int t=e[i];
		start2[n][++tot2[n]]=t;
		for (int j=n-1;j>=1;j--){
			t+=tt[j];
			if (t<=K) start2[j][++tot2[j]]=t;
		}
	}
	/*for (int i=1;i<=n;i++){
		for (int j=1;j<=tot1[i];j++) printf("%d ",start1[i][j]);
		printf("\n");
	}*/
}
inline void updata(int &a,int b){
	if (b<a) a=b;
}
void DP(){
	for (int i=0;i<=K;i++)
		for (int j=1;j<=n;j++)
			f[i][j]=INF;
	for (int i=0;i<=K;i++) f[i][1]=i;
	//printf("%d\n",f[20][1]);
	for (int i=1;i<=n;i++) now1[i]=now2[i]=1;
	for (int i=0;i<=K;i++){
		for (int j=1;j<=n;j++){
			while (start1[j][now1[j]]<i&&now1[j]<=tot1[j]) now1[j]++;
			while (start2[j][now2[j]]<i&&now2[j]<=tot2[j]) now2[j]++;	
		}
		for (int j=1;j<=n;j++) if (f[i][j]!=INF){
			if (j<n){
				for (int k=now1[j];k<=tot1[j];k++){
					int reach=start1[j][k]+tt[j];
					//if (reach==25) printf("!%d %d %d %d :%d\n",i,j,reach,j+1,reach-i);
					if (reach<=K) updata(f[reach][j+1],f[i][j]+start1[j][k]-i);
				}
			}
			if (j>1){
				for (int k=now2[j];k<=tot2[j];k++){
					int reach=start2[j][k]+tt[j-1];
					if (reach<=K) updata(f[reach][j-1],f[i][j]+start2[j][k]-i);		
				}
			}
		} 
	}	
}
void init(){
	for (int i=1;i<=n;i++) tot1[i]=tot2[i]=0;
}
int main(){
	freopen("spy.in","r",stdin);
	freopen("spy.out","w",stdout);
	int cas=0;
	while (scanf("%d",&n)!=EOF&&n){
		inPut();
		init();
		preDeal();
		DP();
		int ans=INF;
		for (int i=K;i>=0;i--) ans=min(ans,f[i][n]+K-i);
		if (ans==INF) printf("Case Number %d: impossible\n",++cas);
		else printf("Case Number %d: %d\n",++cas,ans);
	}
	return 0;
}
