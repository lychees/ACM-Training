#include <iostream>
using namespace std;

int main(){
	srand(time(NULL));
	freopen("hey.in","w",stdout);
	printf("%d.%d%d %d.%d%d\n",rand()%100,rand()%10,rand()%10,rand()%50,rand()%10,rand()%10);
	return 0;
}
