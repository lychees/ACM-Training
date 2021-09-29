#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
typedef long long ll;
typedef char arr[4][4];
const int u[]={1,0,-1,0},v[]={0,1,0,-1};
int Case,n,m,w,h,t,x,y,x0,y0; arr a[100005],e;
ll f[100005]; map<ll,int> d; bool b[4][4][4][4];
ll get(arr a){ll x=0; rep(i,n) rep(j,n) x=x*2*m+a[i][j]; return x;}
bool move(int x,int y,int p,int id)
{
	int i=x+u[p],j=y+v[p];
	if (i>=0 && i<n && j>=0 && j<n && !b[x][y][i][j]){
		if (!e[i][j]) return move(i,j,p,id);
		if (e[i][j]>m) if (e[i][j]==id+m) return e[i][j]=0,1; else return 0;
	}
	return e[x][y]=id,1;
}
bool turn(arr &a,int p,ll &y)
{
	rep(i,n) rep(j,n) e[i][j]=a[i][j]>m?a[i][j]:0;
	rep(i,n) rep(j,n){
		int x=p!=0?i:n-1-i,y=p!=1?j:n-1-j,id=a[x][y];
		if (id && id<=m) if (!move(x,y,p,id)) return 0;
	}
	return y=get(e),1;
}
int main()
{
	while (scanf("%d%d%d",&n,&m,&w),n){
		memset(a[1],0,sizeof(a[1])),memset(b,0,sizeof(b)),d.clear();
		rep(i,m*2) scanf("%d%d",&x,&y),a[1][x][y]=i+1;
		rep(i,w) scanf("%d%d%d%d",&x,&y,&x0,&y0),b[x][y][x0][y0]=b[x0][y0][x][y]=1;
		h=0,t=1,d[f[1]=get(a[1])]=0;
		while (h<t){
			ll x=f[++h],y; int D=d[x]+1;
			rep(i,4) if (turn(a[h],i,y)){
				if (d.find(y)==d.end()) d[f[++t]=y]=D,memcpy(a[t],e,sizeof(e));
				if (!y) break;
			}
			if (!y) break;
		}
		printf("Case %d: ",++Case);
		if (d.find(0)==d.end()) puts("impossible\n"); else printf("%d moves\n\n",d[0]);
	}
	return 0;
}
