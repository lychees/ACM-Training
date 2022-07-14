#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1000010
using namespace std;
int n,m,a[maxn],sum[maxn];
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	Read(n),Read(m);
	for(int i=1;i<=m;++i)
		Read(a[i]);
}
void Run(int x)
{
	int rem=a[1]-x,maxv=0,now=0;
	printf("%d\n",rem);
	a[1]=x;
	for(int i=1;i<=m;++i)
		now+=a[i],++sum[a[i]],maxv=max(maxv,a[i]);
	for(int i=1;i<=m;++i)
		if(a[i])
		{
			while(!sum[maxv])
				--maxv;
			for(int j=1;j<=a[i];++j)
				printf("%d\n",i);
			for(int j=i+1;j<=m&&a[i];++j)
				while(a[i]&&a[j])
				{
					int tmp=maxv;
					--sum[a[j]--],++sum[a[j]],--sum[a[i]--],++sum[a[i]],now-=2;
					while(!sum[maxv])
						--maxv;
					if(now-maxv<maxv)
					{
						--sum[a[j]++],++sum[a[j]],--sum[a[i]++],++sum[a[i]],now+=2,maxv=tmp;
						break;
					}
					else
						printf("%d\n",j);
				}
		}
	for(int i=1;i<=rem;++i)
		printf("1\n");
}
void print()
{
	int maxv=*max_element(a+2,a+m+1);
	if(maxv>=n-maxv)
	{
		printf("NO\n");
		return ;
	}
	else if(m==2)
	{
		printf("YES\n");
		for(int i=1;i<=n;++i)
			printf("%d\n",i<=a[1]?1:2);
	}
	else
	{
		printf("YES\n");
		if(maxv>n-a[1]-maxv)
			Run(maxv-(n-a[1]-maxv));
		else if((n-a[1])&1)
			Run(1);
		else
			Run(0);
	}
}
int main()
{
	read();
	print();
	return 0;
}
