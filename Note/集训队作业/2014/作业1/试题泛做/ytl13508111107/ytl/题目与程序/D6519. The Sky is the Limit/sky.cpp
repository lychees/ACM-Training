#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 105
using namespace std;

namespace Geometry{
	double EPS=1e-4;
	int dcmp(const double a,double b=0){
		if (a-b>EPS) return 1;
		if (b-a>EPS) return -1;
		return 0;
	}
	inline double sqr(double a){return a*a;}
	struct Point{
		double x,y;
		Point(double x=0,double y=0):x(x),y(y){};
		double len(){return sqrt(sqr(x)+sqr(y));}
		double dis(const Point &A)const{return sqrt(sqr(A.x-x)+sqr(A.y-y));}
		void print(){
			printf("%.2lf %.2lf\n",x,y);
		}
	};
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	Point operator * (const double &k,const Point &A){return Point(A.x*k,A.y*k);}
	Point operator * (const Point &A,const double &k){return Point(A.x*k,A.y*k);}
	Point operator / (const Point &A,const double &k){if (!k) return Point(0,0);return Point(A.x/k,A.y/k);}
	bool operator == (const Point &A,const Point &B){return dcmp(A.x,B.x)==0&&dcmp(A.y,B.y)==0;}
	double det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	double dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}//Atention not '-'!
	
	struct Line{
		Point A,dir;
		Line(Point A=Point(0,0),Point dir=Point(0,0)):A(A),dir(dir){};
	};
	bool between(const Point &P,const Point &A,const Point &B){return dcmp(dot(A-P,B-P))<=0;}//Attention:���� 
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
		return false;//Attenaion!
	}
}
using namespace Geometry;

double p[N*N*4+N*3],X[N],B[N],H[N],MaxH;
Point a[N],b[N],c[N];
int n,po,tot;
Line l[N*2],la[N*N*4+N*3];

void getRange(){
	tot=0;po=0;
	for (int i=1;i<=n;i++){
		a[i]=Point(X[i]-B[i],0);
		b[i]=Point(X[i]+B[i],0);
		c[i]=Point(X[i],H[i]);
		l[++tot]=Line(c[i],a[i]-c[i]);
		l[++tot]=Line(c[i],b[i]-c[i]);	
	}
	for (int i=1;i<=n;i++) p[++po]=a[i].x,p[++po]=b[i].x,p[++po]=c[i].x;
	Point P;
	for (int i=1;i<=tot;i++)
		for (int j=i+1;j<=tot;j++)
			if (intersectSeg(l[i],l[j],P)) p[++po]=P.x;
	
	sort(p+1,p+po+1);
	int pp=po;po=0;
	for (int i=1;i<=pp;i++) if (i==1||dcmp(p[i],p[i-1])!=0) p[++po]=p[i];
	
	for (int i=1;i<=po;i++) la[i]=Line(Point(p[i],0),Point(0,MaxH+100));
}
int main(){
	freopen("sky.in","r",stdin);
	freopen("sky.out","w",stdout);
	while (scanf("%d",&n)!=EOF&&n){
		for (int i=1;i<=n;i++){
			scanf("%lf%lf%lf",&X[i],&H[i],&B[i]);
			B[i]/=2.0;MaxH=max(MaxH,H[i]);
		}
		getRange();
		double ans=0;
		for (int i=2;i<=po;i++){
			Point P1,P2;
			double h=0,len=0;
			for (int j=1;j<=tot;j++) 
				if (intersectSeg(l[j],la[i-1],P1)&&intersectSeg(l[j],la[i],P2)){
					Point P=(P1+P2)/2;
					if (P.y>h){
						h=P.y;
						len=P1.dis(P2);
					}
				}
			ans+=len;
		}
		printf("%.lf\n",ans);
	}
	return 0;
}
