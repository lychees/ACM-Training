#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
LL n,A,B;
double C0(LL n,LL m)
{
	double ans=0;
	for(int i=1;i<=m;++i)
		ans+=log(n-i+1)-log(i);
	return ans;
}
LL C(LL n,LL m)
{
	LL ans=1;
	for(int i=1;i<=m;++i)
		ans=ans*(n-i+1)/i;
	return ans;
}
bool check(LL T)
{
	LL c=0;
	double N=log(n);
	for(LL j=0;j*B<=T;++j)
	{
		LL K1=(T-B-j*B)/A,K2=(T-j*B)/A;
		if(C0(K2+j,j+1)>N+1)
			return true;
		if(T-B<j*B)
			c+=C(K2+j+1,j+1);
		else
			c+=C(K2+j+1,j+1)-C(K1+j+1,j+1);
		if(c>=n)
			return true;
	}
	return false;
}
LL binary(LL l,LL r)
{
	while(l<r)
	{
		LL mid=(l+r)>>1;
		!check(mid)?l=mid+1:r=mid;
	}
	return l;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	cin>>T;
	for(int i=1;i<=T;++i)
	{
		cin>>n>>A>>B;
		printf("Case #%d: %I64d\n",i,binary(0,B*55+A));
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
