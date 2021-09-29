#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 25
using namespace std;

const double inf=1e22;

int n,use[N];
double dis[N],w[N][N],tot;

inline double sqr(double a){return a*a;}
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){};
	double dis(const Point &A){
		return sqrt(sqr(A.x-x)+sqr(A.y-y));
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
}p[N];

void dijk(){
	int u=-1;double x=inf;
	for (int i=1;i<=n;i++) if (!use[i]&&dis[i]<x){
		x=dis[i];
		u=i;
	}
	if (u==-1) return;
	use[u]=1;
	for (int v=1;v<=n;v++) if (!use[v]){
		double x=w[u][v];
		if (2*x>tot) continue;
		if (tot-2*x>=dis[u]){
			dis[v]=min(dis[v],x+dis[u]);
			continue;
		}
		if (tot-3*x>0){
			double times=ceil((dis[u]-tot+2*x)/(tot-3*x));
			dis[v]=min(dis[v],(times*2+1)*x+dis[u]);
		}
	}
}


int main(){
	freopen("desert.in","r",stdin);
	freopen("desert.out","w",stdout);
	scanf("%d%lf",&n,&tot);
	for (int i=1;i<=n;i++) p[i].read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			w[i][j]=p[i].dis(p[j]);
	for (int i=1;i<=n;i++) dis[i]=inf;
	dis[n]=0;
	for (int i=1;i<=n-1;i++) dijk();
	dis[1]=max(1.0,ceil(dis[1]));
	if (dis[1]==1){
		printf("1 unit of food\n");
		return 0;
	}
	if (dis[1]==inf||dis[1]>1e6||dis[1]==0) printf("Impossible\n");else printf("%.lf units of food\n",dis[1]);
	return 0;
}
