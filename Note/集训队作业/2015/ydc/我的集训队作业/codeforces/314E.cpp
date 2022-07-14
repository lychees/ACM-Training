#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 100010
using namespace std;
typedef unsigned uint;
uint dp[maxn];
void read()
{
	int n;
	scanf("%d",&n);
	if(n&1)
	{
		printf("0\n");
		return ;
	}
	uint *f=dp+5;
	f[0]=1;
	getchar();
	for(int i=1;i<=n;++i)
		if(getchar()=='?')
			for(int j=i&1;j<=i;j+=2)
				f[j]=f[j-1]*25+f[j+1];
		else
			for(int j=i&1;j<=i;j+=2)
				f[j]=f[j-1];
	printf("%u\n",f[0]);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%f\n",(double)clock()/CLOCKS_PER_SEC);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
