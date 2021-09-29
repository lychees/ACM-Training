//By ytl 2013-11-26
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 55
using namespace std;

double ans,w[N],sum;
int n,m,tot,use[N];
struct data{
	int a,b;double c;
	data(int a=0,int b=0,double c=0):a(a),b(b),c(c){};
}edge[N*N];
bool cmp(const data &a,const data &b){
	return a.c<b.c;
}

inline double sqr(double a){return a*a;}
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){};
	double dis(const Point &A)const{return sqrt(sqr(A.x-x)+sqr(A.y-y));}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
}p[N];

namespace Graph{
	int head[N],gt=1;
	struct Rec{int go,nex;double c;}eg[N*N];
	void build(int a,int b,double c){
		eg[++gt]=(Rec){b,head[a],c};
		head[a]=gt;
	}
	void initGraph(){
		memset(head,0,sizeof(head));
		gt=1;
	}
}
using namespace Graph;

namespace UFS{
	int ff[N];
	int find(int a){
		if (ff[a]==a) return a;
		ff[a]=find(ff[a]);
		return ff[a];
	}
}
using namespace UFS;

void init(){
	tot=0;ans=0;sum=0;
	for (int i=1;i<=n;i++) use[i]=0;
	initGraph();
}
void kruscal(){
	int now=0;
	for (int i=1;i<=n;i++) ff[i]=i;
	sort(edge+1,edge+tot+1,cmp);
	for (int i=1;i<=tot;i++){
		int a=edge[i].a,b=edge[i].b;double c=edge[i].c;
		if (find(a)!=find(b)){
			ff[find(a)]=find(b);
			build(a,b,c);
			build(b,a,c);
			now++;
			if (now==n-1) break;
		}
	}
}
void dfs(int p,double x){
	ans+=x*w[p];
	use[p]=1;
	for (int i=head[p];i;i=eg[i].nex){
		if (!use[eg[i].go]) dfs(eg[i].go,max(x,eg[i].c));
	}
	
}
int main(){
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	int cas=0;
	while (scanf("%d",&n)!=EOF&&n){
		init();
		for (int i=1;i<=n;i++){
			p[i].read();
			scanf("%lf",&w[i]);
			sum+=w[i];
		}
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				edge[++tot]=data(i,j,p[i].dis(p[j]));
		kruscal();
		dfs(1,0);
		printf("Island Group: %d Average %.2lf\n\n",++cas,ans/sum);
	}
	return 0;
}
