#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=1005;
int Case,n,m,X,Y,w,x1[N],y1[N],x2[N],y2[N],x[N*4],y[N*3],b[N*4][N*3]; long long ans;
void add(int x[],int &n,int v,int m,int flag)
{
	if (v && flag<=0) x[n++]=v-1; x[n++]=v;
	if (v+1<m && flag>=0) x[n++]=v+1;
}
int main()
{
	while (scanf("%d%d%d",&Y,&X,&w),X){
		ans=n=m=0; x[n++]=y[m++]=0;
		rep(i,w) scanf("%d%d%d%d",x1+i,y1+i,x2+i,y2+i),
			add(x,n,x1[i],X,-1),add(y,m,y1[i],Y,0),add(x,n,x2[i],X,1);
		sort(x,x+n),n=unique(x,x+n)-x,x[n]=X,sort(y,y+m),m=unique(y,y+m)-y,y[m]=Y;
		rep(i,n) rep(j,m) b[i][j]=0; b[n-1][m-1]=1;
		rep(i,w){
			int r=lower_bound(x,x+n,x2[i])-x,h=lower_bound(y,y+m,y1[i])-y;
			for (int l=lower_bound(x,x+n,x1[i])-x;l<=r;++l) b[l][h]=-1;
			}
		for (int i=n-1;i>=0;--i) for (int j=m-1;j>=0;--j) if (b[i][j]>0){
			if (i && !b[i-1][j]) b[i-1][j]=1;
			if (j && !b[i][j-1]) b[i][j-1]=1;
		}
		rep(i,n) rep(j,m) if (!b[i][j]) ans+=(x[i+1]-x[i]+0LL)*(y[j+1]-y[j]);
		printf("Case %d: %I64d\n",++Case,ans);
	}
	return 0;
}
