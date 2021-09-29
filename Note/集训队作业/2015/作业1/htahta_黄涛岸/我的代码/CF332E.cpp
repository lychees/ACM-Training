#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
char a[1002003],b[2003];
int s[2003],ans[2003],k,n,m,T;
bool have=0;
inline bool judge()
{
	for(int i=1;i<=k;i++)
		if(s[i]<ans[i])return 1;
		else if(s[i]>ans[i])return 0;
	return 0;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=m=1;
	while((a[n]=getchar())!='\n')n++;
	while((b[m]=getchar())!='\n')m++;
	a[n]=b[m]='\0',n--,m--;
	scanf("%d",&k);T=n/k;
	for(int i=1;i<=m;i++)
	{
		if(!(i*T<=m&&(i*(T+1)>=m)))continue;
		int c=i;
		for(int j=1;j<=k;j++)s[j]=0;
		for(int j=k;j&&c;j--)
		{
			bool f=1;
			for(int x=0;f&&x<=T;x++)
				if((x*k+j<=n||x*i+c<=m)&&a[x*k+j]!=b[x*i+c])f=0;
			if(f)c--,s[j]=1;
		}
		if(!c&&(!have||judge()))have=1,memcpy(ans+1,s+1,k*4);
	}
	if(!have)k=1;
	for(int i=1;i<=k;i++)putchar('0'+ans[i]);
	puts("");
	return 0;
}
