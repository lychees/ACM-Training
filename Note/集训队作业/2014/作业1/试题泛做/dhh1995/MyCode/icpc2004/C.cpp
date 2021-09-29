#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
//front, left, back, right, top, bottom
const int u[7]={0,1,0,-1,0,0,0},v[7]={0,0,0,0,0,1,-1},w[7]={0,0,1,0,-1,0,0};
int n,flag,c,a[12][12][12][8]; char s[12];
void chg(int d,int &x,int &y,int &z)
{
	if (d==2) x=n+1-z,z=1;
	if (d==3) x=n,z=n+1-z;
	if (d==4) x=z,z=n;
	if (d==5) x=n+1-y,y=1;
	if (d==6) x=y,y=n;
}
void push(int d,int x,int y,int z,int c)
{
	if (!c) return; while (*a[x][y][z]<0) x+=u[d],y+=v[d],z+=w[d]; a[x][y][z][d]=c;
	if (!*a[x][y][z]) *a[x][y][z]=c; else if (*a[x][y][z]!=c) *a[x][y][z]=-1;
}
int main()
{
	while (scanf("%d",&n),n){
		memset(a,0,sizeof(a));
		rep(i,n) rep(d,6){
			scanf("%s",s+1); int x,y,z;
			rep(j,n) x=1,y=i,z=j,chg(d,x,y,z),push(d,x,y,z,s[j]=='.'?-1:s[j]-64);
		}
		c=n*n*n,flag=1;
		while (flag){
			flag=0;
//			rep(i,n){rep(j,n){rep(k,n) printf("%2d ",*a[i][j][k]); puts("");}puts("");}
			rep(i,n) rep(j,n) rep(k,n) if (*a[i][j][k]==-1)
				{*a[i][j][k]=-2,flag=1,--c; rep(d,6) push(d,i,j,k,a[i][j][k][d]);}
		}
		printf("Maximum weight: %d gram(s)\n",c);
	}
	return 0;
}
