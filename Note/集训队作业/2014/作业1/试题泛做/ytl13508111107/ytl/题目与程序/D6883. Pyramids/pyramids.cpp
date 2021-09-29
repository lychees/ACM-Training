#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int n,tot,sum[400],f[1000005],tol[1000005];
struct data{
	int h,a,b;
	data(int h=0,int a=0,int b=0):h(h),a(a),b(b){};
}w[400];
bool cmp(const data &a,const data &b){
	return a.h<b.h;
}
int main(){
	freopen("pyramids.in","r",stdin);
	freopen("pyramids.out","w",stdout);
	scanf("%d",&n);
	sum[1]=1;sum[2]=5;
	for (int i=2;sum[i]<=n;i++){
		w[++tot]=data(sum[i],i,'H');
		sum[i+1]=sum[i]+(i+1)*(i+1);
	}
	sum[1]=1;sum[2]=4;sum[3]=10;
	for (int i=3;sum[i]<=n;i++){
		w[++tot]=data(sum[i],i,'L');
		sum[i+1]=sum[i-1]+(i+1)*(i+1);
	}
	sort(w+1,w+tot+1,cmp);
	f[0]=-1;
	for (int i=1;i<=n;i++){
		tol[i]=400;
		for (int j=tot;j>=1;j--) 
			if (i-w[j].h>=0&&f[i-w[j].h]&&j>f[i-w[j].h]){
				if (tol[i-w[j].h]+1<tol[i]){
					f[i]=j;
					tol[i]=tol[i-w[j].h]+1;
				}
			}
	}
	if (f[n]){
		for (int i=n;i;i=i-w[f[i]].h) printf("%d%c ",w[f[i]].a,w[f[i]].b);
		printf("\n");
	}else printf("impossible\n");
	return 0;
}
