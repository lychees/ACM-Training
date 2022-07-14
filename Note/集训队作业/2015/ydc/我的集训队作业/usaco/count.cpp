#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
struct node
{
	long long x,y;
	double Tan;
}point[100010];
long long n,sum,now;
bool cmp(struct node a,struct node b)
{
	return a.Tan<b.Tan;
}
long long calc(int a,int b)
{
	return point[a].x*point[b].y-point[b].x*point[a].y;
}
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%I64d %I64d",&point[i].x,&point[i].y);
		point[i].Tan=atan2(point[i].x,point[i].y);
	}
	sort(point+1,point+n+1,cmp);
}
void solve()
{
	for(int i=1,j=2;i<=n;i++)
	{
		for(;calc(i,j)<0;j=j%n+1)
			now++;
		sum=sum+now*(now-1)/2,now--;
	}
}
int main()
{
	read();
	solve();
	printf("%I64d\n",n*(n-1)*(n-2)/6-sum);
	return 0;
}
