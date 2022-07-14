#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
int n,use[maxn];
void DFS(int p)
{
	use[p]=1;
	if(p==1)
	{
		printf("0 1 ");
		return ;
	}
	!use[(p+n)/2]?DFS((p+n)/2):DFS(p/2);
	printf("%d ",p);
}
int main()
{
	freopen("input.txt","r",stdin);
	cin>>n;
	if(n&1)
		printf("-1\n");
	else
		DFS(0);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
