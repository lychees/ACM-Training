#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
char a[105][105];
int R(int x){return ((rand()<<15)+rand())%x+1;}
int main()
{
	freopen("F.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(i,50){
		int t=R(10),N=R(100),M=R(70); printf("%d\n",t);
//		rep(k,t){
//			int n=R(10),m=R(7); printf("%d %d\n",n,m);
//			rep(i,n){rep(j,m) printf("%c",R(20)<2?R(26)+64:'-'); puts("");}
//		}
		rep(i,N) rep(j,M) a[i][j]=R(10)<4?R(2)+64:'-';
		rep(k,t){
			int n=R(min(N,10)),m=R(min(M,10)),x=R(N+1-n),y=R(M+1-m); printf("%d %d\n",n,m);
			for (int i=x;i<x+n;++i){for (int j=y;j<y+m;++j) printf("%c",a[i][j]); puts("");}
		}
	}
	puts("0");
	return 0;
}
