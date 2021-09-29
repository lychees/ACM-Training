#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int u[4]={1,0,-1,0},v[4]={0,1,0,-1};
bool b[9][9]; int Case,n,m,S,ans,a[9][9],d[9][9],s[5],X[5],Y[5];
bool empty(int x,int y){return x>=0 && x<n && y>=0 && y<m && !b[x][y];}
void dfs(int x,int y,int t,int i)
{
	int c=0,x1=x,y1=y,dir=-1; rep(k,4) if (empty(x+u[k],y+v[k])) ++c,x1+=u[k],y1+=v[k];
	if (c==2 && !empty(x1,y1) || !c && t<S || a[x][y] && t<a[x][y]) return;
	if (t==s[i] && (x!=X[i] || y!=Y[i])) return; i+=t==s[i]; if (i>3){++ans; return;}
	int D=abs(x-X[i])+abs(y-Y[i]); if (t+D>s[i] || (t+D&1)!=(s[i]&1)) return;
	rep(k,4) if (empty(x+u[k],y+v[k]) && d[x+u[k]][y+v[k]]==1 && (x+u[k] || y+v[k]!=1)){if (dir>=0) return; dir=k;}
	rep(k,4) if (dir<0 || k==dir){
		x1=x+u[k],y1=y+v[k];
		if (empty(x1,y1)){
			b[x1][y1]=1; rep(l,4) if (empty(x1+u[l],y1+v[l])) --d[x1+u[l]][y1+v[l]];
			dfs(x1,y1,t+1,i);
			b[x1][y1]=0; rep(l,4) if (empty(x1+u[l],y1+v[l])) ++d[x1+u[l]][y1+v[l]];
		}
	}
}
int main()
{
	while (scanf("%d%d",&n,&m),n){
		S=n*m; rep(i,n) rep(j,m) a[i][j]=b[i][j]=0,d[i][j]=4-(!i || i+1==n)-(!j || j+1==m);
		rep(i,4) i<3?scanf("%d%d",X+i,Y+i):(X[i]=0,Y[i]=1),a[X[i]][Y[i]]=s[i]=S*(i+1)/4;
		b[0][0]=1,--d[0][1],--d[1][0],ans=0,dfs(0,0,1,0),printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
