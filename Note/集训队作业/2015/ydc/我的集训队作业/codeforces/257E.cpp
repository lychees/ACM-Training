#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define lowbit(x) x&-x
#define maxn 100010
using namespace std;
typedef long long LL;
template<class T>
void Read(T &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct Event
{
	int id,ed,st;
	LL t;
	friend bool operator < (const Event &a,const Event &b)
	{
		return a.t<b.t;
	}
}Eve[maxn];
int n,m,sum[maxn];
set< pair<LL,int> > wait;
void add(int p,int v)
{
	for(int i=p;i<=m;i+=lowbit(i))
		sum[i]+=v;
}
int getsum(int p)
{
	int ans=0;
	for(int i=p;i;i-=lowbit(i))
		ans+=sum[i];
	return ans;
}
int getsum(int l,int r)
{
	return getsum(r)-getsum(l-1);
}
void read()
{
	Read(n),Read(m);
	for(int i=1;i<=n;++i)
	{
		Eve[i].id=i;
		Read(Eve[i].t),Read(Eve[i].st),Read(Eve[i].ed);
	}
	sort(Eve+1,Eve+n+1);
}
void work()
{
	static LL ans[maxn];
	LL nowT=0;
	int now=1,l=1,dir=0;
	wait.insert(make_pair(1000000000000000LL,0));
	Eve[n+1].t=1000000000000000LL;
	while(l<=n||dir)
	{
		int r;
		while(nowT<Eve[l].t&&dir)
		{
			set< pair<LL,int> >::iterator it=wait.upper_bound(make_pair(now,0));
			if(dir==-1)
				--it;
			if(nowT+abs(now-it->first)<=Eve[l].t)
			{
				nowT+=abs(now-it->first),now=it->first;
				while(it->first==now)
				{
					if(it->first==Eve[it->second].st)
					{
						add(it->first,-1),add(Eve[it->second].ed,1);
						wait.insert(make_pair(Eve[it->second].ed,it->second));
					}
					else
						ans[Eve[it->second].id]=nowT,add(it->first,-1);
					wait.erase(it),it=wait.lower_bound(make_pair(now,0));
				}
				int v1=getsum(1,now-1),v2=getsum(now+1,m);
				if(v1==0&&v2==0)
					dir=0;
				else
					dir=v1>v2?-1:1;
			}
			else
				now+=dir*(Eve[l].t-nowT),nowT=Eve[l].t;
		}
		for(r=l;r<=n&&Eve[r].t==Eve[l].t;++r)
		{
			if(Eve[r].st==now)
				add(Eve[r].ed,1),wait.insert(make_pair(Eve[r].ed,r));
			else
				add(Eve[r].st,1),wait.insert(make_pair(Eve[r].st,r));
		}
		int v1=getsum(1,now-1),v2=getsum(now+1,m);
		if(v1==0&&v2==0)
			dir=0;
		else
			dir=v1>v2?-1:1;
		nowT=Eve[l].t,l=r;
	}
	for(int i=1;i<=n;++i)
		printf("%I64d\n",ans[i]);
}
int main()
{
	read();
	work();
	return 0;
}
