#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int R(int x){return ((rand()<<15)+rand())%x+1;}
bool b[1005][1005]; int n,m,x[50005],y[50005],z[50005];
int main()
{
	freopen("E.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(_,10){
		int n=R(50)+1,m=0;
		rep(i,n) rep(j,n) b[i][j]=i==j;
		rep(i,n-1){
			int s=R((n-i)/5+1),j;
			rep(k,s) j=i+R(n-i),b[i][j]=1,x[m+k]=i,y[m+k]=j,z[m+k]=R(10);
			m+=s;
		}
		rep(i,n){
			rep(j,i-1) if (b[i][j]) b[1][i]=1;
			if (!b[1][i]) b[1][i]=1,x[++m]=1,y[m]=i,z[m]=R(10);
		}
		for (int i=n;i;--i){
			if (!b[i][n]) b[i][n]=1,x[++m]=i,y[m]=n,z[m]=R(10);
			rep(j,i-1) if (b[j][i]) b[j][n]=1;
		}
		printf("%d %d\n",n,m);
		rep(i,m) printf("%d %d %d\n",x[i],y[i],z[i]);
	}
	puts("0 0");
	return 0;
}
