#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int n,x;
LL Pow(LL a,int b,int p)
{
	LL res=1;
	for(a%=p;b;b/=2,a=a*a%p)
		if(b&1)res=res*a%p;
	return res;
}
int main()
{
	//freopen("tmp.in","r",stdin);
	//freopen("tmp.out","w",stdout);
	scanf("%d%d",&n,&x);
	if(n==1)return printf("%d\n",x>2?x-1:-1),0;
	for(int i=2;i*i<n;i++)
		if((n+1)%i==0)return puts("-1"),0;
	for(int b=x-1;b>1;b--)
	{
		if(b%(n+1)==0)continue;
		bool flag=1;
		for(int i=2;i*i<=n&&flag;i++)
			if(n%i==0)flag&=Pow(b,i,n+1)!=1&&Pow(b,n/i,n+1)!=1;
		if(flag)return printf("%d\n",b),0;
	}
	puts("-1");
	return 0;
}
