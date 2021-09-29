#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=100033;
typedef unsigned int uint;
uint f[maxn],ans;
int n,tot=0;
char s[maxn];
int main()
{
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++)s[i]=getchar(),tot+=(s[i]!='?');
	if((n&1)||tot>n/2)return puts("0"),0;
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		if(s[i]!='?')continue;
		int l=i>n/2?i-n/2:1,r=i/2;
		for(int j=r;j>=l;--j)f[j]+=f[j-1];
	}
	ans=f[n/2];
	for(int i=n/2-tot;i;i--)ans*=25;
	cout<<ans<<endl;
	return 0;
}
