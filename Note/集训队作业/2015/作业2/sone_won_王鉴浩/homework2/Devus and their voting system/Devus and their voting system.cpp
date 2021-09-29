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
#define N 40
#define db long double
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
int i,j,k,n,m,u,r,v,t,w;
db f[N][N][N][N],g[N][N][N][N],C[N][N],x,an[N];
int main() {
	//freopen("DE.out","w",stdout);
	n=36;
	For(i,0,n) {
		C[i][0]=1;
		For(j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	For(r,1,n) g[0][0][r][r-1]=1;
	For(j,1,n)For(v,0,j-1)For(r,1,n-j) {
		For(w,1,r)For(t,0,min(v,w)) {
			int t_=v-t+(r-w);
			g[j][v][r][t_]+=C[r-1][w-1]*C[v][t]*C[j+1-v][w-t];
		}
	}
	f[0][1][0][0]=1;
	For(i,1,n) {
		for (j=n;j>=0;j--)
		For(k,1,max(1,j))For(u,0,j/k)For(v,0,j) if (x=f[j][k][u][v]) {
			For(r,1,n-j) {
				int j_=j+r;
				int k_=max(k,r);
				int u_=r>k?1:r==k?u+1:u;
				For(t,0,j_) f[j_][k_][u_][t]+=x*g[j][v][r][t];
			}
		}
		For(k,1,i)For(u,1,i/k) an[i]+=f[i][k][u][0]*u;
		db sum=i;
		For(j,1,i-1) sum*=i-1;
		an[i]/=sum;
	}
	/*For(i,1,n) {
		double re=an[i];
		printf("%lf,\n",re);
	}
	printf("%d\n",clock());*/
	int T;
	scanf("%d",&T);
	for (;T;T--) {
		scanf("%d",&n);
		double re=an[n];
		printf("%lf\n",re);
	}
	return 0;
}
