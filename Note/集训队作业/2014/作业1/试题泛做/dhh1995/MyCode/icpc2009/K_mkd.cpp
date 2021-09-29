#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int R(int x){return ((rand()<<15)+rand())%x+1;}
bool b[1005][1005]; int n,m,x[50005],y[50005],z[50005];
int main()
{
	freopen("K.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(_,10){
		int n=R(20),m=R(5),T=4;
		rep(i,m) printf("%c",R(T)+64); putchar(' ');
		rep(i,m) printf("%c",R(T)+64); putchar(' ');
		printf("%d\n",n);
		rep(i,n){
			int L=R(m);
			rep(j,L) printf("%c",R(T)+64); putchar(' ');
			rep(j,L) printf("%c",R(T)+64); puts("");
			
		}
	}
	puts(".");
	return 0;
}
