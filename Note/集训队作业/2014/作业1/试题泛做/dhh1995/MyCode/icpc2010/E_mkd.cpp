#include<iostream>
#include<windows.h>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int u[]={0,1,0,-1},v[]={1,0,-1,0};
int n,m,d[25][15],f[205],g[205]; char a[25][15];
int R(int x){return ((rand()<<15)+rand())%x+1;}
bool invaild()
{
	rep(i,n) rep(j,m) d[i][j]=-1;
	int h=0,t=1; f[1]=0,g[1]=0,d[0][0]=0; if (a[0][0]=='#') return 1;
	while (h<t){
		int x=f[++h],y=g[h];
		rep(k,4){
			int i=x+u[k],j=y+v[k];
			if (a[i][j]!='#' && d[i][j]<0) d[i][j]=d[x][y]+1,f[++t]=i,g[t]=j;
		}
	}
	return d[n-1][m-1]<0;
}
int main()
{
	srand(time(0)); //Sleep(1000);
	freopen("E.in","w",stdout);
	rep(_,10){
		n=R(20-1)+1,m=R(9-1)+1; printf("%d %d\n",n,m);
		rep(i,n) rep(j,m) a[i][j]=R(5)>1?'.':'#'; 
		while (invaild()) rep(i,n) rep(j,m) a[i][j]=R(5)>1?'.':'#';
		
		rep(i,n){rep(j,m) putchar(a[i][j]); puts("");}
	}
	puts("0 0");
	return 0;
}
