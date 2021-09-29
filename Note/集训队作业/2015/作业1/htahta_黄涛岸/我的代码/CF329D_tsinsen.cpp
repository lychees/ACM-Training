#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n,k;
char a[303][303];
int main()
{
	scanf("%d",&k);n=2*k;
	if(n==2)return puts(">.\n..\n1 1"),0;
	for(int i=1,j;i<n;i++)
		if(i&1)
		{
			for(j=1;j<k;j++)a[i][j+1]='>';
			for(j=1;j<k;j++)a[i][n-j]=j&1?'.':'>';
			a[i][n]='v';
		}else
		{
			for(j=1;j<k;j++)a[i][n-j+1]='<';
			for(j=1;j<k;j++)a[i][2+j]=j&1?'.':'<';
			a[i][2]='v';
		}
	a[1][1]='>';
	for(int i=k+1;i<=n;i++)a[i][1]='^';
	for(int i=1;i<k;i++)a[i+1][1]=i&1?'.':'^';
	for(int i=k+1;i<=n;i++)a[n][i]='<';
	for(int i=1;i<k;i++)a[n][i+1]=i&1?'.':'<';
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)putchar(a[i][j]);
	puts("1 1");
	return 0;
}

