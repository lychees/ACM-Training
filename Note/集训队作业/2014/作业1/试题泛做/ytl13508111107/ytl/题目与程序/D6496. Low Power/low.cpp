#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 1000005
using namespace std;

int n,k,t,v[N];

bool can(int x){
	int j=n+1;
	for (int i=1;i<=t;i++){
		int t=1;
		for (j=min(j-2,n-2*i*k+1);j>=1;j--)
			if (v[j+1]-v[j]<=x){
				t=0;
				break;
			}
		if (t) return false;
	}	
	return true;
}
int main(){
	freopen("low.in","r",stdin);
	freopen("low.out","w",stdout);
	scanf("%d%d",&t,&k);
	n=t*2*k;
	for (int i=1;i<=n;i++) scanf("%d",&v[i]);	
	sort(v+1,v+n+1);
	int l=v[2]-v[1],r=v[n]-v[1],mid;
	while (l<r){
		mid=(l+r)>>1;
		if (can(mid)) r=mid;else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
