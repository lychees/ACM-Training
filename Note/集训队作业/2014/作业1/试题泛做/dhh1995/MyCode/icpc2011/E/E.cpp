#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=2005,M=500005;
int Case,k,n,m,Q,r,ans,X,Y,x[M],y[M],c[N][N];
void add(int x,int y,int v)
{if (x<0) x=0; if (x>n) x=n; if (y<0) y=0; if (y>n) y=n; c[x][y]+=v;}
int main()
{
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	while (scanf("%d%d%d%d",&n,&m,&k,&Q),n && m){
		rep(i,k) scanf("%d%d",&X,&Y),x[i]=X+Y,y[i]=X-Y+m;
		printf("Case %d:\n",++Case); n+=m+1;
		while (Q--){
			scanf("%d",&r),X=Y=1,ans=0;
			rep(i,n) rep(j,n) c[i][j]=0;
			rep(i,k) add(x[i]-r,y[i]-r,1),add(x[i]+r+1,y[i]+r+1,1),
					add(x[i]-r,y[i]+r+1,-1),add(x[i]+r+1,y[i]-r,-1);
			rep(i,n) rep(j,n){
				int x=(i+j-m)/2,y=(i-j+m)/2;
				if (x>0 && y>0 && !((i+j-m)&1) && (c[i][j]==ans?y==Y?x<X:y<Y:c[i][j]>ans)) ans=c[i][j],X=x,Y=y;
				c[i+1][j]+=c[i][j],c[i][j+1]+=c[i][j],c[i+1][j+1]-=c[i][j];
			}
			printf("%d (%d,%d)\n",ans,X,Y);
		}
	}
	return 0;
}
