#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#define maxn 100010
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
struct Line
{
	int h,l,r;
	friend bool operator < (const Line &a,const Line &b)
	{
		return a.h>b.h;
	}
}L[maxn];
int n,ans[maxn];
set< pair<int,int> >T;
void read()
{
	int m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d %d %d",&L[i].h,&L[i].l,&L[i].r);
	sort(L+1,L+n+1);
}
int calc(int a,int b)
{
	return min(L[a].r,L[b].r)-max(L[a].l,L[b].l);
}
void work()
{
	static bool bottom[maxn];
	T.insert(make_pair(-1000000000,0));
	L[0].l=-1000000000,L[0].r=1000000000;
	ans[0]=2000000000;
	memset(bottom,true,sizeof(bottom));
	for(int i=1,x;i<=n;++i)
	{
		set< pair<int,int> >::iterator it=T.upper_bound(make_pair(L[i].l,1<<30)),next=it;
		for(--it;it!=T.end()&&it->first<L[i].r;it=next++)
		{
			x=it->first;
			int y=next==T.end()?1000000000:next->first;
			if(x==L[it->second].l&&L[it->second].r==y)
				ans[i]=max(ans[i],min(ans[it->second],calc(it->second,i)));
			if(x<=L[i].l&&L[it->second].r==y)
				ans[i]=max(ans[i],min(ans[it->second],calc(it->second,i)));
			if(y>=L[i].r&&L[it->second].l==x)
				ans[i]=max(ans[i],min(ans[it->second],calc(it->second,i)));
			if(x<=L[i].l&&y>=L[i].r)
				ans[i]=max(ans[i],min(ans[it->second],calc(it->second,i)));
			bottom[it->second]=false;
			if(next==T.end()||next->first>L[i].r)
				next=T.insert(make_pair(L[i].r,it->second)).first;
			T.insert(make_pair(L[i].l,i));
			if(x>=L[i].l)
				T.erase(it);
		}
		T.insert(make_pair(L[i].l,i));
	}
	int maxv=0;
	for(int i=1;i<=n;++i)
		if(bottom[i])
			maxv=max(maxv,ans[i]);
	printf("%d\n",maxv);
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
