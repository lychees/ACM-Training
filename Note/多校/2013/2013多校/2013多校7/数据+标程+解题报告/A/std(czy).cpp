#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iterator>

using namespace std;

#define itm map<int,int>::iterator

int k;
int nq,od,id,nh,last,cnt;
int x[65536][8];
map <int,int> h[64];

inline void dec(int v,int p)
{
	itm i=h[p].find(v);
	(*i).second--;
	if ((*i).second==0) h[p].erase(i);
}

inline void inc(int v,int p)
{
	h[p][v]++;
}

void dfs(int dep,int id,void f(int,int),int now,int p)
{
	if (dep>k)
	{
		f(now+x[id][dep],p);
		return;
	}
	dfs(dep+1,id,f,now-x[id][dep],p*2);
	dfs(dep+1,id,f,now+x[id][dep],p*2+1);
}

int main()
{
	while (scanf("%d%d",&nq,&k) != EOF) {
		nh=1<<k;
		od=id=last=cnt=0;
		for (int i=0;i<64;++i) h[i].clear();
		memset(x, 0, sizeof x);
		for (int i=1;i<=nq;i++)
		{
			scanf("%d",&od);
			if (od==0)
			{
				for (int j=1;j<=k;j++) scanf("%d",x[i]+j);
				dfs(1,i,inc,0,0);
			}
			else
			{
				scanf("%d",&id);
				dfs(1,id,dec,0,0);
			}
			int ans=0;
			for (int j=0;j<nh;j++)
			{
				itm l=h[j].begin();
				itm r=h[j].end();
				r--;
				ans=max(ans,abs((*r).first-(*l).first));
			}
			if (last!=ans) cnt++;
			last=ans;
			printf("%d\n",ans);
		}
		//printf("\n");
	}
	return 0;
}
