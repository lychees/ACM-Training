#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
int n,x;
int Power(int p,int n,int mod)
{
	int ans=1;
	for(;n;n>>=1,p=(LL)p*p%mod)
		if(n&1)
			ans=(LL)ans*p%mod;
	return ans;
}
bool isRoot(int p,int n)
{
	for(int i=2;i*i<=n-1;++i)
		if((n-1)%i==0&&(Power(p,(n-1)/i,n)==1||Power(p,i,n)==1))
			return false;
	return true;
}
bool isPrime(int n)
{
	for(int i=2;i*i<=n;++i)
		if(n%i==0)
			return false;
	return true;
}
int work()
{
	if(n==1)
		return x==2?-1:x-1;
	if(!isPrime(++n))
		return -1;
	while(--x>1)
		if(x%n&&isRoot(x%n,n))
			return x;
	return -1;
}
int main()
{
	cin>>n>>x;
	printf("%d\n",work());
	return 0;
}
