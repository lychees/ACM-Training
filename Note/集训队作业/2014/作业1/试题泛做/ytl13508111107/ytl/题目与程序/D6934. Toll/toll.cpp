#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 60
using namespace std;

const int INF=0x7fffffff/3;

char trans(int x){
	if (x<=26) return 'a'+x-1;
	else return 'A'+x-27;
}

int n,K;char S,T;
int go[100005],edge[N][N],Q[N*N],dis[N],use[N];
void spfa(int S){
	Q[1]=S;
	for (int i=1;i<=52;i++) dis[i]=INF;
	dis[S]=K;
	for (int p1=1,p2=1;p1<=p2;p1++){
		int u=Q[p1];
		use[u]=0;
		for (int v=1;v<=52;v++) if (edge[u][v]){
			int x;
			if (u<=26) x=dis[u]+1;
			else  x=go[dis[u]];
			//printf("!%c %c %d\n",trans(u),trans(v),x);exit(0);
			if (x<dis[v]){
				dis[v]=x;
				if (!use[v]){
					use[v]=1;
					Q[++p2]=v;
				}
			}
		}
	}
}
void preDeal(){
	for (int i=100000;i>=1;i--) go[i-(i+19)/20]=i; 
}
void init(){
	memset(edge,0,sizeof(edge));
}
int trans(char a){
	if (a<='z'&&a>='a') return a-'a'+1;
	else return a-'A'+1+26;
}
int main(){
	freopen("toll.in","r",stdin);
	freopen("toll.out","w",stdout);
	int cas=0;
	preDeal();
	while (scanf("%d\n",&n)!=EOF&&(n!=-1)){
		init();x
		for (int i=1;i<=n;i++){
			char x,y;int a,b;
			scanf("%c %c\n",&x,&y);
			a=trans(x);b=trans(y);
			edge[a][b]=1;
			edge[b][a]=1;
		}
		char x,y;
		scanf("%d %c %c\n",&K,&x,&y);
		S=trans(x);T=trans(y);
		spfa(T);
		printf("Case %d: %d\n",++cas,dis[int(S)]);
	}
	return 0;
}
