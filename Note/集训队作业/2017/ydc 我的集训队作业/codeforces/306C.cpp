#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 4010
#define mod 1000000009 
using namespace std;
typedef long long LL;
int fact[maxn],invfact[maxn];
int Power(int p,int n)
{
	int ans=1;
	for(;n;n>>=1,p=(LL)p*p%mod)
		if(n&1)
			ans=(LL)ans*p%mod;
	return ans;
}
int C(int n,int m)
{
	if(n<m)
		return 0;
	return (LL)fact[n]*invfact[m]%mod*invfact[n-m]%mod;
}
int n,w,b;
int work()
{
	fact[0]=1,invfact[0]=1;
	int N=max(max(w,b),n);
	for(int i=1;i<=N;++i)
		fact[i]=(LL)fact[i-1]*i%mod,invfact[i]=Power(fact[i],mod-2);
	int ans=0;
	for(int i=2;i<n;++i)
		for(int j=i;j<n;++j)
			ans=(ans+(LL)C(b-1,j-i)*C(w-1,n-(j-i+1)-1))%mod;
	return (LL)ans*fact[w]%mod*fact[b]%mod;
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d %d",&n,&w,&b);
	printf("%d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
