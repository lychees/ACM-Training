#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=1000033;
char s[5000033];
int e[maxn],p[maxn],f[maxn],n,r,c,L=1;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d\n",&n,&r,&c);
	for(int i=1;i<=n;e[i]=L-1,i++)
		while(isalpha(s[L]=getchar()))++L;
	for(int i=1,j=0;i<=n;f[i]=p[i]=j,i++)
		for(;e[i]-e[j]+i-j-1>c;j++);
	for(int i=r-1;i;i/=2)
		for(int j=n;j;--j)i&1?p[j]=f[p[j]]:0,f[j]=f[f[j]];
	int t,v=0;
	for(int i=1;i<=n;i++)
		if(i-p[i]>v)v=i-p[i],t=p[i];
	for(int m;r;r--,t=m-1,puts(""))
	{
		for(m=t;m<=n&&e[m]-e[t]+m-t-1<=c;m++);
		for(int i=t+1;i<m;i++,i<m?putchar(' '):0)
			for(int j=e[i-1]+1;j<=e[i];++j)putchar(s[j]);
	}
	return 0;
}
