#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=1005;
int c[N],a[N][N]; string s[N],t[N];
int R(int x){return ((rand()<<15)+rand())%x+1;}
int main()
{
	freopen("G.in","w",stdout); srand(time(0));
	int n=R(5)+3,m=R(20),L,T=R(10),x,y;
	rep(i,n){L=R(15); rep(j,L) s[i]+=char(R(26)+96);}
	rep(i,m){L=R(15); rep(j,L) t[i]+=char(R(26)+96);}
	rep(i,n){
		c[i]=R(min(5,m)); printf("MTA %s %d",s[i].c_str(),c[i]);
		rep(j,c[i]) printf(" %s",t[a[i][j]=R(m)].c_str()); puts("");
	}
	puts("*");
	while (T--){
		x=R(n),y=R(c[n]),L=R(5);
		printf("%s@%s",t[a[x][y]].c_str(),s[x].c_str());
		rep(j,L) x=R(n),y=R(m),printf(" %s@%s",t[y].c_str(),s[x].c_str()); puts(""),puts("*");
		L=R(200);
		rep(j,L){
			printf("%c",R(90)+32);
			if (j%78==0 || j==L) puts("");
		}
		puts("*");
	}
	puts("*");
	return 0;
}
