#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int a[45];
int R(int x){return ((rand()<<15)+rand())%x+1;}
int main()
{
	freopen("D.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(i,5){
		int n=R(10);
		rep(i,n) printf("%c",a[i]=(R(26)+65));
		printf("%c\n",a[R(n)]);
	}
	puts("X");
	return 0;
}
