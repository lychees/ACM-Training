#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,ans,c[6],d[6],e[6]; bool flag;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator /(const double &A){return node(x/A,y/A);}
	node operator *(const node &A){return node(x*A.x-y*A.y,x*A.y+y*A.x);}
	bool operator <(const node &A) const{return x==A.x?y<A.y:x<A.x;}
	double len(){return sqrt(x*x+y*y);}
	void snap(){x=round(x),y=round(y);}
	void read(){scanf("%lf%lf",&x,&y);}
}a[6],b[3];
int get(int *c)
{
	int x0=c[1]-c[0],x1=c[2]-c[1],x2=x0+x1,y0=c[4]-c[3],y1=c[5]-c[4],y2=y0+y1;
	if (!x0 && !x1 && !y0 && !y1) return 2; if (!x0 && !x1 || !y0 && !y1) return 0;
	if ((!x0 && !y0 || !x1 && !y1) && y2%x2==0 && y2/x2>0) return 1;
	if (!x0 || !x1 || !y0 || !y1) return 0;
	return y0%x0==0 && y1%x1==0 && y0/x0==y1/x1 && y0/x0>0;
}
int cal(node *b)
{
	sort(b,b+3); rep(i,3) c[i]=b[i].x,d[i]=b[i].y;
	ans+=get(c)*get(d);
}
void work(int x,int y)
{
	node V(x,y); V=V/V.len();
	rep(i,3) b[i]=a[i]*V,b[i].snap();
	cal(b); rep(i,3) b[i].y*=-1; cal(b);
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	for (;;){
		ans=flag=0;
		rep(i,6){
			a[i].read(); flag|=a[i]<node(0,0) || node(0,0)<a[i];
			if (i==2 && !flag) return 0;
		}
		sort(a+3,a+6); rep(i,6) c[i]=a[i].x,d[i]=a[i].y;
		for (int i=-10;i<=10;++i){
			work(-10,i),work(10,i);
			if (i>-10 && i<10) work(i,-10),work(i,10);
		}
		printf("Case %d: %s solution%s\n",++Case,ans?ans>1?"inconsistent":"equivalent":"no",ans?"s":"");
	}
}
