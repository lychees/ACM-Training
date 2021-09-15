#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define maxn 100010
#define INF 1000000000000000LL
using namespace std;
typedef long long LL;
struct Point
{
	LL x,y;
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.x<b.x||(a.y==b.y&&a.y<b.y);
	}
}p[maxn];
int n,m,r,father[maxn],size[maxn];
int Find(int p)
{
	if(father[p]!=p)
		father[p]=Find(father[p]);
	return father[p];
}
void read()
{
	scanf("%d %d",&n,&r);
	for(int i=1,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		p[i].x=a+b,p[i].y=a-b;
		father[i]=i;
	}
	sort(p+1,p+n+1);
}
void work()
{
	set< pair<LL,int> >T;
	T.insert(make_pair(-INF,0)),T.insert(make_pair(INF,0));
	for(int i=1,fr=1;i<=n;++i)
	{
		while(p[fr].x<p[i].x-r)
			T.erase(make_pair(p[fr].y,fr)),++fr;
		set< pair<LL,int> >::iterator R=T.lower_bound(make_pair(p[i].y,0)),L=R;
		--L;
		if(p[i].y-L->first<=r)
			father[Find(L->second)]=i;
		if(R->first-p[i].y<=r)
			father[Find(R->second)]=i;
		T.insert(make_pair(p[i].y,i));
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		++size[Find(i)],cnt+=father[i]==i;
	printf("%d %d\n",cnt,*max_element(size+1,size+n+1));
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
