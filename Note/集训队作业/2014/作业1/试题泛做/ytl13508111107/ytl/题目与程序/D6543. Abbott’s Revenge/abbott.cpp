#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 15
using namespace std;

const int change[4][3]={
{2,3,0},
{3,2,1},
{1,0,2},
{0,1,3}};
const int xo[]={-1,1,0,0};
const int yo[]={0,0,-1,1};

struct data{
	int x,y,dir;
	data(int x=0,int y=0,int dir=0):x(x),y(y),dir(dir){};
};

char Dir;
int Sx,Sy,Tx,Ty,xx,yy,ttt,flag,tDir;
int can[N][N][4][4],use[N][N][4];
data Q[N*N*4],f[N][N][4];

int trans(char a){
	switch(a){
		case'N':return 0;break;
		case'S':return 1;break;
		case'W':return 2;break;
		case'E':return 3;break;
		case'L':return 0;break;
		case'R':return 1;break;
		case'F':return 2;break;
	}
	return -1;
}
void deal(int x,int y,char str[]){
	int n=strlen(str);
	for (int i=1;i<n;i++){
		can[x][y][trans(str[0])][trans(str[i])]=1;
	}
}
void print(int x,int y,int dir){
	if (x==xx&&y==yy&&dir==tDir){
		printf(" (%d,%d)",x,y);
		ttt++;
		return;
	}
	data o=f[x][y][dir];
	print(o.x,o.y,o.dir);
	if (ttt==1) printf(" ");
	printf(" (%d,%d)",x,y);
	ttt++;
	if (ttt==11){
		ttt=1;
		printf("\n");
	}
}
void bfs(){
	if (xx==Tx&&yy==Ty){
		printf("  (%d,%d) (%d,%d)\n",Sx,Sy,Tx,Ty);
		flag=1;
		return;
	}
	Q[1]=data(xx,yy,trans(Dir));
	use[xx][yy][trans(Dir)]=1;
	for (int p1=1,p2=1;p1<=p2;p1++){
		int x=Q[p1].x,y=Q[p1].y,dir=Q[p1].dir;
		for (int i=0;i<3;i++) if (can[x][y][dir][i]){
			int ndir=change[dir][i];
			int nx=x+xo[ndir],ny=y+yo[ndir];
			if (!use[nx][ny][ndir]){
				use[nx][ny][ndir]=1;
				Q[++p2]=data(nx,ny,ndir);
				f[nx][ny][ndir]=data(x,y,dir);
				if (nx==Tx&&ny==Ty){
					flag=1;
					printf("  (%d,%d)",Sx,Sy);
					ttt=2;
					print(x,y,dir);
					if (ttt==1) printf(" ");
					printf(" (%d,%d)\n",Tx,Ty);
					return;	
				}
			}
		}
	}
}
void init(){
	memset(use,0,sizeof(use));
	memset(can,0,sizeof(can));
	flag=0;
}
char name[100];
int main(){
	freopen("abbott.in","r",stdin);
	freopen("abbott.out","w",stdout);
	while (gets(name)&&strcmp(name,"END")!=0){
		init();
		int x,y;char str[10];char temp;
		scanf("%d%d%c%c%d%d",&Sx,&Sy,&temp,&Dir,&Tx,&Ty);
		tDir=trans(Dir);xx=Sx+xo[tDir],yy=Sy+yo[tDir];
		while (scanf("%d",&x)!=EOF&&x){
			scanf("%d",&y);
			while (scanf("%s",str)!=EOF&&strcmp(str,"*")!=0){
				deal(x,y,str);
			}
		}
		scanf("\n");
		printf("%s\n",name);
		bfs();
		if (!flag) printf("  No Solution Possible\n");
	}
	return 0;
}
