#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
//front botton left right top back
const int N=50005,u[]={1,0,0,-1},v[]={0,1,-1,0},
	w[4][6]={{1,5,2,3,0,4},{0,3,1,4,2,5},{0,2,4,1,3,5},{4,0,2,3,5,1}};
int L,n,m,sx,sy,st,T,F,a[15][15],f[35][7],g[35][7],id[N],X[N],Y[N];
bool b[15][15][35]; char s[25];
int get(int *a)
{
	int x=0,b[6]; rep(i,6) x=x*6+a[i]-1; if (id[x]) return id[x];
	x=id[x]=++L; rep(i,6) f[x][i]=a[i];
	rep(k,4){rep(i,6) b[w[k][i]]=a[i]; g[x][k]=get(b);} return x;
}
bool dfs(int t,int x,int y,int s)
{
	if (t && x==sx && y==sy) return L=t+1,X[t]=x,Y[t]=y,1;
	if (x<0 || x>=n || y<0 || y>=m || b[x][y][s]) return 0; b[x][y][s]=1;
	rep(k,4){
		int i=x+u[k],j=y+v[k];
		if ((a[i][j]<0 || a[i][j]==f[s][4]) && dfs(t+1,i,j,g[s][k])) return X[t]=x,Y[t]=y,1;
	}
	return 0;
}
int main()
{
	rep(i,6) f[0][i]=i+1; get(f[0]);
	while (scanf("%s",s),strcmp(s,"END")){
		puts(s),scanf("%d%d%d%d%d%d",&n,&m,&sx,&sy,&T,&F),--sx,--sy;
		for (int i=24;i;--i) if (f[i][0]==F && f[i][4]==T) st=i;
		rep(i,n) rep(j,m){scanf("%d",a[i]+j); rep(k,24) b[i][j][k+1]=0;}
		if (dfs(0,sx,sy,st)){
			rep(i,L){
				if (i%9==0) printf("  "); printf("(%d,%d)",X[i]+1,Y[i]+1);
				if (i+1<L) printf(","); if (i+1==L || i%9==8) puts("");
			}
		}else puts("  No Solution Possible");
	}
	return 0;
}
