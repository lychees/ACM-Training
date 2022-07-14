#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
typedef long long LL;
int n,x[maxn],y[maxn],cx[maxn],cy[maxn];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d",x+i,y+i);
		cx[i]=x[i],cy[i]=y[i];
	}
}
LL work()
{
	int s[2][2]={{0,0},{0,0}},f=0;
	LL ans=0;
	sort(x+1,x+n+1),sort(y+1,y+n+1);
	int m=(n+1)>>1,dx=x[m+1]-x[m],dy=y[m+1]-y[m];
	if(n&1)
		dx=min(dx,x[m]-x[m-1]),dy=min(dy,y[m]-y[m-1]);
	for(int i=1;i<=n;++i)
	{
		ans+=abs(x[i]-x[m])+abs(y[i]-y[m]);
		s[cx[i]<=x[m]][cy[i]<=y[m]]=1;
		f|=cx[i]==x[m]&&cy[i]==y[m];
	}
	if((n%2==0||f)&&s[0][0]&&s[0][1])
		ans-=min(dx,dy);
	return ans*2;
}
int main()
{
	read();
	cout<<work()<<endl;
	return 0;
}
