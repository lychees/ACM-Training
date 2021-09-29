#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int R(){return ((rand()<<15)+rand())%10000000+1;}
int main()
{
	freopen("J.in","w",stdout); srand(time(0));
	int T=100;
	while (T--){
		int n=rand()%100+1; printf("%d\n",n);
		rep(i,n) printf("%d %d %d\n",R(),R(),R());
		}
	puts("0");
	return 0;
}
