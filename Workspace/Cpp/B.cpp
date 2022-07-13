#include<bits/stdc++.h>
using namespace std;
typedef long double db;
const int N=45;
const db eps=1e-9;
int sgn(db x){return (-eps<=x&&x<=eps)?0:(x>0?1:-1);}
int n,m,t,id[N];db res[N];
db a[N][N];
int rd(){int x;cin>>x;return x;}
void pivot(int x,int y){
	swap(id[n+x],id[y]);
	db d=-a[x][y];
	for(int i=0;i<=n;i++)a[x][i]/=d;
	a[x][y]=-1./d;
	for(int i=0;i<=m;i++)if(i!=x&&sgn(a[i][y])){
		d=a[i][y],a[i][y]=0;
		for(int j=0;j<=n;j++)a[i][j]+=a[x][j]*d;
	}
}
void simplex(){
	iota(id+1,id+1+n+m,1);
	while(1){
		int u=1,v=0;
		for(int i=1;i<=m;i++)if(a[i][0]<a[u][0])u=i;
		if(sgn(a[u][0])>=0)break;
		for(int j=1;j<=n;j++)if(sgn(a[u][j])>0&&(!v||(id[j]>id[v])))v=j;
		if(!v)puts("Infeasible"),exit(0);
		pivot(u,v);
	}
	while(1){
		int u=0,v=1;db mn=1e9;
		for(int j=1;j<=n;j++)if(a[0][j]>a[0][v])v=j;
		if(sgn(a[0][v])<=0)break;
		for(int i=1;i<=m;i++)if(sgn(a[i][v])<0){
			db t=-a[i][0]/a[i][v];
			if(sgn(t-mn)<0||(sgn(t-mn)==0&&(!u||id[i]>id[u])))mn=t,u=i;
		}
		if(!u)puts("Unbounded"),exit(0);
		pivot(u,v);
	}
}
signed main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++)a[0][i]=rd();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)a[i][j]=-rd();
		a[i][0]=rd();
	}
	simplex();
	printf("%.10Lf\n",a[0][0]);
	if(t){
		for(int i=1;i<=m;i++)res[id[i+n]]=a[i][0];
		for(int i=1;i<=n;i++)printf("%.10Lf ",res[i]);
	}

}
