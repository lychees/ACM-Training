#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
typedef __int64 lld;
#define mod (10007*24)
lld pow_mod(lld a,lld b)
{
	lld ret=1;
	a%=mod;
	while(b)
	{
		if(b&1)
			ret=(ret*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ret;
}
int main()
{
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		lld k;
		cin >> k;
		lld ans=pow_mod(k,74)+pow_mod(k,38)*9+pow_mod(k,26)*8+pow_mod(k,20)*6;
		ans%=mod;
		ans/=24;
		printf("Case %d: ",cc);
		cout << ans << endl;
	}
	return 0;
}
