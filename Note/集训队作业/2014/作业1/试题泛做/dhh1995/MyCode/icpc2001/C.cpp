#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int M=10,N=205;
int Case,n,L[N],E[N],x[N],y[N],slot[N][N],end[N][N]; bool u[N],b[N],o[N];
char a[N][N],s[N][N],dir[N],tmp[5];
int expand(int x,int y,char d)
{
	for (int i=1;;++i){
		++(d=='D'?x:y);
		if (slot[x][y]&(d=='D'?1:2)) return i-1;
		if (x==M || y==M) return i;
	}
}
bool check(int i,int x,int y,char d)
{
	rep(k,L[i]){
		if (end[x][y] || a[x][y]!=' ' && a[x][y]!=s[i][k]) return 0;
		if (d=='D'){if (slot[x][y+1]&2) return 0; ++x;}
		else{if (slot[x+1][y]&1) return 0; ++y;}
	}
	return !slot[x][y] && a[x][y]==' ';
}
void cover(int i,int x,int y,char d,int *c)
{
	rep(k,L[i]){if (a[x][y]==' ') c[k]=1,a[x][y]=s[i][k]; else c[k]=0; ++(d=='D'?x:y);}
	++end[x][y];
}
void uncover(int i,int x,int y,char d,int *c)
{rep(k,L[i]){if (c[k]) a[x][y]=' '; ++(d=='D'?x:y);} --end[x][y];}
void dfs()
{
	bool flag=1; rep(i,n+1) if (!b[i] && !o[i]) flag=0; if (flag) return;
	int j=-1,c[15]; rep(i,n) if (!u[i]) if (j<0 || a[x[i]][y[i]]!=' ') j=i;
	if (j<0){rep(i,n+1) o[i]|=!b[i]; return;} u[j]=1;
	rep(i,n+1) if (!b[i] && L[i]<=E[j] && check(i,x[j],y[j],dir[j])){
		b[i]=1,cover(i,x[j],y[j],dir[j],c),dfs(),b[i]=0,uncover(i,x[j],y[j],dir[j],c);
	}
	u[j]=0;
}
bool cmp(const int i,const int j){return strcmp(s[i],s[j])<0;}
int main()
{
	while (scanf("%d",&n)!=EOF && n){
		rep(i,M+1) rep(j,M+1) a[i][j]=' ',slot[i][j]=0,end[i][j]=0; int flag=0;
		rep(i,n){
			u[i]=0,scanf("%d%d%s",x+i,y+i,tmp),--x[i],--y[i],dir[i]=*tmp;
			if (x[i]<0 || y[i]<0 || x[i]>9 || y[i]>9) flag=-1;
			else slot[x[i]][y[i]]|=(dir[i]=='D'?1:2);
		}
		if (!flag) rep(i,n){E[i]=expand(x[i],y[i],dir[i]); if (E[i]<2) flag=-1;}
		rep(i,n+1) scanf("%s",s[i]),L[i]=strlen(s[i]),b[i]=o[i]=0;
		if (!flag) dfs();
		printf("Trial %d:",++Case);
		if (!flag) rep(i,n+1) if (o[i]) printf(" %s",s[i]),flag=1;
		puts(flag>0?"\n":" Impossible\n");
	}
	return 0;
}
