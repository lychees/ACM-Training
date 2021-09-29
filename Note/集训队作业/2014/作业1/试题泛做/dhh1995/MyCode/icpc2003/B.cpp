#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=105,M=335;
char A[N],B[N]; int F=1,Case,n,cnt,ans,a[M],b[M],c[M],d[M],v[M]; string S,res;
int StoB(int m,char *A,int *a)
{
	rep(i,M) a[i]=0; rep(i,m) v[m-i]=A[i]-48; int n=0;
	while (m){
		a[n++]=v[1]&1;
		for (int i=m;i;--i){if (v[i]&1) v[i-1]+=10; v[i]>>=1;}
		while (m && !v[m]) --m;
	}
	return n;
}
void BtoS(int *a,string &S)
{
	int m=1; v[0]=0;
	for (int i=n-1;i>=0;--i){
		rep(j,m) v[j]*=2; v[0]+=a[i];
		rep(j,m) if (v[j]>9) v[j]-=10,++v[j+1];
		if (v[m]) ++m;
	}
	S=""; for (int i=m-1;i>=0;--i) S+=char(v[i]+48),v[i]=0;
}
void work(bool flag)
{
	rep(i,n) c[i]=a[i],d[i]=0; cnt=0;
	if (flag) c[0]^=1,c[1]^=1,d[0]=1,++cnt;
	rep(i,n) if (i && c[i-1]!=b[i-1]) c[i-1]^=1,c[i]^=1,c[i+1]^=1,d[i]=1,++cnt;
	if (c[n-1]!=b[n-1]) return; BtoS(d,res);
	if (cnt<ans || cnt==ans && (res.size()<S.size() || res.size()==S.size() && res<S)) ans=cnt,S=res;
}
int main()
{
	while (scanf("%s%s",A,B),*A!='0' || *B!='0'){
		n=max(StoB(strlen(A),A,a),StoB(strlen(B),B,b)),ans=1<<9,work(0),work(1);
		if (F) F=0; else puts("");
		printf("Case Number %d: %s\n",++Case,ans<1<<9?S.c_str():"impossible");
	}
	return 0;
}
