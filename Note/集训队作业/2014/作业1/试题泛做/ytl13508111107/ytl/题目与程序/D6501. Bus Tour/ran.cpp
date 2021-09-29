#include <iostream>
using namespace std;

int n=3,m=10,h=3600;
int main(){
	freopen("bus.in","w",stdout);
	printf("%d %d\n",n,m);
	for (int i=1;i<=m;i++) printf("%d %d %d\n",rand()%n,rand()%n,rand()%h+1);
	return 0;
}
