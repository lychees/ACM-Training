#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;
int n;int k=0,mm;
int sz=0;
int a[100005];
int pr[1100005],ptot=0;
int mi[10000005]={0};
void sieve(int n){
	for (int i=2;i<=n;i++){
		if(!mi[i]){
			pr[++ptot]=i;mi[i]=i;
		}
		for (int j=1;j<=ptot && pr[j]*i<=n;j++){
			mi[pr[j]*i]=pr[j];
			if(i%pr[j]==0)break;
		}
	}
}
int tms[10000005]={0};
int mt[10000005]={0};
int has[10000005]={0};
int qu[1000],q;
int cmp(int i,int j){
	return has[i]<has[j];
}
void check(int x){
	int n0=0;
	int mat=0;
	for (int i=1;i<=n;i++){
		int d=abs(x-a[i]);
		if(d==0){n0++;continue;}
		while(d!=1){
			int p=mi[d],cnt=0;
			while(mi[d]==p)d/=p,cnt++;
			if(!tms[p]){
				tms[p]=1;mt[p]=cnt;has[p]=i;
			}else{
				tms[p]++;mt[p]=min(mt[p],cnt);has[p]=has[p]*314159+i;
			}
			if(tms[p]>mat)mat=tms[p];
		}
	}
	q=0;
	for (int i=1;i<=n;i++){
		int d=abs(x-a[i]);
		if(d==0)continue;
		while(d!=1){
			int p=mi[d];while(mi[d]==p)d/=p;
			int cn=tms[p];tms[p]=0;
			if(cn==mat)	qu[q++]=p;
		}
	}	
	if(mat+n0<k)return;	
	sort(qu,qu+q,cmp);
	for (int i=0,cu=1;i<q;i++){
		int p=qu[i];
		for (int j=1;j<=mt[p];j++)cu*=p;
		if(i==q-1 || has[qu[i]]!=has[qu[i+1]]){
			if(mat+n0>k){
				k=mat+n0;mm=cu;
			}else if(mat+n0==k && cu>mm){
				mm=cu;
			}
			cu=1;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]),sz=max(sz,a[i]);
	sieve(sz);
	int tms=10;
	while(tms--){
		int x=a[rand()%n+1];
		check(x);		
	}
	printf("%d %d\n",k,mm);
	return 0;
}
	