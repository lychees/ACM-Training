#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 100010
#define INF 314000000
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
vector<int> rule[maxn],way[maxn];
int minv[maxn],maxv[maxn];
int val[maxn],n,m,vis[maxn];
void read()
{
	scanf("%d %d",&m,&n);
	for(int i=1,p,s;i<=m;++i)
	{
		scanf("%d %d",&p,&s);
		way[p].push_back(i);
		for(int j=1;j<=s;++j)
		{
			scanf("%d",&p);
			if(p==-1)
				++val[i];
			else
				rule[i].push_back(p);
		}
	}
}
int Dp(int p)
{
	if(vis[p]==1)
		return 1<<30;
	if(vis[p]==2)
		return maxv[p];
	int &ans=maxv[p];
	vis[p]=1;
	each(r,way[p])
	{
		int sum=val[*r];
		bool mark=true;
		each(x,rule[*r])
		{
			if(minv[*x]==1<<30)
				mark=false;
		}
		if(!mark)
			continue;
		each(x,rule[*r])
		{
			int a=Dp(*x);
			if(sum==1<<30||a==1<<30)
				sum=1<<30;
			else
				sum=min(sum+a,INF);
		}
		ans=max(ans,sum);
	}
	vis[p]=2;
	return ans;
}
void print()
{
	fill(minv+1,minv+n+1,1<<30);
	for(bool mark=true;mark;)
	{
		mark=false;
		for(int i=1;i<=n;++i)
			each(r,way[i])
			{
				int sum=val[*r];
				each(x,rule[*r])
				{
					if(minv[*x]==1<<30||sum==1<<30)
						sum=1<<30;
					else
						sum=min(INF,sum+minv[*x]);
				}
				if(minv[i]>sum)
					minv[i]=sum,mark=true;
			}
	}
	for(int i=1;i<=n;++i)
	{
		if(!vis[i])
			Dp(i);
		if(minv[i]==1<<30)
			printf("%d %d\n",-1,-1);
		else
			printf("%d %d\n",minv[i],maxv[i]==1<<30?-2:maxv[i]);
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
