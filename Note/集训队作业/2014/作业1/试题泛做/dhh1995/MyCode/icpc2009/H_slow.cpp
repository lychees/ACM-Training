#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,s,x[5],y[5]; bool b[205][205],F; char ch;
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		n*=2; rep(i,n) rep(j,n) b[i][j]=0;
		rep(i,m){
			scanf("%d",&s);
			rep(i,s) scanf("%d%*c%c",x+i,&ch),--x[i],y[i]=ch=='y';
			if (s<3){rep(i,s) b[x[i]*2|!y[i]][x[i]*2|y[i]]=1;}
			else rep(i,s) rep(j,s) if (i!=j) b[x[i]*2|!y[i]][x[j]*2|y[j]]=1;
		}
		rep(k,n) rep(i,n) rep(j,n) b[i][j]|=b[i][k]&&b[k][j];
		F=0; rep(i,n) if (i&1) F|=b[i][i^1]&&b[i^1][i];
		printf("Case %d: ",++Case);
		if (F) puts("impossible");
		else {rep(i,n) if (i&1) putchar(b[i][i^1]?'n':b[i^1][i]?'y':'?'); puts("");}
	}
	return 0;
}
