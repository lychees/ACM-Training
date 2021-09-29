#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define formap for (int j=1;j<m-1;++j) for (int i=0;i<n-1;++i)
const int B1=31,B2=37,N=3000007;
int n,m,ans,T,O,*V,G,g[N],id[256],L[105],d[105][105],dp[105],son[N],next[N],data[N];
char C,name[105],ch[105],a[10][10],f[N];
int get(char a){if (a!='-' && !id[a]) id[a]=++T,ch[T]=a; return id[a];}
inline void hash(int C,int &h1,int &h2)
{
	h1=h2=C;
	formap h1=(h1*B1+a[i][j]+1)%N,h2=h2*B2+a[i][j]+1;
}
inline int find(int H1,int H2)
{
	for (int p=son[H1];p;p=next[p]) if (data[p]==H2) return f[p];
	return -1;
}
inline void ins(int H1,int H2,int v)
{
	g[++G]=H1,f[G]=v,data[G]=H2,next[G]=son[H1],son[H1]=G;
}
inline void chg(int H1,int H2,int v)
{
	for (int p=son[H1];p;p=next[p]) if (data[p]==H2){f[p]=v; return;}
}
void dfs(int x,int y,int c)
{
	if (x<0 || a[x][y]!=c) return; a[x][y]=0,--C;
	dfs(x-1,y,c),dfs(x+1,y,c),dfs(x,y-1,c),dfs(x,y+1,c);
}
void work()
{
	formap if (a[i][j]>0 && !a[i+1][j]){
		int u=i; while (u && a[u-1][j]>0) --u;
		int d=i+1; while (!a[d+1][j]) ++d;
		for (int k=i;k>=u;--k) a[d-i+k][j]=a[k][j],a[k][j]=0;
	}
	bool flag=0;
	formap if (a[i][j]>0 && (a[i][j]==a[i+1][j] || a[i][j]==a[i][j+1])) flag=1,dfs(i,j,a[i][j]);
	if (flag) work();
}
inline int eval()
{
	rep(i,T) L[i]=0;
	formap if (a[i][j]>0){
		int x=a[i][j]-1;
		d[x][L[x]++]=j;
	}
	rep(i,T) if (L[i]==1) return 99;
	int res=0;
	rep(i,T){
		rep(j,L[i]+1) dp[j]=99; dp[0]=0;
		rep(j,L[i]){
			if (j+2<=L[i]){
				int v=max(d[i][j+1]-d[i][j]-1,0);
				if (dp[j]+v<dp[j+2]) dp[j+2]=dp[j]+v;
			}
			if (j+3<=L[i]){
				int v=max(d[i][j+1]-d[i][j]-1,0)+max(d[i][j+2]-d[i][j+1]-1,0);
				if (dp[j]+v<dp[j+3]) dp[j+3]=dp[j]+v;
			}
		}
		res+=dp[L[i]];
	}
	return max(res,1)+C;
}
bool cmp(const int i,const int j){return V[i]<V[j];}
int dfs(int res,int E)
{
	int H1,H2,opt; hash(res,H1,H2),opt=find(H1,H2);
	if (opt>=0) return opt; if (!C) return ins(H1,H2,0),0;
	if (res+E-C>=ans) return 99; opt=99,ins(H1,H2,99);
	char b[9][9],c=C; rep(i,n) rep(j,m) b[i][j]=a[i][j];
	int S=0,x[155],y[155],z[155],e[155],p[155];
	formap rep(k,2) if (a[i][j]>0 && !a[i][j+k-!k]){
		a[i][j+k-!k]=a[i][j],a[i][j]=0,work();
		if ((e[S]=eval())<99) p[S]=S,x[S]=i,y[S]=j,z[S++]=k;
		rep(i,n) rep(j,m) a[i][j]=b[i][j]; C=c;
	}
	V=e,sort(p,p+S,cmp);
	rep(_,S){
		int i=x[p[_]],j=y[p[_]],k=z[p[_]],E=e[p[_]];
		a[i][j+k-!k]=a[i][j],a[i][j]=0,work();
		opt=min(opt,dfs(res+1,E)+1),ans=min(ans,res+opt);
		rep(i,n) rep(j,m) a[i][j]=b[i][j]; C=c;
	}
	chg(H1,H2,opt); return opt;
}
void prt(char o,int i,int j,int k)
{
	printf("(%c,%d,%d,%c)",o,i,j,k?'R':'L');
	if (++O==ans || O%4==0) puts(""); else printf(" ");
}
void prt(int res,int opt)
{
	++res; if (!opt--) return; char b[9][9],c=C; rep(i,n) rep(j,m) b[i][j]=a[i][j];
	formap rep(k,2) if (a[i][j]>0 && !a[i][j+k-!k]){
		char o=ch[a[i][j]]; a[i][j+k-!k]=a[i][j],a[i][j]=0; work();
		int H1,H2; hash(res,H1,H2);
		if (find(H1,H2)==opt){prt(o,i,j,k),prt(res,opt); return;}
		rep(i,n) rep(j,m) a[i][j]=b[i][j]; C=c;
	}
}
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF && (n||m)){
		getchar(),gets(name),ans=12,O=0,C=0,id['#']=-1;
		rep(i,n){scanf("%s",a[i]); rep(j,m) a[i][j]=get(a[i][j]),C+=a[i][j]>0;}
		work(),ans=min(ans,dfs(0,eval()));
		printf("%s: Minimum solution length = %d\n",name,ans),prt(0,ans);
		rep(i,G) son[g[i+1]]=0; G=T=0; rep(i,255) id[i]=0;
	}
	return 0;
}
