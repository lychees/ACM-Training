#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=1005,M=500;
int Case,n,m,ans,p[N],q[N];
bool ax[N][N],bx[N][N],ay[N][N],by[N][N];
int chg(char a){return a=='L'?0:a=='R'?1:a=='U'?2:3;}
void dfs(int m,int l,int r,int u,int d)
{
	if (!m){ax[l][u]=ay[l][u]=ax[l][d]=ay[r][u]=1; return;}
	int z,dir; char opr[3]; scanf("%d%s",&z,opr),dir=chg(*opr); z=dir<2?p[z]:q[z];
	rep(i,0,n){
		int &res=dir<2?p[i]:q[i];
		if ((dir&1)==(res<z)) res=2*z-res;
	}
	int L=l,R=r,U=u,D=d;
	if (dir==0) L=min(L,2*z-R),R=z;
	if (dir==1) R=max(R,2*z-L),L=z;
	if (dir==2) U=min(U,2*z-D),D=z;
	if (dir==3) D=max(D,2*z-U),U=z;
	dfs(m-1,L,R,U,D);
	if (dir==0) rep(i,z,r) rep(j,u,d){
		int k=2*z-i;
		if (i<r) bx[i][j]|=ax[k-1][j],ax[k-1][j]&=k>l && (j==u || j==d);
		if (j<d) by[i][j]|=ay[k][j],ay[k][j]&=k>=l && i==r;
		if (i<r && (k<=l || j==u || j==d)) ax[i][j]|=bx[k-1][j],bx[k-1][j]&=k>l;
		if (j<d && k<=l) ay[i][j]|=by[k][j],by[k][j]&=k==l;
	}
	if (dir==1) rep(i,l,z) rep(j,u,d){
		int k=2*z-i;
		if (i<z) bx[i][j]|=ax[k-1][j],ax[k-1][j]&=k<=r && (j==u || j==d);
		if (j<d) by[i][j]|=ay[k][j],ay[k][j]&=k<=r && i==l;
		if (i<z && (k>r || j==u || j==d)) ax[i][j]|=bx[k-1][j],bx[k-1][j]&=k<=r;
		if (j<d && k>=r) ay[i][j]|=by[k][j],by[k][j]&=k==r;
	}
	if (dir==2) rep(i,l,r) rep(j,z,d){
		int k=2*z-j;
		if (i<r) bx[i][j]|=ax[i][k],ax[i][k]&=k>=u && j==d;
		if (j<d) by[i][j]|=ay[i][k-1],ay[i][k-1]&=k>u && (i==l || i==r);
		if (i<r && k<=u) ax[i][j]|=bx[i][k],bx[i][k]&=k==u;
		if (j<d && (k<=u || i==l || i==r)) ay[i][j]|=by[i][k-1],by[i][k-1]&=k>u;
	}
	if (dir==3) rep(i,l,r) rep(j,u,z){
		int k=2*z-j;
		if (i<r) bx[i][j]|=ax[i][k],ax[i][k]&=k<=d && j==u;
		if (j<z) by[i][j]|=ay[i][k-1],ay[i][k-1]&=k<=d && (i==l || i==r);
		if (i<r && k>=d) ax[i][j]|=bx[i][k],bx[i][k]&=k==d;
		if (j<z && (k>d || i==l || i==r)) ay[i][j]|=by[i][k-1],by[i][k-1]&=k<=d;
	}
}
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF && (n || m)){
		++n; rep(i,0,n) p[i]=M+i,q[i]=M+i;
		dfs(m,M,M+n,M,M+n),ans=-4;
		rep(i,M,M+n) rep(j,M,M+n) ans+=ax[i][j]+bx[i][j]+ay[i][j]+by[i][j];
		rep(i,M,M+n) rep(j,M,M+n) ax[i][j]=bx[i][j]=ay[i][j]=by[i][j]=0;
		printf("Case %d: %d pockets\n",++Case,ans);
	}
	return 0;
}
