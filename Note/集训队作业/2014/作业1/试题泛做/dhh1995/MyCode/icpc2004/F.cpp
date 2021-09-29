#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0,_=n;i<_;++i)
const int N=105;
int Case,t,n[N],m[N],p[N][N],r[N][N],c[N][N]; bool b[N]; char st[2005],s[N][105][105],ch;
void prt(int k)
{
	printf("    MAP %d:\n",k+1);
	printf("    +"); rep(j,m[k]) printf("-"); puts("+");
	rep(i,n[k]){printf("    |"); rep(j,m[k]) printf("%c",s[k][i][j]); puts("|");}
	printf("    +"); rep(j,m[k]) printf("-"); puts("+");
}
int get(char x,char y){return x=='-' || y=='-'?0:x==y?1:-1<<15;}
void cal(int x,int y)
{
	p[x][y]=0;
	for (int R=1-n[y];R<n[x];++R)
		for (int C=1-m[y];C<m[x];++C){
			int v=0,x1=max(R,0),y1=max(C,0),x2=min(n[x],n[y]+R),y2=min(m[x],m[y]+C);
			for (int i=x1;i<x2;++i) for (int j=y1;j<y2;++j) v+=get(s[x][i][j],s[y][i-R][j-C]);
			if (v>p[x][y]) p[x][y]=v,r[x][y]=R,c[x][y]=C;
		}
}
void move(int x,int R,int C)
{
	n[t]=max(n[t],n[x]+R),m[t]=max(m[t],m[x]+C);
	rep(i,n[x]) rep(j,m[x]) if ((ch=s[x][i][j])!='-') s[t][i+R][j+C]=ch;
}
void work()
{
	int res,x,y;
	for(;;){
		res=0;
		rep(i,t) if (b[i]) for (int j=i+1;j<t;++j) if (b[j])
			if (p[i][j]>res) res=p[i][j],x=i,y=j;
		if (res){
			int R=r[x][y],C=c[x][y]; rep(i,101) rep(j,101) s[t][i][j]='-';
			n[t]=m[t]=0,move(x,max(-R,0),max(-C,0)),move(y,max(R,0),max(C,0));
			b[x]=b[y]=0; rep(i,t) if (b[i]) cal(i,t); b[t++]=1;
		}else break;
	}
}
int main()
{
	while (scanf("%d",&t),t){
		rep(k,t){
			b[k]=1,scanf("%d%d",n+k,m+k),gets(st);
			rep(i,n[k]){gets(st); rep(j,m[k]) s[k][i][j]=st[j];}
		}
		rep(j,t) rep(i,j) cal(i,j); work();
		if (Case) puts(""); printf("Case %d\n",++Case);
		int w=0; rep(i,t) if (b[i]){if (w++) puts(""); prt(i);}
	}
	return 0;
}
