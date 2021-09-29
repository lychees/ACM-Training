#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=100005;
int data[N],next[N],son[N],ed[N],next1[N],son1[N],ed1[N];
int Case,n,m,h,t,x,y,L,r[N],f[N],v[N],o[N],z[N]; bool flag,u[N];
int main()
{
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	while (scanf("%d%d",&n,&m),n||m){
		L=h=t=flag=0; rep(i,n) r[i]=son[i]=son1[i]=0;
		rep(i,m) scanf("%d%d%d",&x,&y,data+i),ed[i]=y,next[i]=son[x],son[x]=i,
			ed1[i]=x,next1[i]=son1[y],son1[y]=i,++r[x];
		rep(i,n) if (!r[i]) f[++t]=i;
		while (h<t && !flag){
			x=f[++h],u[x]=v[x]=0;
			for (int p=son[x];p;p=next[p]) v[x]=max(v[x],v[ed[p]]+data[p]);
			for (int p=son[x];p;p=next[p]){
				y=ed[p];
				if (v[y]+data[p]==v[x]) u[x]|=u[y];
				else if (u[y]){flag=1; break;}
					else u[x]=1,o[++L]=p,z[L]=v[x]-v[y]-data[p];
			}
			for (int p=son1[x];p;p=next1[p]) if (!--r[ed1[p]]) f[++t]=ed1[p];
		}
		printf("Case %d: ",++Case);
		if (flag) puts("No solution");
		else{printf("%d %d\n",L,v[1]); rep(i,L) printf("%d %d\n",o[i],z[i]);}
	}
	return 0;
}
