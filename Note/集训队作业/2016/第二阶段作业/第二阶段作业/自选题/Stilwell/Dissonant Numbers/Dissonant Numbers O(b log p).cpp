#include <stdio.h>
#include <stdlib.h>
using namespace std;

int p,K,i,j,k;
long long ans;

bool isprime(int x)
{
	int i;
	for(i=2;i*i<=x;++i)
	if(x%i==0)return false;
	return true;
}

int Power(int a,int b,int p)
{
	int ans=1;
	for(;b;b>>=1,a=(long long)a*a%p)if(b&1)ans=(long long)ans*a%p;
	return ans;
}

int main()
{
	p=1000000000;K=100000;
	for(i=0;i<100000;++i)
	if(isprime(p+i))
	ans+=Power(K-1,p+i-2,p+i);
	printf("%I64d\n",ans);
}
