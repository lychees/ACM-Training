#include <stdio.h>
#include <stdlib.h>
using namespace std;

int p,K,i,j,k;
long long ans;

struct Lagrange_polynomial_interpolation
{
	#define pol_m 200005
	
	int m,p,fac[pol_m],fac_inv[pol_m],fac_l[pol_m],fac_r[pol_m],f[pol_m];
	
	int Power(int a,int b)
	{
		int ans=1;
		for(;b;b>>=1,a=(long long)a*a%p)if(b&1)ans=(long long)ans*a%p;
		return ans;
	}
	void prepare()
	{
		int i;
		m+=K;
		for(fac[0]=i=1;i<=m;++i)fac[i]=(long long)fac[i-1]*i%p;
		for(fac_inv[m]=Power(fac[m],p-2),i=m;i>=1;--i)fac_inv[i-1]=(long long)fac_inv[i]*i%p;
		m-=K;
		for(i=1;i<=m;++i)f[i]=(f[i-1]+(long long)fac[i+K-2]*fac_inv[i])%p;
	}
	int calc(int n)
	{
		n%=p;
		if(n<=m)return f[n];
		int i,ans=0,tmp;
		for(fac_l[0]=i=1;i<=m;++i)fac_l[i]=(long long)fac_l[i-1]*(n-i)%p;
		for(fac_r[m+1]=1,i=m;i>=1;--i)fac_r[i]=(long long)fac_r[i+1]*(n-i)%p;
		for(i=1;i<=m;++i)
		{
			tmp=(long long)f[i]*fac_l[i-1]%p*fac_r[i+1]%p*fac_inv[i-1]%p;
			if((m-i)&1)tmp=(long long)tmp*(p-fac_inv[m-i])%p;
			else tmp=(long long)tmp*fac_inv[m-i]%p;
			ans+=tmp;if(ans>=p)ans-=p;
		}
		return ans;
	}
	
	#undef pol_m
}a;

int D(int p)
{
	a.m=100000;a.p=p;
	a.prepare();
	return p-(long long)a.calc(p-1)*a.fac_inv[K-1]%p;
}

bool isprime(int x)
{
	int i;
	for(i=2;i*i<=x;++i)
	if(x%i==0)return false;
	return true;
}

int main()
{
	p=1000000000;K=100000;
	for(i=0;i<100000;++i)
	if(isprime(p+i))
	ans+=D(p+i);
	printf("%I64d\n",ans);
}
