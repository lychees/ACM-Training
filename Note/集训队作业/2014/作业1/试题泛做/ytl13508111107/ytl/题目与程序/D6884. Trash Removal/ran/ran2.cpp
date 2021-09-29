#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define DEBUG {printf("END\n");exit(0);}
#define N 105
#define PolygonN N
using namespace std;

int minn=3,maxn=6,T=5,H=10;

int rand(int x){
	return rand()*rand()%x;
}
namespace Geometry{
	struct Point{
		int x,y;
		Point (int x=0,int y=0):x(x),y(y){};
		void print()const{
			printf("%d %d\n",x,y);
		}
		void ran(int h=H){
			x=rand(h),y=rand(h);
		}
	};
	int det(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
	int dot(const Point &A,const Point &B){return A.x*B.x+A.y*B.y;}
	Point operator + (const Point &A,const Point &B){return Point(A.x+B.x,A.y+B.y);}
	Point operator - (const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
	bool operator == (const Point &A,const Point &B){return A.x==B.x&&A.y==B.y;}

	struct Line{
		Point A,dir;
		Line (Point A=Point(0,0),Point dir=Point(0,0)):A(A),dir(dir){};
	};
	bool between(const Point &P,const Point &A,const Point &B){return dot(A-P,B-P)<=0;}//Attention:���� 
	//�߶ν���
	int dcmp(int x){
		if (x>0) return 1;
		if (x<0) return -1;
		return 0;
	}
	bool intersectSeg(const Line &la,const Line &lb,Point &P){
		Point A(la.A),A1(la.A+la.dir),
                 B(lb.A),B1(lb.A+lb.dir);
		int d1=dcmp(det(A1-A,B-A)),d2=dcmp(det(A1-A,B1-A)),d3=dcmp(det(B1-B,A-B)),d4=dcmp(det(B1-B,A1-B));
		if ((d1^d2)==-2&&(d3^d4)==-2){//���ʵ�� Attention:���!!! 
			//double s1=det(B-A,B1-A),s2=det(B-A1,B1-A1);
			return true;
		}
		if (!d1&&!d3) return false;//��������߶����غϲ��ֵ�����:������Ϊ���ཻ���մ˴�������Ӧ������ע�͵�����غϲ��ֵ�����һ���
		if (!d1&&between(B, A,A1))  {P=B; return true;}
		if (!d2&&between(B1,A,A1)) {P=B1;return true;}
		if (!d3&&between(A, B,B1))  {P=A; return true;}
		if (!d4&&between(A1,B,B1)) {P=A1;return true;}
		return false;//Attenaion!
	}//����p����ֱ��L�ϵ�ͶӰ��������

	bool cmpY(Point A,Point B){return A.y<B.y||(A.y==B.y&&A.x<B.x);}
	struct Polygon{
		int n;Point a[PolygonN];
		void convex(){
			static Point d[PolygonN];
			sort(a+1,a+n+1,cmpY);//Attention
			int p1=0;
			for (int i=1;i<=n;i++){
				while (p1>1&&det(d[p1]-d[p1-1],a[i]-d[p1])<0) p1--;
				d[++p1]=a[i];
			}
			int p2=p1;
			for (int i=n-1;i>=1;i--){//Attention
				while (p2>p1&&det(d[p2]-d[p2-1],a[i]-d[p2])<0) p2--;
				d[++p2]=a[i];
			}
			n=p2-1;
			for (int i=1;i<=n;i++) a[i]=d[i];
		}
		bool insert(int k,const Point A){
			a[n+1]=a[1];Point P;
			//a[k].print();a[k+1].print();A.print();printf("\n");
			for (int i=1;i<=n;i++){
				if ((i!=k&&i+1!=k)&&intersectSeg(Line(a[i],a[i+1]-a[i]),Line(a[k],A-a[k]),P))  return false;
				if ((i!=k&&i!=k+1)&&intersectSeg(Line(a[i],a[i+1]-a[i]),Line(a[k+1],A-a[k+1]),P)) return false;
			}
			//printf("!\n");
			for (int i=n;i>=k+1;i--) a[i+1]=a[i];
			a[k+1]=A;
			n++;
			return true;
		}
	};
}
using namespace Geometry;

Polygon b;
int n,rank[N];
Point a[N];
bool add(){
	for (int i=1;i<=n;i++) b.a[i]=a[i];b.n=n;
	b.convex();
	int e=n-b.n;
	for (int i=1;i<=e;i++){
		//for (int i=1;i<=b.n;i++) b.a[i].print();printf("\n");//
		Point A;A.ran();
		int t=0;
		for (int j=1;j<=b.n;j++) if (A==b.a[j]) {t=1;break;}
		if (t) continue;
		for (int j=1;j<=b.n;j++) rank[j]=j;
		for (int j=1;j<=b.n;j++) swap(rank[rand(b.n)+1],rank[rand(b.n)+1]);
		for (int j=1;j<=b.n;j++) if (b.insert(rank[j],A)) break;
	}
	return true;
}
bool havesame(){
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) if (i!=j&&a[i]==a[j]) return true;
	return false;
}
void output(){
	printf("%d\n",b.n);
	for (int i=1;i<=b.n;i++) b.a[i].print();
	//printf("\n");
	//for (int i=1;i<=n;i++) a[i].print(); 
}
void work(){
	n=minn+rand(maxn-minn+1);
	while(1){
		while (1){
			for (int i=1;i<=n;i++) a[i].ran(H+1);
			if (!havesame()) break;		
		}
		if (add()) break;
	}
	output();
}
int main(){
	srand(time(NULL));
	freopen("trash.in","w",stdout);
	for (int i=1;i<=T;i++) work();
	printf("0\n");
	return 0;
}
