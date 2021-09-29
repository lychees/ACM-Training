#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int R(int x){return ((rand()<<15)+rand())%x+1;}
int main()
{
	srand(time(0)); freopen("G.in","w",stdout);
	rep(_,10){
		int n=1<<R(7)-1; printf("%d\n",n);
		rep(i,n){rep(j,n) printf("%d",R(2)>1); puts("");}
	}
	puts("0");
	return 0;
}
