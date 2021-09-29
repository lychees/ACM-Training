#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int R(int x){return ((rand()<<15)+rand())%x+1;}
bool b[1005][1005]; int n,m,x[50005],y[50005],z[50005];
int main()
{
	freopen("J.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(_,1000){
		int n=R(100);
		printf("%d\n",n);
		rep(i,n-1) printf("%d %d %d\n",R(i),i+1,R(300));
	}
	puts("0");
	return 0;
}
