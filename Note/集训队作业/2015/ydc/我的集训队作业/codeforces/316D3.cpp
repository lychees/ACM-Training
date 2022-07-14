#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define mod 1000000007
#define maxn 1000010
using namespace std;
typedef long long LL;
int n,fact[maxn],invfact[maxn];
int s1,s2;
int Power(int p,int n)
{
	int ans=1;
	for(;n;n>>=1,p=(LL)p*p%mod)
		if(n&1)
			ans=(LL)ans*p%mod;
	return ans;
}
int inv(int p)
{
	return Power(p,mod-2);
}
int C(int n,int m)
{
	return (LL)fact[n]*invfact[m]%mod*invfact[n-m]%mod;
}
void read()
{
	scanf("%d",&n);
	fact[0]=invfact[0]=1;
	for(int i=1;i<=n+1;++i)
		fact[i]=(LL)fact[i-1]*i%mod;
	invfact[n+1]=inv(fact[n+1]);
	for(int i=n;i>=1;--i)
		invfact[i]=(LL)invfact[i+1]*(i+1)%mod;
	for(int i=1,x;i<=n;++i)
	{
		scanf("%d",&x);
		if(x==1)
			++s1;
		else
			++s2;
	}
}
int work()
{
	static int power[maxn];
	power[0]=1,power[1]=(mod+1)/2;
	for(int i=2;i<=n;++i)
		power[i]=(LL)power[i-1]*power[1]%mod;
	int ans=0;
	LL f2=(LL)fact[n]*invfact[s1]%mod;
	for(int i=0;i<=s1;++i)
		if((s1-i)%2==0)
		{
			int m=i+(s1-i)/2;
			int f1=(LL)C(s1,i)*C(s1-i,(s1-i)/2)%mod*fact[(s1-i)/2]%mod*power[(s1-i)/2]%mod;
			ans=(ans+(LL)f1*f2)%mod;
		}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
