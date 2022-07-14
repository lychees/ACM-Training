#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 5010
using namespace std;
char a[maxn];
int Sg[maxn],n;
void Prepare()
{
	static int flag[maxn];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
			flag[Sg[max(0,j-2)]^Sg[max(0,i-j-1)]]=i;
		for(Sg[i]=0;flag[Sg[i]]==i;Sg[i]++);
	}
}
int check(int p)
{
	int cnt=0,SumNim=0;
	for(int i=1;i<=n;i++)
	{
		if(abs(i-p)>1&&a[i-1]==a[i+1])
			cnt++;
		else
		{
			SumNim^=Sg[cnt];
			cnt=0;
		}
	}
	return SumNim;
}
void work()
{
	for(int i=2;i<=n-1;i++)
		if(a[i-1]==a[i+1]&&!check(i))
		{
			printf("First\n%d\n",i);
			return ;
		}
	printf("Second\n");
}
int main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	Prepare();
	work();
	return 0;
}
