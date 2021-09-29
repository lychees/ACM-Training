#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn=30003,mod=1000000009,seed=13313;
int n;
char s[maxn];
LL Pow[maxn],h1[maxn],h2[maxn];
inline LL get1(int l,int r)
{
	return ((h1[r]-h1[l-1]*Pow[r-l+1])%mod+mod)%mod;
}
inline LL get2(int l,int r)
{
	return ((h2[l]-h2[r+1]*Pow[r-l+1])%mod+mod)%mod;
}
inline bool judge(int x,int y)
{
	int l=0,r=y-x,mid;
	while(l<r)
	{
		mid=(l+r+1)/2;
		if(get1(x,x+mid-1)==get2(y-mid+1,y))l=mid;else r=mid-1;
	}
	return s[x+l]<s[y-l];
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d",&n);Pow[0]=1;
	for(int i=1;i<=n;i++)
	{
		while(!isalpha(s[i]=getchar()));
		Pow[i]=Pow[i-1]*seed%mod;
		h1[i]=(h1[i-1]*seed+s[i])%mod;
	}
	for(int i=n;i;i--)h2[i]=(h2[i+1]*seed+s[i])%mod;
	for(int i=1,j=n,c=1;i<=j;c++)
	{
		putchar(judge(i,j)?s[i++]:s[j--]);
		if(c%80==0)puts("");
	}
	return 0;
}
