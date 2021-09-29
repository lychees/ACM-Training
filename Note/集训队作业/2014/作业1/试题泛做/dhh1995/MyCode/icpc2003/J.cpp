#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=52,inf=1<<25;
int Case,n,x,y,S,c,d[N]; char X[3],Y[3]; bool a[N][N];
int G(char x){return x<'a'?x-39:x-97;}
int F(int x){return x*20/19+(x%19>0);}
int main()
{
	while (scanf("%d",&n),n>=0){
		rep(i,52) rep(j,52) a[i][j]=0,d[i]=inf;
		rep(i,n) scanf("%s%s",X,Y),x=G(*X),y=G(*Y),a[x][y]=a[y][x]=1;
		scanf("%d%s%s",&c,X,Y),S=G(*X),y=G(*Y),d[y]=c;
		rep(_,52){
			int i=-1,D=inf;
			rep(j,52) if (d[j]>=0 && d[j]<D) D=d[j],i=j;
			if (S==i) break; d[i]=-1; if (i<26) ++D; else D=F(D);
			rep(j,52) if (a[i][j] && D<d[j]) d[j]=D;
		}
		printf("Case %d: %d\n",++Case,d[S]);
	}
	return 0;
}
