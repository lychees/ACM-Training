#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int R(int x){return ((rand()<<15)+rand())%x+1;}
int a[35];
int main()
{
	freopen("G.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(_,10){
		int n=R(9)+4;
		
		printf("%s\n%d\n",R(2)&1?"Axel":"Birgit",n);
		rep(i,n*2) a[i]=i;
		random_shuffle(a,a+n*2);
		rep(i,n*2) printf("%d%c ",a[i]%n+1,a[i]<n?'R':'B'); puts("");
	}
	puts("End");
	return 0;
}
