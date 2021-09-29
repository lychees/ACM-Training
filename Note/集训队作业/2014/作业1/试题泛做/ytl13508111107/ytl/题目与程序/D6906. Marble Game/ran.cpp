#include <iostream>
#define N 5
using namespace std;

const int xo[]={0,0,1,-1};
const int yo[]={1,-1,0,0};

int tt=10,n=4,m=4,w=4;
int can[N][N],map[N][N],hole[N][N];

bool o(int a){
	return a>=0&&a<n;
}
int main(){
	freopen("game.in","w",stdout);
	for (int i=1;i<=tt;i++){
		printf("%d %d %d\n",n,m,w);
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				map[i][j]=hole[i][j]=0;
		for (int i=1;i<=m;i++){
			int a,b;
			do{
				a=rand()%n;b=rand()%n;
			}while (map[a][b]);
			map[a][b]=i;
			printf("%d %d\n",a,b);
		}
		for (int i=1;i<=m;i++){
			int a,b;
			do{
				a=rand()%n;b=rand()%n;
			}while (hole[a][b]);
			hole[a][b]=i;
			printf("%d %d\n",a,b);
		}
		for (int i=1;i<=w;i++){
			int a,b,x,y,dir;
			do{
				a=rand()%n;b=rand()%n;dir=rand()%4;
				x=a+xo[dir];y=b+yo[dir];
			}while (!(o(a)&&o(b)&&o(x)&&o(y)));
			printf("%d %d %d %d\n",a,b,x,y);
		}
	}
	printf("0 0 0\n");
	return 0;
}
