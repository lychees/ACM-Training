#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
const int maxn=1003;
int n,a[maxn][maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d",&n);
	if(n==4)return puts("-1"),0;
	for(int i=1;i<=n;i++)a[i][i%n+1]=1;
	for(int i=1;i<=n;i++)
		for(int j=i+2;j<=n-(i==1);j++)
			if((j-i)&1)a[j][i]=1;else a[i][j]=1;
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)printf("%d ",a[i][j]);
	return 0;
}


