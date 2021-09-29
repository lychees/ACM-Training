#include <iostream>
using namespace std;

string str1[]={"A","B","AB","O"};
string str2[]={"+","-"};
void output(){
	int a=rand()%4;
	int b=rand()%2;
	cout<<str1[a]<<str2[b]<<" ";
}
int main(){
	srand(time(NULL));
	freopen("calculate.in","w",stdout);
	for (int i=1;i<=10;i++){
		int t=rand()%3;
		if (t==0) printf("? ");else output();
		if (t==1) printf("? ");else output();
		if (t==2) printf("? ");else output();
		printf("\n");
	} 
	printf("E N D\n");
	return 0;
}
