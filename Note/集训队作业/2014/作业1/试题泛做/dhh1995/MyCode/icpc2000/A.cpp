#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=12,u[5]={1,0,-1,0},v[5]={0,1,0,-1};
int sx,sy,ex,ey,dir,x,y,z,d[N][N][4]; bool a[N][N][4][4]; char s[25];
struct node{
	int x,y,z; node(){}
	node(int _x,int _y,int _z):x(_x),y(_y),z(_z){}
	node move(int d){return node(x+u[d],y+v[d],d);}
	bool operator !=(node A){return x!=A.x || y!=A.y || z!=A.z;}
	void prt(){printf(" (%d,%d)",x,y);}
}f[N*N*4],pre[N][N][4],o[N*N*4];
int chg(char d){return d=='F'?0:d=='R'?3:1;}
int get(char d){return d=='S'?0:d=='E'?1:d=='N'?2:3;}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	while (scanf("%s",s),strcmp(s,"END")){
		puts(s); scanf("%d%d%s%d%d",&sx,&sy,s,&ex,&ey),dir=get(*s);
		memset(a,0,sizeof(d)),memset(d,0,sizeof(d));
		while (scanf("%d",&x),x){
			scanf("%d",&y);
			while (scanf("%s",s),*s!='*'){
				z=get(*s);
				rep(i,1,strlen(s)-1) a[x][y][z][(z+chg(s[i]))%4]=1;
			}
		}
		int h=0,t=1,ans=0; node S(sx,sy,dir),A=S;
		z=dir,x=sx+u[z],y=sy+v[z]; d[x][y][z]=2; f[1]=node(x,y,z),pre[x][y][z]=S;
		while (h<t){
			A=f[++h]; x=A.x,y=A.y,z=A.z;
			if (x==ex && y==ey){ans=d[x][y][z]; break;}
			rep(i,0,3) if (a[x][y][z][i]){
				node B=A.move(i);
				if (B.x>0 && B.x<10 && B.y>0 && B.y<10 && !d[B.x][B.y][B.z])
					d[B.x][B.y][B.z]=d[x][y][z]+1,pre[B.x][B.y][B.z]=A,f[++t]=B;
			}
		}
		if (ans){
			int L=ans; while (A!=f[1]) o[L--]=A,A=pre[A.x][A.y][A.z];
			o[2]=A,o[1]=S;
			rep(i,1,ans){
				if (i%10==1) printf(" "); o[i].prt();
				if (i==ans || i%10==0) puts("");
			}
		}else puts("  No Solution Possible");
	}
	return 0;
}
