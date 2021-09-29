#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define mp make_pair
#define x first
#define y second
using namespace std;
const int inf=1000000000;
int n,m,a[20],all;
pair<int,int> f[1<<18],v;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",a+i);
	all=1<<n;
	for(int i=1;i<all;i++)f[i]=mp(inf,inf);
	f[0]=mp(1,0);
	for(int i=0;i<all;i++)
	{
		if(f[i].x==inf)continue;
		for(int j=0;j<n;j++)
			if(!(i&(1<<j)))
			{
				v=mp(inf,inf);
				if(m-f[i].y>=a[j])v=mp(f[i].x,f[i].y+a[j]);
				else if(m>=a[j])v=mp(f[i].x+1,a[j]);
				if(f[i|(1<<j)]>v)f[i|(1<<j)]=v;
			}
	}
	printf("%d\n",f[all-1].x);
	return 0;
}
