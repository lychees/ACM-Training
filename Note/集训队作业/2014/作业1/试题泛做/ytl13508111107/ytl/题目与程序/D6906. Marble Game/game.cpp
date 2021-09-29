//By ytl 2013-11-22
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#define N 5
#define SS 1000000
using namespace std;
typedef long long LL;

set<LL> vis;
int n,m,w,FLAG;
int map[N][N],nmap[N][N],hole[N][N],cant[N][N][N][N],hx[N],hy[N],num[N][N],numx[N*N],numy[N*N];
LL jc[10],S,T;

void print(int map[N][N]){
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++) printf("%d ",map[i][j]);
		printf("\n");
	}
	printf("\n");
}


struct data{
	LL s;int step;
	data(LL s=0,int step=0):s(s),step(step){};
}Q[SS];

void copy(int a[N][N],int b[N][N]){
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			b[i][j]=a[i][j];
}
void code(int map[N][N],LL &s){
	s=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) if (map[i][j])
			s+=(num[i][j]*jc[map[i][j]-1]);		
}
void uncode(LL s,int map[N][N]){
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) 
			map[i][j]=0;
	for (int i=1;i<=m;i++){
		LL a=s%17;
		if (a){
			map[numx[a]][numy[a]]=i;
			map[hx[i]][hy[i]]=i+m;
		}
		s/=17;
	}
}
bool go(int map[N][N],int k,LL &ns){
	if (k==0){
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++) if (map[i][j]>0&&map[i][j]<=m){
				int x=i,y=j;
				while (x>0&&map[x][y]<=m&&!cant[x][y][x-1][y]&&!(map[x-1][y]>0&&map[x-1][y]<=m)) x--;
				if (map[x][y]>m){
					if (map[i][j]+m==map[x][y]){
						map[i][j]=map[x][y]=0;
					}else return false;
				}else swap(map[i][j],map[x][y]);
			}
	}
	if (k==1){
		for (int i=n-1;i>=0;i--) 
			for (int j=0;j<n;j++) if (map[i][j]>0&&map[i][j]<=m){
				int x=i,y=j;
				while (x<n-1&&map[x][y]<=m&&!cant[x][y][x+1][y]&&!(map[x+1][y]>0&&map[x+1][y]<=m)) x++;
				if (map[x][y]>m){
					if (map[i][j]+m==map[x][y]){
						map[i][j]=map[x][y]=0;
					}else return false;
				}else swap(map[i][j],map[x][y]);
			}
	}	
	if (k==2){
		for (int j=0;j<n;j++)
			for (int i=0;i<n;i++) if (map[i][j]>0&&map[i][j]<=m){
				int x=i,y=j;
				while (y>0&&map[x][y]<=m&&!cant[x][y][x][y-1]&&!(map[x][y-1]>0&&map[x][y-1]<=m)) y--;
				if (map[x][y]>m){
					if (map[i][j]+m==map[x][y]){
						map[i][j]=map[x][y]=0;
					}else return false;
				}else swap(map[i][j],map[x][y]);
			}
	}
	if (k==3){
		for (int j=n-1;j>=0;j--)
			for (int i=0;i<n;i++) if (map[i][j]>0&&map[i][j]<=m){
				int x=i,y=j;
				while (y<n-1&&map[x][y]<=m&&!cant[x][y][x][y+1]&&!(map[x][y+1]>0&&map[x][y+1]<=m)) y++;
				if (map[x][y]>m){
					if (map[i][j]+m==map[x][y]){
						map[i][j]=map[x][y]=0;
					}else return false;
				}else swap(map[i][j],map[x][y]);
			}
	}
	code(map,ns);
	return true;
}
int bfs(){
	code(map,S);
	T=0;
	vis.insert(S);
	Q[1]=data(S,0);
	for (int p1=1,p2=1;p1<=p2;p1++){
		LL s=Q[p1].s,ns;
		uncode(s,map);
		for (int i=0;i<4;i++){
			copy(map,nmap);
			if (go(nmap,i,ns)){
				if (vis.find(ns)==vis.end()){					
					vis.insert(ns);
					Q[++p2]=data(ns,Q[p1].step+1);
					if (ns==T) return Q[p2].step;
				}
			}
		}
	}
	return -1;
}
void init(){
	FLAG=-1;
	memset(map,0,sizeof(map));
	memset(hole,0,sizeof(hole));
	memset(cant,0,sizeof(cant));
	vis.clear();
}
void Input(){
	for (int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if (map[a][b]) FLAG=0;
		map[a][b]=i;
	}
	for (int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if (hole[a][b]) FLAG=0;
		hole[a][b]=i;
	}
	for (int i=0;i<w;i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		cant[a][b][c][d]=cant[c][d][a][b]=1;
	}
}
void preDeal(){
	jc[0]=1;
	for (int i=1;i<=9;i++) jc[i]=jc[i-1]*17;
	int po=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			num[i][j]=++po;
			numx[po]=i;
			numy[po]=j;
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (map[i][j]&&hole[i][j]){
				if (map[i][j]!=hole[i][j]){
					FLAG=0;
					return;
				}else{
					int x=map[i][j];
					map[i][j]=hole[i][j]=0;
					for (int a=0;a<n;a++)
						for (int b=0;b<n;b++){
							if (hole[a][b]>x) hole[a][b]--;
							if (map[a][b]>x) map[a][b]--;
						}
					m--;
				}
			}
	if (!m) {FLAG=1;return;}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) if (hole[i][j]){
			hx[hole[i][j]]=i;
			hy[hole[i][j]]=j;
			map[i][j]=hole[i][j]+m;
		}
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int cas=0;
	while (scanf("%d%d%d",&n,&m,&w)!=EOF&&(n||m||w)){
		init();
		Input();
		preDeal();
		if (FLAG==0){
			printf("Case %d: impossible\n\n",++cas);	
			continue;
		}
		if (FLAG==1){
			printf("Case %d: %d moves\n\n",++cas,0);//moves???
			continue;
		}
		int ans=bfs();	 
		if (ans!=-1) printf("Case %d: %d moves\n\n",++cas,ans);
		else printf("Case %d: impossible\n\n",++cas);	
	}
	return 0;
}
