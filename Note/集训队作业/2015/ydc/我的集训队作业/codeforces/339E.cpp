#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
using namespace std;
int n,a[maxn];
void read()
{
	scanf("%d",&n);
	a[n+1]=n+1;
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
}
bool check()
{
	for(int i=1;i<=n;++i)
		if(a[i]!=i)
			return false;
	return true;
}
void DFS(int p)
{
	static int l[5],r[5];
	if(check())
	{
		printf("%d\n",p-1);
		for(int i=p-1;i>=1;--i)
			printf("%d %d\n",l[i],r[i]);
		exit(0);
	}
	if(p>3)
		return ;
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(abs(a[i]-a[j+1])==1||abs(a[j]-a[i-1])==1)
			{
				l[p]=i,r[p]=j;
				reverse(a+i,a+j+1);
				DFS(p+1);
				reverse(a+i,a+j+1);
			}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("1.out","w",stdout);
	read();
	DFS(1);
	return 0;
}
