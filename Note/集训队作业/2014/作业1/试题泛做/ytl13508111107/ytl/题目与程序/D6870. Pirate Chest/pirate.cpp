//By ytl 2013-11-19
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 505
using namespace std;
typedef long long LL;

LL ans,SS;
int n,m,A,B,pp;
int h[N],v[N][N],tot[N];

struct data{
	int w,h;
	data(int w=0,int h=0):w(w),h(h){};
}stack[N];

void updata(LL S,LL x,int a,int b,int limit){
	LL h=(x*SS-1)/(SS-S);
	ans=max(ans,h*LL(S));
}
void ask(int wide,int limit,int a,int b){
	pp=0;
	for (int i=1;i<=m+1;i++){
		int sum=0;
		while (pp&&stack[pp].h>h[i]){
			sum+=stack[pp].w;
			updata(wide*min(sum,limit),stack[pp].h,a,b,limit);
			pp--;	
		}
		stack[++pp]=data(sum+1,h[i]);
	}	
}

int main(){
	freopen("pirate.in","r",stdin);
	freopen("pirate.out","w",stdout);
	SS=n*m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&v[i][j]);
	if (A>B) swap(A,B);
	for (int i=1;i<=n;i++){
		for (int k=1;k<=m;k++) h[k]=v[i][k];
			ask(1,B,i,i);
		for (int j=i+1;j<=min(n,A+i-1);j++){
			for (int k=1;k<=m;k++) h[k]=min(h[k],v[j][k]);
			ask(j-i+1,B,i,j);
		}
		if (i+A-1<n){
			for (int j=i+A;j<=min(n,i+B-1);j++){
				for (int k=1;k<=m;k++) h[k]=min(h[k],v[j][k]);
				ask(j-i+1,A,i,j);
			}
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
