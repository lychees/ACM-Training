#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m,a[44444],prev[44444],T,s[44444],f[44444];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)f[i]=i;
	for(T=0;T*T<=n;T++);
	T--;
	for(int i=1;i<=n;i++)
	{
		int j;
		for(j=0;j<=T&&s[j]-1!=prev[a[i]];j++);
		j--; prev[a[i]]=i;
		for(;j>=0;j--)s[j+1]=s[j];
		s[0]=i+1;
		for(j=1;j*j<=f[i];j++)
			f[i]=min(f[i],f[s[j]-(s[j]?1:0)]+j*j);
	}
	printf("%d\n",f[n]);
	return 0;
}
