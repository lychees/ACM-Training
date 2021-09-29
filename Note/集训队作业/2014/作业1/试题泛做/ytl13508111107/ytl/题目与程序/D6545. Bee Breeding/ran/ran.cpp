#include <iostream>
using namespace std;

int main(){
	freopen("bee.in","w",stdout);
	for (int i=1;i<=70;i++)
		for (int j=1;j<=70;j++)
			printf("%d %d\n",i,j);
	printf("0 0\n");
	return 0;
}
