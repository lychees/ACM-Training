#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define DEBUG {printf("Debuging...\n");exit(0);} 
#define N 105
using namespace std;

int n,cas;
double Vl,Vp,Circum;

namespace Geometry{
	const double EPS=1e-8;
	int dcmp(const double &a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	double round(double x,int k){
		for (int i=1;i<=k;i++) x*=10;
		x=floor(x+0.5);
		for (int i=1;i<=k;i++) x/=10;
		return x;
	}
	inline double sqr(double a){return a*a;}	
	
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){};
		void read(){scanf("%lf%lf",&x,&y);}
		double len()const{return sqrt(sqr(x)+sqr(y));}
		double dis(const Point &A)const{return sqrt(sqr(A.x-x)+sqr(A.y-y));}
		void print()const{
			printf("%.2lf %.2lf\n",x,y);
		}
	};
	Point a[N],P;
	double det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	double dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}//Atention not '-'!
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	Point operator * (const double &k,const Point &A){return Point(A.x*k,A.y*k);}
	Point operator * (const Point &A,const double &k){return Point(A.x*k,A.y*k);}
	Point operator / (const Point &A,const double &k){if (!k) return Point(0,0);return Point(A.x/k,A.y/k);}
	bool operator == (const Point &A,const Point &B){return dcmp(A.x,B.x)==0&&dcmp(A.y,B.y)==0;}
	bool operator != (const Point &A,const Point &B){return dcmp(A.x,B.x)!=0||dcmp(A.y,B.y)!=0;}
	
	
	struct Line{
		Point A,dir;
		Line(Point A=Point(0,0),Point dir=Point(0,0)):A(A),dir(dir){};
		int position(const Point &P){
			if (dir==Point(0,0)) return 0;
			Point dir2(P-A);
			if (dir2==Point(0,0)) return 4;
			if (dcmp(det(dir,dir2))!=0) return 0;
			if (dcmp(dot(dir,dir2))<0) return 1;
			if (dcmp(dir2.len(),dir.len())<0) return 3;
			if (dcmp(dir2.len(),dir.len())>0) return 2;
			return 5;
   		}
	};
	Line l[N];
	bool intersectLine(const Line &la,const Line &lb,Point &P){
		Point A(la.A),A1(la.A+la.dir),
                 B(lb.A),B1(lb.A+lb.dir);
		double s1=det(B-A,B1-A),s2=det(B-A1,B1-A1),s=s1-s2;
  		if (dcmp(s)==0) return false;
		P=A+la.dir*s1/s;
		return true;
	}
	bool between(const Point &P,const Point &A,const Point &B){return dcmp(dot(A-P,B-P))<=0;}
	bool intersectSeg(const Line &la,const Line &lb,Point &P){
		Point A(la.A),A1(la.A+la.dir),
                 B(lb.A),B1(lb.A+lb.dir);
		int d1=dcmp(det(A1-A,B-A)),d2=dcmp(det(A1-A,B1-A)),d3=dcmp(det(B1-B,A-B)),d4=dcmp(det(B1-B,A1-B));
		if ((d1^d2)==-2&&(d3^d4)==-2){
			double s1=det(B-A,B1-A),s2=det(B-A1,B1-A1);
			P=A+la.dir*s1/(s1-s2);
            return true;
		}
		if (!d1&&!d3) return false;
		if (!d1&&between(B, A,A1))  {P=B; return true;}
		if (!d2&&between(B1,A,A1)) {P=B1;return true;}
		if (!d3&&between(A, B,B1))  {P=A; return true;}
		if (!d4&&between(A1,B,B1)) {P=A1;return true;}
		return false;
	}
    
	bool inPoly(const Point &P){
		for (int i=1;i<=n;i++) if (l[i].position(P)>=3) return false;
		int t,check;Point A;
		while (1){
			t=1;check=0;
			double r=rand()%30000/100.0;
			Line l1(P,Point(std::cos(r),std::sin(r)));
			for (int i=1;i<=n;i++){
                if (intersectLine(l[i],l1,A)&&l1.position(A)>1){
					if (l[i].position(A)>=4){t=0;break;}
					if (l[i].position(A)==3) check^=1;
				}
			}
			if (t) return check;
		}
	}
	
}
using namespace Geometry;


