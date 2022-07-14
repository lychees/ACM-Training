#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
void print()
{
	if(n==0)
	{
		printf("1\n");
		printf("0 0 -> R\n");
		return ;
	}
	int s=17;
	for(int i=n;i;i>>=1)
		++s;
	printf("%d\n",s);
	int now=0;
	for(int i=1;n;++i)
	{
		printf("%d 0 -> E %d %d\n",now,i,100+n%2);
		now=i,n>>=1;
	}
	printf("%d 0 -> W 200 0\n",now);
	printf("200 100 -> W 200 100\n");
	printf("200 101 -> W 200 101\n");
	printf("200 0 -> E 201 0\n");
	printf("201 100 -> E 202 0\n");
	printf("201 101 -> E 203 0\n");
	printf("202 100 -> E 202 101\n");
	printf("202 101 -> E 203 101\n");
	printf("203 100 -> E 203 100\n");
	printf("203 101 -> E 204 100\n");
	printf("204 100 -> E 203 101\n");
	printf("204 101 -> E 204 101\n");
	printf("203 0 -> W 205 0\n");
	printf("205 0 -> E 207 0\n");
	printf("207 0 -> R\n");
	printf("205 101 -> W 200 101\n");
	printf("204 0 -> W 200 101\n");
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
