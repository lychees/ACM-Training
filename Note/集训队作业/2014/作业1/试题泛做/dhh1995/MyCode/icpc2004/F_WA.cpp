#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0,_=n;i<_;++i)
const int N=45;
int Case,t,n[N],m[N],p[N][N],r[N][N],c[N][N]; char st[2005],s[N][105][105],ch; vector<int> q;
void prt(int k)
{
	printf("    MAP %d:\n",k+1);
	printf("    +"); rep(j,m[k]) printf("-"); puts("+");
	rep(i,n[k]){printf("    |"); rep(j,m[k]) printf("%c",s[k][i][j]); puts("|");}
	printf("    +"); rep(j,m[k]) printf("-"); puts("+");
}
int get(char x,char y){return x=='-' || y=='-'?0:x==y?1:-1<<25;}
void cal(int x,int y)
{
	p[x][y]=0;
	for (int R=1-n[y];R<n[x];++R)
		for (int C=1-m[y];C<m[x];++C){
			int v=0,x1=max(-R,0),y1=max(-C,0),x2=min(n[y],n[x]-R),y2=min(m[y],m[x]-C);
			for (int i=x1;i<x2;++i) for (int j=y1;j<y2;++j) v+=get(s[x][i+R][j+C],s[y][i][j]);
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
	int res,u,v;
	for(;;){
		res=0;
		rep(i,q.size()) for (int j=i+1;j<_;++j){
			int x=q[i],y=q[j]; if (p[x][y]>res) res=p[x][y],u=i,v=j;
		}
//		printf("%d %d %d\n",res,q[u],q[v]);
		if (res){
			int x=q[u],y=q[v],R=r[x][y],C=c[x][y];
			n[t]=m[t]=0,move(x,max(-R,0),max(-C,0)),move(y,max(R,0),max(C,0));
//			printf("%d %d %d %d\n",x,y,R,C),prt(t);
			q.erase(q.begin()+v),q.erase(q.begin()+u);
			rep(i,q.size()) cal(q[i],t); q.push_back(t++);
		}else break;
	}
}
int main()
{
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	while (q.clear(),scanf("%d",&t),t){
		rep(k,t*2) rep(i,101) rep(j,101) s[k][i][j]='-';
		rep(k,t){
			scanf("%d%d",n+k,m+k),gets(st); q.push_back(k);
			rep(i,n[k]){gets(st); rep(j,m[k]) s[k][i][j]=st[j];}
		}
		rep(j,t) rep(i,j) cal(i,j); work();
		if (Case) puts(""); printf("Case %d\n",++Case);
		rep(i,q.size()){if (i) puts(""); prt(q[i]);}
	}
	return 0;
}
