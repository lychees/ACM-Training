#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int s[405],h[15];
int R(int x){return ((rand()<<15)+rand())%x+1;}
bool Run(int y){return y%4==0 && (y%100!=0 || y%400==0);}
void prt(int t,bool flag)
{
	int y=t/365,m,d; if (s[y]>=t) --y; t-=s[y];
	m=t/30+1; if (h[m]+(m>2&&Run(y))>=t) --m; d=t-h[m]-(m>2&&Run(y));
	printf("%d%02d%02d%s",y+1700,m,d,flag?" ":"\n");
}
int main()
{
	rep(i,401) s[i+1]=s[i]+365+Run(i+1700);
	rep(i,13) if (i) h[i+1]=h[i]+(i==2?28:i==4||i==6||i==9||i==11?30:31);
	freopen("E.in","w",stdout);
	srand(time(0)); //Sleep(1000);
	rep(_,1){
		int n=R(10),m=R(10);
		printf("%d %d\n",n,m);
		rep(i,n+m){
			int x=R(146461),y=R(146461); if (x>y) swap(x,y);
			prt(x,1); prt(y,0);
		}
	}
	puts("0 0");
	return 0;
}
