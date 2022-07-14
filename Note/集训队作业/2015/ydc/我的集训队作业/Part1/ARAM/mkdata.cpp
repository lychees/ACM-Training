#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<ctime>
using namespace std;
int randint(int l,int r)
{
	return rand()%(r-l+1)+l;
}
int main()
{
	srand(time(0));
	freopen("F19.in","w",stdout);
	int T=1;
	printf("%d\n",T);
	for(int i=1;i<=T;++i)
	{
		int n=1000,G=20,R=20;
		printf("%d %d %d\n",n,R,G);
		for(int i=1;i<=n;++i)
			printf("%.4f ",rand()%10001/10000.0);
		printf("\n");	
	}
	return 0;
}
