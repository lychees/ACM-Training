//By ytl 2013-10-26
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 505
using namespace std;
//typedef (short int) int;

const int INF=0x7fffffff/3;

int n;
int f[N],can[N][N],use[N],st[N][N],v[N],w[N][N];
short int g[N][N][N];
void DP(){
	f[0]=0;
	for (int i=1;i<=n;i++) f[i]=INF;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=i;j++)
			if (can[j][i])
				f[i]=min(f[i],f[j-1]+w[j][i]);
}
int join(int a,int b,int c,int d){
	int x=max(st[a][b],st[c][d]);
	return int(g[a][b][x]+g[c][d][x]);
}
void getg(){
	for (int x=1;x<=n;x++)
		for (int i=1;i<=n;i++)
			for (int j=i;j<=n;j++)
				g[i][j][x]=g[i][j-1][x]+(short int)(v[j]>=x);
}
void getst(){
	for (int i=1;i<=n;i++){
		st[i][i]=v[i];
		for (int j=i+1;j<=n;j++) 
			st[i][j]=min(st[i][j-1],v[j]);
	}
}
void getcan(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) use[j]=0;
		int now=0;
		for (int j=i;j<=n;j++){
			if (use[v[j]]) break;
			use[v[j]]=1;
			while (use[now+1]) now++;
			if (now==j-i+1) can[i][j]=1;
 		}
	}
}
void getw(){
	for (int i=1;i<=n;i++) w[i][i]=0;
	for (int len=2;len<=n;len++)
		for (int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			w[i][j]=INF;
			for (int k=i;k<j;k++)
				w[i][j]=min(w[i][j],w[i][k]+w[k+1][j]+join(i,k,k+1,j));
		}
}
void preDeal(){
	getcan();
	getst();
	getg();
	getw();
}	
int main(){
	freopen("doll.in","r",stdin);
	freopen("doll.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&v[i]);
		if (v[i]>n){
			printf("Impossible\n");
			return 0;
		}
	}
	preDeal();
	DP();
	if (f[n]==INF) 	printf("Impossible\n");
	else printf("%d\n",f[n]);
	return 0;
}
