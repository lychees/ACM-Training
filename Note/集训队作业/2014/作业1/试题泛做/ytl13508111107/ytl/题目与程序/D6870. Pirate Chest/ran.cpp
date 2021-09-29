#include <iostream>
using namespace std;

int randM(){
	return rand()|(rand()<<15)|((rand()&1)<<30);
}
int rand(int x){
	return randM()%x;
}
int n=200,m=200,h=1000000000;
int main(){
	srand(time(NULL));
	freopen("pirate.in","w",stdout);
	printf("%d %d %d %d\n",rand(n)+1,rand(m)+1,n,m);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) printf("%d ",rand(h));
		printf("\n");
	}
}
