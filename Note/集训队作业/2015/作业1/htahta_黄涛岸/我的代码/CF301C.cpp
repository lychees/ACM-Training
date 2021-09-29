#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int main()
{
	for(int i=0;i<=9;i++)printf("??%d>>%d??\n",i,i);
	puts("??>>?");
	for(int i=0;i<9;i++)printf("%d?<>%d\n",i,i+1);
	puts("9?>>?0");
	puts("?<>1");
	puts(">>??");
	return 0;
}
