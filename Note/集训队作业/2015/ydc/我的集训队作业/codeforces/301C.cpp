#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	for(int i=0;i<=9;i++)
		printf("??%d>>%d??\n",i,i);
	printf("??>>?\n");
	for(int i=0;i<9;i++)
		printf("%d?<>%d\n",i,(i+1)%10);
	printf("9?>>?0\n");
	printf("?<>1\n");
	printf(">>??\n");
	return 0;
}
