#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
using namespace std;
int ans[maxn][maxn],n;
void work(int n)
{
	if(n==3)
		ans[1][2]=1,ans[2][3]=1,ans[3][1]=1;
	else if(n==4)
	{
		printf("-1\n");
		exit(0);
	}
	else if(n==6)
	{
		ans[1][2]=ans[1][3]=ans[1][5]=1;
		ans[2][3]=ans[2][4]=ans[2][6]=1;
		ans[3][4]=ans[3][5]=1;
		ans[4][1]=ans[4][5]=ans[4][6]=1;
		ans[5][2]=ans[5][6]=1;
		ans[6][1]=ans[6][3]=1;
	}
	else
	{
		work(n-2);
		for(int i=1;i<=n-2;++i)
			ans[n-1][i]=1,ans[i][n]=1;
		ans[n][n-1]=1;
	}
}
void print()
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			printf("%d%c",ans[i][j],j<n?' ':'\n');
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d",&n);
	work(n);
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
