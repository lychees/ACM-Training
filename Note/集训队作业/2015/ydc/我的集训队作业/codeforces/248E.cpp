#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define maxm 110
using namespace std;
int n,a[maxn],cnt[maxn];
double prob[maxn][maxm],ans;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	Read(n);
	for(int i=1;i<=n;++i)
	{
		Read(a[i]);
		prob[i][a[i]]=1,cnt[i]=a[i];
	}
	ans=count(a+1,a+n+1,0);
}
void work()
{
	int m;
	Read(m);
	for(int i=1,u,v,s;i<=m;++i)
	{
		Read(u),Read(v),Read(s);
		ans-=prob[u][0];
		for(int j=0;j<=a[u];++j)
		{
			if(j+s>cnt[u])
				prob[u][j]=0;
			else
			{
				double sum=0,p=1;
				for(int k=1;k<=s;++k)
					p=p*(cnt[u]-j-s+k)/(cnt[u]-s+k);
				for(int k=0;k<=s;++k)
				{
					sum+=prob[u][j+k]*p;
					p=p*(j+k+1)/(k+1)/(cnt[u]-j-k)*(s-k);
				}
				prob[u][j]=sum;
			}
		}
		ans+=prob[u][0],cnt[u]-=s,cnt[v]+=s;
		printf("%.10f\n",ans);
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
