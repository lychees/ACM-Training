#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int R(int x){return ((rand()<<15)+rand())%x+1;}
bool b[1005][1005]; int n,m,x[50005],y[50005],z[50005];
int main()
{
	freopen("F.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(_,10){
		int n=R(5),m=R(3);
		printf("%d %d\n",n,m);
		rep(i,n) printf("%d %d\n",R(21),R(21));
	}
	puts("0 0");
	return 0;
}