namespace GT{
	namespace Graph{
		double edge[N][N];
		void build(int a,int b,double c){
			edge[a][b]=c;
		}
	}
	using namespace Graph;
	bool goThrough(const Point &A,const Point &B){
		Line l1(A,B-A);
		Point P;
		for (int i=1;i<=n;i++) 
			if (intersectSeg(l[i],l1,P)){
				if (P!=A&&P!=B) return false;
			}
		Point C=(A+B)/2;
		if (inPoly(C)) return false;
		return true;
	}
	void makeGraph(){
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				if (goThrough(a[i],a[j])){
					build(i,j,a[i].dis(a[j]));
					build(j,i,a[i].dis(a[j]));
				}
		for (int i=1;i<=n;i++) if (goThrough(P,a[i])){
			build(i,n+1,P.dis(a[i]));
			build(n+1,i,P.dis(a[i]));
		}
	}
	void newNode(const Point &A){
		for (int i=1;i<=n+1;i++) edge[n+2][i]=edge[i][n+2]=0;
		for (int i=1;i<=n;i++) if (goThrough(A,a[i])){
			build(n+2,i,A.dis(a[i]));
			build(i,n+2,A.dis(a[i]));
		}
		if (goThrough(P,A)){
			build(n+2,n+1,A.dis(P));
			build(n+1,n+2,A.dis(P));
		}
	}
	namespace SSSP{
		const double INF=0x7fffffff/3;
		double dis[N];
		int Q[N],use[N];
		double spfa(){
			for (int i=1;i<=n+2;i++) dis[i]=INF;
			dis[n+1]=0;
			Q[1]=n+1;
			for (int p1=1,p2=1;p1<=p2;p1++){
				int u=Q[p1%(n+2)];
				use[u]=0;
				for (int v=1;v<=n+2;v++) if (edge[u][v]){
					if (dis[u]+edge[u][v]<dis[v]){
						dis[v]=dis[u]+edge[u][v];
						if (!use[v]){
							use[v]=1;
							Q[(++p2)%(n+2)]=v;
						}
					}
				}
			}
			return dis[n+2];
		}
	}
	using namespace SSSP;
}
using namespace GT;

bool can(double len,const Point &A){
	newNode(A);
	double x=len,y=spfa();
	return dcmp(x/Vl,y/Vp)>=0;
}
void chuli(double time,int &a,int &b){
	a=b=0;
	time=time-trunc(time);
	time*=60;
	int tt=int(round(time));
	b=tt%10;
	a=tt/10;
}
void output(double len){
	double time=len/Vl;
	time=round(time,4);
	int a,b;
	chuli(time,a,b);
	printf("Case %d: Time = %.lf:%d%d\n",++cas,trunc(time),a,b);
}
Point getPoint(double len){
	len-=trunc(len/Circum)*Circum;
	double now=0; 
	for (int i=1;i<=n;i++){
		if (now==len) return a[i];
		if (dcmp(now+a[i].dis(a[i+1]),len)<=0){
			now+=a[i].dis(a[i+1]);
			continue;
		}
		Point dir(a[i+1]-a[i]);
		return a[i]+dir/dir.len()*(len-now);
	}
	return Point(INF,INF);
}
void getAns(){
	double l=0,r=1e6,mid;
	Point A;
	while (r-l>1e-5){
		mid=(l+r)/2;
		A=getPoint(mid);
		if (can(mid,A)) r=mid;else l=mid;
	}
	output(l);
}
void init(){
	memset(edge,0,sizeof(edge));
}
void deal(){
	a[n+1]=a[1];
	for (int i=1;i<=n;i++) l[i]=Line(a[i],a[i+1]-a[i]);
	Circum=0;
	for (int i=1;i<=n;i++) Circum+=a[i].dis(a[i+1]);
}
int main(){
	freopen("collecting.in","r",stdin);
	freopen("collecting.out","w",stdout);
	while (scanf("%d",&n)!=EOF&&n){
		init();
		for (int i=1;i<=n;i++) a[i].read();
		P.read();
		scanf("%lf%lf",&Vl,&Vp);
		deal();
		makeGraph();
		getAns();
	}
	return 0;
}
