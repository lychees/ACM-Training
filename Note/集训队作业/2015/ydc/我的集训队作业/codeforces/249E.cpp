#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL P=10000000000LL;
LL mul(LL a,LL b,LL mod)
{
	a%=mod,b%=mod;
	return (a*b-(LL)(((long double)a*b+0.5)/mod)*mod+mod)%mod;
}
LL sum3(LL n,LL mod)
{
	LL a=n,b=n+1,c=2*n+1;
	a&1?b/=2:a/=2;
	if(a%3==0)
		a/=3;
	else if(b%3==0)
		b/=3;
	else
		c/=3;
	return mul(mul(a,b,mod),c,mod);
}
LL sum2(LL n,LL mod)
{
	LL a=n,b=n+1;
	a&1?b/=2:a/=2;
	return mul(a,b,mod);
}
LL calc(int n,int m,LL mod)
{
	if(n==0||m==0)
		return 0;
	LL sum=sum2((LL)min(n,m)*min(n,m),mod);
	if(n<m)
		return (sum+mul(sum2(n,mod),m-n,mod)+mul(sum3(m-1,mod)-sum3(n-1,mod)+mod,n,mod))%mod;
	return (sum-mul(sum2(m-1,mod),n-m,mod)+mul(sum3(n,mod)-sum3(m,mod)+mod,m,mod)+mod)%mod;
}
LL work(int a,int b,int c,int d,LL mod)
{
	return (calc(c,d,mod)-calc(a-1,d,mod)-calc(c,b-1,mod)+calc(a-1,b-1,mod)+2*mod)%mod;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,a,b,c,d;
	for(cin>>T;T;--T)
	{
		scanf("%d %d %d %d",&a,&b,&c,&d);
		LL v1=work(a,b,c,d,P),v2=work(a,b,c,d,P-1);
		if(v1%(P-1)==v2)
			printf("%I64d\n",v1);
		else
			printf("...%010I64d\n",v1);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
