#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=205;
int Case,n,m,s,l,top,tot,D,x[5],y[5],f[N],dfn[N],low[N],stack[N],num[N],son[N],ed[N*N],next[N*N];
bool in[N],b[N][N],d[N],F; char ch;
void tarjan(int x)
{
	dfn[x]=low[x]=++D,in[stack[++top]=x]=1; int y;
	for (int p=son[x];p;p=next[p]){
		y=ed[p];
		if (!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);
		else if (in[y]) low[x]=min(low[x],dfn[y]);
	}
	if (low[x]==dfn[x]){++tot; do in[y=stack[top--]]=0,num[y]=tot; while (y!=x);}
}
bool reach(int S,int T)
{
	int h=0,t=1; f[1]=S; rep(i,n) d[i]=0; d[S]=1;
	while (h<t){
		int x=f[++h];
		for (int p=son[x];p;p=next[p]){
			int y=ed[p]; if (y==T) return 1;
			if (!d[y]) d[y]=1,f[++t]=y;
		}
	}
	return 0;
}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		n*=2,l=F=D=top=tot=0; rep(i,n){son[i]=dfn[i]=0; rep(j,n) b[i][j]=0;}
		rep(i,m){
			scanf("%d",&s);
			rep(i,s) scanf("%d%*c%c",x+i,&ch),--x[i],y[i]=ch=='y';
			if (s<3){rep(i,s) b[x[i]*2|!y[i]][x[i]*2|y[i]]=1;}
			else rep(i,s) rep(j,s) if (i!=j) b[x[i]*2|!y[i]][x[j]*2|y[j]]=1;
		}
	 	rep(i,n) rep(j,n) if (b[i][j]) ed[++l]=j,next[l]=son[i],son[i]=l;
	 	rep(i,n) if (!dfn[i]) tarjan(i);
		rep(i,n) if (i&1) F|=num[i]==num[i^1];
		printf("Case %d: ",++Case);
		if (F) puts("impossible");
		else {rep(i,n) if (i&1) putchar(reach(i,i^1)?'n':reach(i^1,i)?'y':'?'); puts("");}
	}
	return 0;
}
