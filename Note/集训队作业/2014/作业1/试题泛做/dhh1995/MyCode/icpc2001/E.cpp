#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=55; pair<int,int> p[N*N];
int a[N][N],x[N],y[N],z[N],u[N],v[N],Case,n,m,t,ans,T,x1,y1,x2,y2,L;
bool add(int x,int y,int t,int &f){if (!f || a[x][y]) return f=0; a[x][y]=t; return 1;}
void change(int i,int &X,int &Y){X=x[i]%n,Y=y[i]%m; if (z[i]&1) X=n-1-X; if (z[i]&2) Y=m-1-Y;}
void move(int i){if ((x[i]+.5)*v[i]/u[i]<y[i]+.5+1e-8) ++x[i]; else ++y[i];}
void upd(int res,int k,int i,int j)
{
	if (res==ans?k<T:res>ans) ans=res,T=k,L=0;
	if (res==ans && k==T) p[L++]=make_pair(++i,++j);
}
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF && (n || m)){
		scanf("%d",&t),ans=0;
		rep(i,t){
			scanf("%d%d",u+i,v+i),z[i]=0;
			if (u[i]<0) u[i]*=-1,z[i]|=1;
			if (v[i]<0) v[i]*=-1,z[i]|=2;
		}
		rep(i,t) rep(j,t) if (i<j){
			x[i]=y[i]=x[j]=y[j]=0; int k=1,f=1,g=1,res=0;
			rep(X,n) rep(Y,m) a[X][Y]=0;
			while (f || g){
				change(i,x1,y1),add(x1,y1,k,f),change(j,x2,y2),add(x2,y2,k,g);
				if (f) ++res,move(i); if (g) ++res,move(j); upd(res,k++,i,j);
				if (x1==x2 && y1==y2) f=0;
			}
		}
		printf("Case %d   Cells Illuminated: %d   Minimum Time: %d\n",++Case,ans,T);
		rep(i,L) printf("   Geoduck IDs:%3d%3d\n",p[i].first,p[i].second);
	}
	return 0;
}
