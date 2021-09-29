#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=250; int c[N*3][N*3];
double pi=acos(-1.),an,cut; int Case,n,ans;
struct node{
	int x,y; node(){}
	node(int _x,int _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	int operator %(const node &A){return x*A.y-y*A.x;}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(0.+x*x+y*y);}
	void read(){scanf("%d%d",&x,&y),c[x+N][y+N]=-4;}
}a[35];
void work(node A,node B)
{
	if (A.x>B.x) swap(A,B); node C=B-A; int y1=min(A.y,B.y),y2=max(A.y,B.y);
	rep(i,A.x,B.x) rep(j,y1,N){
		int v=(node(i,j)-A)%C,&res=c[i+N][j+N];
		if (j<=y2 && res>-6) if (!v){if (res>=0) res=4;}else if (abs(v)<C.len()/2) res=-8;
		if (i<B.x && v<0) res^=1;
	}
}
int main()
{
	while (scanf("%d",&n),n){
		rep(x,-N,N) rep(y,-N,N) c[x+N][y+N]=0; ans=n-2,cut=0;
		rep(i,1,n) a[i].read(); a[0]=a[n],a[n+1]=a[1]; rep(i,1,n) work(a[i-1],a[i]);
		rep(x,-N,N) rep(y,-N,N){int v=c[x+N][y+N]; if (v>=0) if (v>3) ++ans; else ans+=v*2;}
		rep(i,1,n) if (c[a[i].x+N][a[i].y+N]<-6)
			an=(a[i+1]-a[i]).angle()-(a[i-1]-a[i]).angle(),cut+=an<0?an+pi*2:an;
		printf("%.3lf\n",n<3?0:ans*pi/8-cut/8);
	}
	return 0;
}
