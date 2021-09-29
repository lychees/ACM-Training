#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int R(int n){return rand()%n;}
int x[25],y[25],r[25];
bool check(int n)
{
	rep(i,n)
		if ((x[i]-x[n])*(x[i]-x[n])+(y[i]-y[n])*(y[i]-y[n])<=(r[i]+r[n])*(r[i]+r[n])) return 0;
	return 1;
}
int main()
{
	freopen("C.in","w",stdout); srand(time(0));
	int T=10000;
	while (T--){
		int n=8;
		printf("%d\n",n);
		rep(i,n){
			x[i]=R(100),y[i]=R(100),r[i]=R(10)+1;
			while (!check(i)) x[i]=R(100),y[i]=R(100),r[i]=R(100)+1;
			printf("%d %d %d C",x[i],y[i],r[i]);
			if (R(2)) printf("C"); puts("");
		}
		int x=R(n),y=R(n); while (x==y) x=R(n),y=R(n);
		printf("%d %d %lf\n",x,y,R(50)+R(10000)/10000.);
	}
	puts("0");
	return 0;
}
