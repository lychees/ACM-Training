#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 4005
using namespace std;
typedef long long LL;

const int xo[]={-1,0};
const int yo[]={0,-1};

struct data{
	int x1,x2,y;
	data(int x1=0,int x2=0,int y=0):x1(x1),x2(x2),y(y){};
	void read(){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		a++;b++;c++;d++;
		x1=a;y=b;x2=c;
	}
}wall[N];

int n,m,w;
int map[N][N],go[N][N],widex[N],widey[N];
LL reach,allcave;

namespace LSH{
	int order[N],totx=0,toty=0;double ordx[N],ordy[N];
	int look(int x,double order[],int tot){
		int l=1,r=tot,mid;
		while (l<r){
			mid=(l+r)>>1;
			if (x>order[mid]) l=mid+1;else r=mid;
		}
		return l;
	}
	void lsh(){
		totx=toty=0;
		order[0]=0;
		for (int i=1;i<=w;i++) order[++order[0]]=wall[i].y;
		sort(order+1,order+order[0]+1);
		order[0]=0;
		for (int i=1;i<=w;i++) if (i==1||order[i]!=order[order[0]]) order[++order[0]]=order[i];
		for (int i=1;i<=order[0];i++){
			if (i!=1&&order[i]!=order[i-1]+1){
				ordy[++toty]=double(order[i]+order[i-1])/2;
				widey[toty]=order[i]-order[i-1]-1;
			}
			ordy[++toty]=order[i];
			widey[toty]=1;
		} 
		for (int i=1;i<=w;i++) wall[i].y=look(wall[i].y,ordy,toty); 				
		order[0]=0;
		for (int i=1;i<=w;i++) order[++order[0]]=wall[i].x1,order[++order[0]]=wall[i].x2;
		sort(order+1,order+order[0]+1);
		int tot=order[0];order[0]=0;
		for (int i=1;i<=tot;i++) if (i==1||order[i]!=order[order[0]]) order[++order[0]]=order[i];
		for (int i=1;i<=order[0];i++){
			if (i!=1&&order[i]!=order[i-1]+1){
				ordx[++totx]=double(order[i]+order[i-1])/2;
				widex[totx]=order[i]-order[i-1]-1;
			}
			ordx[++totx]=order[i];
			widex[totx]=1;
		} 
		for (int i=1;i<=w;i++){
			wall[i].x1=look(wall[i].x1,ordx,totx);
			wall[i].x2=look(wall[i].x2,ordx,totx);
		}
	}
	
}
using namespace LSH;

void dfs(int x,int y){
	go[x][y]=1;
	if (x==n&&y==m){
		go[x][y]=2;
		reach+=LL(widex[x])*widey[y];
		return;
	}
	for (int i=0;i<2;i++){
		int nx=x+xo[i],ny=y+yo[i];
		if (!map[nx][ny]){
			if (!go[nx][ny]) dfs(nx,ny);
			if (go[nx][ny]==2) go[x][y]=2; 
		}
	}
	if (go[x][y]==2) reach+=LL(widex[x])*widey[y];
}

void init(){
	allcave=LL(n)*m;
	reach=0;
	for (int i=1;i<=totx;i++)
		for (int j=1;j<=toty;j++) 
			map[i][j]=go[i][j]=0;
}

void makeWall(){
	for (int i=1;i<=totx;i++)
		for (int j=1;j<=toty;j++)
			map[i][j]=1;
	for (int i=2;i<totx;i++)
		for (int j=2;j<toty;j++)
			map[i][j]=0;
	for (int i=1;i<=w;i++) 
		for (int j=wall[i].x1;j<=wall[i].x2;j++)
			map[j][wall[i].y]=1;
}

void dp(){
	if (map[n][m]==1) return;
	go[n][m]=1;reach+=LL(widex[n])*widey[m];
	for (int i=n;i>=1;i--)
		for (int j=m;j>=1;j--) if (!(i==n&&j==m)){
			if (!map[i][j]){
				go[i][j]=go[i+1][j]||go[i][j+1];
				if (go[i][j]) reach+=LL(widex[i])*widey[j];
			}
		}
}

struct point{
	int x,y;
	point(int x=0,int y=0):x(x),y(y){};
};
point Q[N*N];
void bfs(){
	if (map[n][m]==1) return;
	Q[1]=point(n,m);
	for (int p1=1,p2=1;p1<=p2;p1++){
		int x=Q[p1].x,y=Q[p1].y;
		reach+=LL(widex[x])*widey[y];
		for (int i=0;i<2;i++){
			int nx=x+xo[i],ny=y+yo[i];
			if (!map[nx][ny]){
				map[nx][ny]=2;
				Q[++p2]=point(nx,ny);
			}
		}
	}
}

void checkWall(){
	for (int i=1;i<=w;i++) if (wall[i].x1>wall[i].x2) while (1);
	for (int i=1;i<=w;i++)
		for (int j=i+1;j<=w;j++)
			if (wall[i].y==wall[j].y&&
				(!((wall[i].x1<wall[j].x1&&wall[i].x2<wall[j].x1)||(wall[j].x1<wall[i].x1&&wall[j].x2<wall[i].x1)))
			   )
				while (1);
}

int main(){
	freopen("biobots.in","r",stdin);
	freopen("biobots.out","w",stdout);
	int cas=0;
	while (scanf("%d%d%d",&m,&n,&w)!=EOF&&(m||n||w)){
		cas++;
		if (w==0){
			printf("Case %d: 0\n",cas);
			continue;
		}
		init();
		for (int i=1;i<=w;i++){
			wall[i].read();
			allcave-=wall[i].x2-wall[i].x1+1;
		}
		wall[w+1]=data(0,n+1,m+1);
		wall[w+2]=data(0,n+1,0);
		w+=2;
		lsh();
		n=totx-1;m=toty-1;
		makeWall();
		bfs();
		printf("Case %d: %I64d\n",cas,allcave-reach);
	}
	return 0;
}
