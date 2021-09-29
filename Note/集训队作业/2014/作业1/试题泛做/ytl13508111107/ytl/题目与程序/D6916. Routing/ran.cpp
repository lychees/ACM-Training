#include <iostream>
using namespace std;

int n=100,m=1000;
int main(){
	freopen("routing.in","w",stdout);
	for (int i=1;i<=5;i++){
		printf("%d %d\n",n,m);
		for (int i=1;i<=m;i++) printf("%d %d\n",rand()%n+1,rand()%n+1);
	}
	printf("0 0\n");
	return 0;
}
