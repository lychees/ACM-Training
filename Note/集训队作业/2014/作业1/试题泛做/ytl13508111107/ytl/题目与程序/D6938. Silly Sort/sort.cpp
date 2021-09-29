//By ytl 2013-11-14
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 1005
using namespace std;

const int INF=0x7fffffff/3;

int n,use[N];
struct data{int x,a,b;}v[N];

bool cmp(const data &a,const data &b){
	return a.x<b.x;
}
int main(){
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	int cas=0;
	while (scanf("%d",&n)!=EOF&&n){
		int minAll=INF,ans=0;
		for (int i=1;i<=n;i++) use[i]=0;
		for (int i=1;i<=n;i++){
			scanf("%d",&v[i].x);
			v[i].b=i;
			minAll=min(minAll,v[i].x);
		}
		sort(v+1,v+n+1,cmp);
		for (int i=1;i<=n;i++) if (!use[i]){
			int k=i,sum=0,len=0,rec=INF;
			while (!use[k]){
				use[k]=1;
				sum+=v[k].x;
				len++;
				rec=min(rec,v[i].x);
				k=v[k].b;
			}
			ans+=min((len-1)*rec+sum-rec,minAll+rec+len*minAll+sum);
		}
		printf("Case %d: %d\n\n",++cas,ans);
	}
	return 0;
}
