#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define DEBUG {printf("#\n");exit(0);}
#define N 15
#define T 40
using namespace std;

void print(int a[],int n){
	for (int i=1;i<=n;i++) printf("%d ",a[i]);printf("\n");
}	

const int change[4][4]={
{2,6,5,1},
{5,6,2,1},
{3,6,4,1},
{4,6,3,1}};
const int xo[]={-1,1,0,0};
const int yo[]={0,0,-1,1};

struct data{
	int x,y,t;
	data(int x=0,int y=0,int t=0):x(x),y(y),t(t){};
};

int n,m,sx,sy,t1,t2,flag;
int use[N][N][T],type[7][7],trans[T][5],map[N][N],up[T],canGo[T];
data f[N][N][T],Q[N*N*T];


void move(int tz[7],int k){
	int t=tz[change[k][0]];
	for (int i=0;i<3;i++) tz[change[k][i]]=tz[change[k][i+1]];
	tz[change[k][3]]=t;
}
int kind(int tz[7]){
	canGo[type[tz[1]][tz[2]]]=1;
	return type[tz[1]][tz[2]];
}

void changeTo(int tz[7]){
	int nt[7];
	for (int i=0;i<4;i++){
		memcpy(nt,tz,sizeof(nt));
		move(nt,i);
		trans[kind(tz)][i]=kind(nt);
	}
}
void getChange(int tz[7]){
	for (int i=1;i<=4;i++){
		move(tz,0);
		changeTo(tz);
	}
}
void deal(){
	int po=0;
	for (int i=1;i<=6;i++)
		for (int j=1;j<=6;j++){
			type[i][j]=++po;
			up[po]=i;
		}
	int tz[7]={0,1,2,3,4,5,6},nt[7];
	getChange(tz); 
	for (int i=1;i<=4;i++){
		move(tz,0);
		memcpy(nt,tz,sizeof(nt));
		move(nt,3);
		getChange(nt);
	}
	move(nt,3);
	getChange(nt);
}
int ttt=0;
void print(int x,int y,int t){
	if (x==sx&&y==sy){
		printf("(%d,%d),",x,y);
		ttt++;
		return;
	}
	data o=f[x][y][t];
	print(o.x,o.y,o.t);
	printf("(%d,%d),",x,y);
	ttt++;
	if (ttt==9){
		printf("\n");
		ttt=0;
	}
}
void bfs(){
	int st=type[t1][t2];
	Q[1]=data(sx,sy,st);
	for (int p1=1,p2=1;p1<=p2;p1++){
		int x=Q[p1].x,y=Q[p1].y,t=Q[p1].t;
		for (int i=0;i<4;i++){
			int nx=x+xo[i],ny=y+yo[i],nt=trans[t][i];
			if (!use[nx][ny][nt]&&(map[nx][ny]==-1||up[t]==map[nx][ny])){
				use[nx][ny][nt]=1;
				Q[++p2]=data(nx,ny,nt);
				f[nx][ny][nt]=data(x,y,t);
				if (nx==sx&&ny==sy){
					print(x,y,t);
					printf("(%d,%d)\n",nx,ny);
					flag=1;return;
				}
			}
		}
	}
}
void init(){
	ttt=0;flag=0;
	memset(use,0,sizeof(use));
}
char str[100];
int main(){
	freopen("dicey.in","r",stdin);
	freopen("dicey.out","w",stdout);
	deal();
	scanf("%d%d%d%d%d%d",&n,&m,&sx,&sy,&t1,&t2);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) 
			scanf("%d",&map[i][j]);
	scanf("\n");
	init();
	bfs();
	if (!flag) printf("No Solution Possible\n");
	return 0;
}
