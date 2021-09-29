#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#define fi first
#define se second
#define PA pair<int,int>
#define VI vector<int>
#define VP vector<PA >
#define mk(x,y) make_pair(x,y)
#define N 210
#define M N*2
#define mo 10007
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
int i,j,k,n,m,nn,an;
int a[M][M],b[M][M],f[N][N][N];
char p[N];
inline void mul(int a[M][M],int b[M][M]) {
	int i,j,k,c[M][M]={};
	For(i,1,nn)For(j,i,nn)For(k,j,nn) c[i][k]=(a[i][j]*b[j][k]+c[i][k])%mo;
	For(i,1,nn)For(j,i,nn) a[i][j]=c[i][j];
}
inline void S(int &x,int y) {
	x=(x+y)%mo;
}
inline void pre() {
	int i,j,k,u,x;
	f[1][m][0]=1;
	for (i=m-1;i>=0;i--) For(j,1,m-i) For(k,0,m) {
		u=j+i;
		if ((x=f[j][u][k])>0) {
			if (p[j]==p[u]) S(f[j+1][u-1][k],x);
			else S(f[j+1][u][k+1],x),S(f[j][u-1][k+1],x);
		}
	}
}
int main() {
	scanf("%s%d",p+1,&n);
	m=strlen(p+1);
	pre();
	n+=m;
	int flag=n&1;
	n/=2;
	int n24=m,n25=(m+1)/2,n26=n25+1;
	nn=n24+n25+n26;
	For(i,1,n24+n25-1) a[i][i+1]=1;
	For(i,0,n25) a[n24+i][nn-i]=1;
	For(i,1,n24) a[i][i]=24;
	For(i,1,n25) a[n24+i][n24+i]=25;
	For(i,1,n26) a[n24+n25+i][n24+n25+i]=26;
	For(i,1,nn) b[i][i]=1;
	for (k=n;k;k/=2) {
		if (k&1) mul(b,a);
		mul(a,a);
	}
	For(i,0,m) {
		int v24=i,v25=(m-i+1)/2,s=0;
		For(j,1,m) S(s,f[j+1][j-1][i]),S(s,f[j][j-1][i]);
		an=(s*b[n24-v24+1][nn-v25]%mo*(flag?26:1)+an)%mo;
		
		if (flag&&(m-v24)%2==1) {
			s=0;
			For(j,1,m) S(s,f[j][j][i]);
			an=(s*b[n24-v24+1][n24+v25]+an)%mo;
		}
	}
	printf("%d\n",an);
	return 0;
}
