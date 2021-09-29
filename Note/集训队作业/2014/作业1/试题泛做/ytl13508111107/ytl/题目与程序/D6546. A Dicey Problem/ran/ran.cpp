#include <iostream>
using namespace std;

int canGo[7][7]={
{0,0,0,0,0,0,0},
{0,0,1,1,1,1,0},
{0,1,0,1,1,0,1},
{0,1,1,0,0,1,1},
{0,1,1,0,0,1,1},
{0,1,0,1,1,0,1},
{0,0,1,1,1,1,0}
};
int rand(int x){
	return rand()*rand()%x;
}
int main(){
	freopen("dicey.in","w",stdout);
	int n=10,m=10,T=100;
	for (int cas=1;cas<=T;cas++){
		printf("DICEMAZE%d\n",cas);
		printf("%d %d %d %d ",n,m,rand(n)+1,rand(m)+1);
		int a,b;
		while (1){
			a=rand(6)+1,b=rand(6)+1;
			if (canGo[a][b]) break;
		}
		printf("%d %d\n",a,b);
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++) printf("%d ",rand(8)-1);
			printf("\n");
		}
	}
	printf("END\n");
	return 0;
}
