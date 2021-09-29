#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 55
#define PolygonN N
using namespace std;

const int inf=0x2f2f2f2f;

namespace Geometry{
	const double EPS=1e-8;
	int dcmp(const double &a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){}; 
		void read(){
			scanf("%lf%lf",&x,&y);
		}
		void print()const{
			printf("%.2lf %.2lf\n",x,y);
		}
		Point rotate(const Point &angle){
			return Point(x*angle.x-y*angle.y,x*angle.y+y*angle.x);
		}
	};
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	Point operator * (const double &k,const Point &A){return Point(A.x*k,A.y*k);}
	Point operator * (const Point &A,const double &k){return Point(A.x*k,A.y*k);}
	Point operator / (const Point &A,const double &k){if (!k) return Point(0,0);return Point(A.x/k,A.y/k);}
	double det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	double dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}//Atention not '-'!

	struct Line{
		Point A,dir;
		Line(Point A=Point(0,0),Point dir=Point(0,0)):A(A),dir(dir){};
	};
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
		if (!d1&&!d3) return true;
		if (!d1&&between(B, A,A1))  {P=B; return true;}
		if (!d2&&between(B1,A,A1)) {P=B1;return true;}
		if (!d3&&between(A, B,B1))  {P=A; return true;}
		if (!d4&&between(A1,B,B1)) {P=A1;return true;}
		return false;
	}
	Line midLine(const Point &A,const Point &B){
		return Line((A+B)/2,(B-A).rotate(Point(0,1)));
	}

	struct Polygon{
		int n;Point a[PolygonN];
		int intersect(const Line &l){
			int x=0;Point P;
			a[n+1]=a[1];               
			for (int i=1;i<=n;i++) if (intersectSeg(l,Line(a[i],a[i+1]-a[i]),P)) x++;
			return x;
		}
	};
	bool cmpLine(const Line &la,const Line &lb){return dcmp(atan2(la.dir.y,la.dir.x),atan2(lb.dir.y,lb.dir.x))<0;}
	bool onLeft(const Point &P,const Line &l){
		return dcmp(det(l.dir,P-l.A))>0;
	}
	int Flag=1;
	void HalfplaneIntersect(Line l[],int n,Polygon &a){
		static Point P[PolygonN];
		static Line Q[PolygonN];
		sort(l+1,l+n+1,cmpLine);
		Q[1]=l[1];int p1=1,p2=1;
		for (int i=2;i<=n;i++){
			while (p1<p2&&!onLeft(P[p2-1],l[i])) p2--;
			while (p1<p2&&!onLeft(P[p1],l[i])) p1++;
			Q[++p2]=l[i];
			if (dcmp(det(Q[p2].dir,Q[p2-1].dir))==0){
				if (onLeft(l[i].A,Q[p2-1])) Q[p2-1]=l[i];
				p2--;
			}	
			if (p1<p2) intersectLine(Q[p2],Q[p2-1],P[p2-1]);
		}
		while (p1<p2&&!onLeft(P[p2-1],Q[p1])) p2--;
		if (p1<p2) intersectLine(Q[p2],Q[p1],P[p2]);
		a.n=0;
		if (p2-p1<=1) return;
		for (int i=p1;i<=p2;i++) a.a[++a.n]=P[i];
	}	
};
using namespace Geometry;

int B,C,R,Q;
int tot[N],dis[N][N];
double Minl,Minr,Maxl,Maxr;
Line l[N][N];
Point city[N],bts[N];
Polygon poly[N];

void getVoronoi(){
	for (int i=1;i<=B;i++){
		for (int j=1;j<=B;j++) if (j!=i) l[i][++tot[i]]=midLine(bts[i],bts[j]);
		l[i][++tot[i]]=Line(Point(Minl,Maxr),Point(-10000,0));
		l[i][++tot[i]]=Line(Point(Minl,Maxr),Point(0,-10000));
		l[i][++tot[i]]=Line(Point(Maxl,Minr),Point(0,10000));
		l[i][++tot[i]]=Line(Point(Maxl,Minr),Point(10000,0));
		HalfplaneIntersect(l[i],tot[i],poly[i]);
	}
}

int totCut(const Line &l){
	int x=0;
	for (int i=1;i<=B;i++) x+=poly[i].intersect(l);
	return x/2;
}

void Floyd(){
	for (int i=1;i<=C;i++) dis[i][i]=0;
	for (int k=1;k<=C;k++)
		for (int i=1;i<=C;i++) if (i!=k)
			for (int j=1;j<=C;j++) if (j!=i&&j!=k)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}

void init(){
	memset(dis,0x2f,sizeof(dis));
	memset(tot,0,sizeof(tot));
	Maxl=Maxr=-inf;
	Minl=Minr=inf;
}

int main(){
	freopen("gsm.in","r",stdin);
	freopen("gsm.out","w",stdout);
	int cas=0;
	while (scanf("%d%d%d%d",&B,&C,&R,&Q)!=EOF&&(B||C||R||Q)){
		cas++;
		printf("Case %d:\n",cas);
		init();
		for (int i=1;i<=B;i++){
			bts[i].read();
			Maxl=max(Maxl,bts[i].x);Minl=min(Minl,bts[i].x);
			Maxr=max(Maxr,bts[i].y);Minr=min(Minr,bts[i].y);
		}
		for (int i=1;i<=C;i++){
			city[i].read();
			Maxl=max(Maxl,city[i].x);Minl=min(Minl,city[i].x);
			Maxr=max(Maxr,city[i].y);Minr=min(Minr,city[i].y);
		}
		Maxl+=100;Maxr+=100;Minl-=100;Minr-=100;
		getVoronoi();
		for (int i=1;i<=R;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			if (a!=b){
				dis[a][b]=dis[b][a]=totCut(Line(city[a],city[b]-city[a]));
			}
		}			
		Floyd(); 
		for (int i=1;i<=Q;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			if (dis[a][b]==inf) printf("Impossible\n");
			else printf("%d\n",dis[a][b]);
		}
	}
	return 0;
}
