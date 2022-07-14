#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 100010
#define lowbit(x) (x&-x)
using namespace std;
set<int> num[maxn],pos;
set< pair<int,int> >val;
int n,m,dp[maxn],a[maxn];
void read()
{
	scanf("%d %d",&n,&m);
	++n;
	a[1]=-1<<30,dp[1]=1,num[1].insert(1),pos.insert(1),val.insert(make_pair(-1<<30,1));
}
bool check(int x,int want)
{
	set<int>::iterator it=num[want].upper_bound(x);
	return it!=num[want].end()&&a[*it]>a[x];
}
void Query()
{
	static int tmp[maxn];
	for(int i=1,t,x,y;i<=m;++i)
	{
		scanf("%d",&t);
		if(t==1)
		{
			scanf("%d %d",&x,&y);
			a[++x]=y-i;
			int tot=0;
			for(set< pair<int,int> >::iterator it=val.begin();it!=val.end()&&it->first<a[x];++it)
				if(it->second<x)
					tmp[++tot]=it->second;
			val.insert(make_pair(a[x],x)),pos.insert(x);
			int l=1,r=dp[1];
			while(l<r)
			{
				int mid=(l+r)>>1;
				check(x,mid)?l=mid+1:r=mid;
			}
			dp[x]=l,num[l].insert(x);
			sort(tmp+1,tmp+tot+1);
			for(int j=tot;j>=1;--j)
				if(check(tmp[j],dp[tmp[j]]))
					num[dp[tmp[j]]].erase(tmp[j]),num[++dp[tmp[j]]].insert(tmp[j]);
		}
		else
		{
			scanf("%d",&x);
			set<int>::iterator it=pos.begin();
			int tot=0;
			for(int j=1;j<=x;++j,++it)
				tmp[++tot]=*it;
			int p=a[*it];
			num[dp[*it]].erase(*it),val.erase(make_pair(a[*it],*it)),pos.erase(it);
			for(int j=tot;j>=1;--j)
				if(a[tmp[j]]<p&&!check(tmp[j],dp[tmp[j]]-1))
					num[dp[tmp[j]]].erase(tmp[j]),num[--dp[tmp[j]]].insert(tmp[j]);
		}
		printf("%d\n",dp[1]-1);
	}
}
int main()
{
	read();
	Query();
	return 0;
}
