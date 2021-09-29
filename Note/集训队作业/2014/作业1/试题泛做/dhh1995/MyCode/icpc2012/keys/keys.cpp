#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=55;
int Case,E,n,ans,res,ed[N],next[N],son[N],C[3],c[N][3],a[N],b[N],f[N][3]; bool v[N]; char s[5];
int id(int x){x-='a'; if (b[x]<0) b[x]=n++; return b[x];}
void add(int x,int y)
{
	if (x>y) swap(x,y); y=id(y);
	if (x<'a') c[y][1+(x<'N')]+=2,++C[1+(x<'N')];
	else x=id(x),ed[++E]=y,next[E]=son[x],son[x]=E,ed[++E]=x,next[E]=son[y],son[y]=E;
}
void dfs(int x)
{
	v[x]=1; f[x][1]=(a[x]==2)*99,f[x][2]=(a[x]==1)*99;
	for (int p=son[x];p;p=next[p]){
		int y=ed[p];
		if (!v[y]) dfs(y),f[x][1]+=min(f[y][1],f[y][2]+1),f[x][2]+=min(f[y][1]+1,f[y][2]);
	}
}
void work(int k)
{
	if (k>ans) return; if (k<ans) ans=k,res=99;
	int m=-!!C[1]-!!C[2]; rep(i,n) v[i]=0,f[i][1]=f[i][2]=99;
	rep(i,n) if (a[i] && !v[i]) dfs(i),m+=min(f[i][1],f[i][2])*2+1;
	if (m<res) res=m;
}
void check(int k)
{
	int s[3]={0,0,0},t; rep(i,n) ++s[a[i]];
	if (!s[1] && C[1])
		{rep(i,n) if (a[i]!=1) t=a[i],a[i]=1,work(k+c[i][2]-c[i][1]),a[i]=t;}
	else if (!s[2] && C[2])
		{rep(i,n) if (a[i]!=2) t=a[i],a[i]=2,work(k+c[i][1]-c[i][2]),a[i]=t;}
	else work(k);
}
void dfs(int t,int k)
{
	if (k>ans) return; while (t<n && !c[t][1] && !c[t][2]) ++t;
	if (t==n){check(k); return;}
	if (c[t][1]) a[t]=1,dfs(t+1,k+c[t][2]);
	if (c[t][2]) a[t]=2,dfs(t+1,k+c[t][1]);
	a[t]=0;
}
int main()
{
	freopen("keys.in","r",stdin);
	freopen("keys.out","w",stdout);
	while (scanf("%s",s)!=EOF){
		E=n=C[1]=C[2]=0; rep(i,26) b[i]=-1,c[i][1]=c[i][2]=0,son[i]=0;
		do add(s[0],s[1]),scanf("%s",s); while (*s!='0');
		ans=99,dfs(0,0); printf("Case %d: ",++Case);
		if (n==1 && C[1] && C[2]) puts("impossible"); else printf("%d %d\n",ans,res);
	}
	return 0;
}
