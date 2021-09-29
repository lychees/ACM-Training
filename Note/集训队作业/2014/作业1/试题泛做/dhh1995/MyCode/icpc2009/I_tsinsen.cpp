#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=505;
int Case,n,m,x[N],y[N],dx[N],dy[N],W[N],H[N],w[N],h[N],f[N],a[N][8],b[4],c[4],next[N],son[N];
bool in(int i,int j){return x[i]<x[j] && y[i]<y[j] && x[j]+w[j]<x[i]+w[i] && y[j]+h[j]<y[i]+h[i];}
void get(int w,int W)
{
	c[3]=w-c[1]-c[2];
	rep(i,3) if (!b[i]) w-=c[i],W-=c[i];
	rep(i,3) if (b[i]) c[i]=1LL*c[i]*W/w;
}
void dfs(int i,int fa)
{
	if (i){
		b[1]=a[i][5],b[2]=a[i][1],b[3]=a[i][6],c[1]=dx[i],c[2]=w[i];
		get(w[fa],W[fa]),x[i]=x[fa]+c[1],W[i]=c[2];
		b[1]=a[i][3],b[2]=a[i][2],b[3]=a[i][4],c[1]=dy[i],c[2]=h[i];
		get(h[fa],H[fa]),y[i]=y[fa]+c[1],H[i]=c[2];
	}
	for (int j=son[i];j;j=next[j]) dfs(j,i);
}
int main()
{
	while (++Case,son[0]=0,scanf("%d%d%d%d",&n,&m,w,h)!=EOF){
		rep(i,n){
			scanf("%d%d%d%d",x+i,y+i,w+i,h+i); rep(j,6) scanf("%d",a[i]+j);
			son[i]=0,a[i][3]|=!a[i][2]&&!a[i][4],a[i][6]|=!a[i][1]&&!a[i][5];
		}
		rep(i,n){
			int k=0; rep(j,n) if (i!=j && in(j,i) && in(k,j)) k=j;
			dx[i]=x[i]-x[k],dy[i]=y[i]-y[k]; next[i]=son[k],son[k]=i;
		}
		rep(_,m){
//			printf("Case %d, ",Case);
			printf("resize operation %d:\n",_);
			scanf("%d%d",W,H); dfs(0,0);
			rep(i,n) //printf("    "),
				printf("Window %d, x = %d, y = %d, width = %d, height = %d\n",i,x[i],y[i],W[i],H[i]);
		}
	}
	return 0;
}
