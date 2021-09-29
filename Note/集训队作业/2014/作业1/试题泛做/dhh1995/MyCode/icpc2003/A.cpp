#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=101,M=N*N*N*3;
int Case,F=1,n,m,l,cnt,res,ans,f[N*N],p[M],x[M],y[M],z[M]; char s[N][N];
int get(int x){return f[x]<0?x:f[x]=get(f[x]);}
bool merge(int x,int y){x=get(x),y=get(y); if (x!=y) return f[x]=y,--cnt,1; return 0;}
void add(int X,int Y,int Z){if (!Z) merge(X,Y); else p[l]=l,x[l]=X,y[l]=Y,z[l++]=Z;}
bool is(int x,int y){return x>=0 && y>=0 && x<n && y<m && s[x][y]=='#';}
bool cmp(const int i,const int j){return z[i]<z[j];}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		rep(i,n*m) f[i]=-1; l=cnt=res=ans=0;
		rep(i,n) scanf("%s",s+i);
		rep(i,n) rep(j,m) if (s[i][j]=='#'){
			int id=i*m+j,c0=1,c1=1,t0,t1; ++cnt;
			for (int k=j+1;k<m &&(c0 || c1);++k){
				t0=c0,t1=c1;
				if (t0 && is(i-1,k)) add(id,i*m+k-m,k-j-1),c0=0;
				if (t0 && t1 && is(i,k)) add(id,i*m+k,k-j-1),c0=c1=0;
				if (t1 && is(i+1,k)) add(id,i*m+k+m,k-j-1),c1=0;
			}
			c0=1,c1=1;
			for (int k=i+1;k<n;++k){
				t0=c0,t1=c1;
				if (t0 && is(k,j-1)) add(id,k*m+j-1,k-i-1),c0=0;
				if (t0 && t1 && is(k,j)) add(id,k*m+j,k-i-1),c0=c1=0;
				if (t1 && is(k,j+1)) add(id,k*m+j+1,k-i-1),c1=0;
			}
		}
		sort(p,p+l,cmp);
		rep(k,l){int i=p[k]; if (merge(x[i],y[i])) ++res,ans+=z[i];}
		if (F) F=0; else puts(""); printf("City %d\n",++Case);
		if (res) printf("%d bridge%s of total length %d\n",res,res>1?"s":"",ans);
		else if (cnt>1) puts("No bridges are possible.");
			else puts("No bridges are needed.");
		if (cnt>1) printf("%d disconnected groups\n",cnt);
	}
	return 0;
}
