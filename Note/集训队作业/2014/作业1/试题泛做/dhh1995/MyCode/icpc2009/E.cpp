#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=100005;
int Case,n,m,h,t,x,y,L,r[N],f[N],u0[N],u1[N],v0[N],v1[N],o[N],z[N];
int data[N],next[N],son[N],ed[N],next1[N],son1[N],ed1[N]; bool flag;
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		L=h=t=flag=0; rep(i,n) u1[i]=v1[i]=r[i]=son[i]=son1[i]=0,u0[i]=v0[i]=1<<28;
		rep(i,m) scanf("%d%d%d",&x,&y,data+i),ed[i]=y,next[i]=son[x],son[x]=i,
			ed1[i]=x,next1[i]=son1[y],son1[y]=i,++r[x];
		rep(i,n) if (!r[i]) f[++t]=i; v0[n]=u0[1]=0;
		while (h<t){
			x=f[++h];
			for (int p=son1[x];p;p=next1[p]){
				y=ed1[p],v1[y]=max(v1[y],v1[x]+data[p]),v0[y]=min(v0[y],v0[x]+data[p]);
				if (!--r[y]) f[++t]=y;
			}
		}
		for (int i=n;i;--i){
			x=f[i];
			for (int p=son[x];p;p=next[p])
				y=ed[p],u1[y]=max(u1[y],u1[x]+data[p]),u0[y]=min(u0[y],u0[x]+data[p]);
		}
		rep(i,n) flag|=u0[i]!=u1[i] && v0[i]!=v1[i];
		printf("Case %d: ",++Case); if (flag){puts("No solution"); continue;}
		rep(x,n) for (int p=son[x];p;p=next[p]){
			y=ed[p];
			if (u1[x]==u0[x] && u1[y]!=u0[y] && u1[x]+data[p]+v1[y]<v1[1])
				o[++L]=p,z[L]=v1[1]-u1[x]-data[p]-v1[y];
		}
		printf("%d %d\n",L,v1[1]); rep(i,L) printf("%d %d\n",o[i],z[i]);
	}
	return 0;
}
