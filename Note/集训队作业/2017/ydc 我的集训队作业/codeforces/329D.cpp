#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define maxn 310
using namespace std;
int n,m;
char map[maxn][maxn];
void print()
{
	n<<=1;
	for(int i=1;i<n;++i)
	{
		if(i&1)
		{
			for(int j=1;j<n/2;++j)
				map[i][j+1]='>';
			for(int j=1;j<n/2;++j)
				map[i][n-j]=j&1?'.':'>';
			map[i][n]='v';
		}
		else
		{
			for(int j=1;j<n/2;++j)
				map[i][n-j+1]='<';
			for(int j=1;j<n/2;++j)
				map[i][2+j]=j&1?'.':'<';
			map[i][2]='v';
		}
	}
	map[1][1]='>';
	for(int i=n/2+1;i<=n;++i)
		map[i][1]='^';
	for(int i=1;i<n/2;++i)
		map[i+1][1]=i&1?'.':'^';
	for(int i=n/2+1;i<=n;++i)
		map[n][i]='<';
	for(int i=1;i<n/2;++i)
		map[n][i+1]=i&1?'.':'<';
	for(int i=1;i<=n;i++)
		printf("%s\n",map[i]+1);
	puts("1 1");
}
int main()
{
	scanf("%d %d",&n,&m);
	print();
	return 0;
}
