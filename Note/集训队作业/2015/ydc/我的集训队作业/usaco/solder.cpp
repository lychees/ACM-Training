#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 50010
using namespace std;
typedef long long LL;
struct Point
{
	int L;
	LL c;
	Point() {}
	Point(int L,LL c): L(L),c(c) {}
	LL calc()
	{
		return c+L*L;
	}
	friend bool operator < (const Point &a,const Point &b)
	{
		return a.L<b.L||(a.L==b.L&&a.c<b.c);
	}
};
int n;
vector<int> adj[maxn];
vector<Point> conv[maxn],tmp;
void read()
{
	scanf("%d",&n);
	for(int i=2,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}
void Tree_Dp(int p,int d)
{
	conv[d].clear();
	if(adj[p].size()==0u)
	{
		conv[d].push_back(Point(0,0));
		return ;
	}
	each(x,adj[p])
	{
		adj[*x].erase(find(adj[*x].begin(),adj[*x].end(),p));
		Tree_Dp(*x,d+1);
		tmp.clear();
		each(B,conv[d+1])
			++B->L;
		if(conv[d].size()==0u)
			tmp=conv[d+1];
		else
		{
			each(A,conv[d])
				each(B,conv[d+1])
				{
					if(!A->L)
						tmp.push_back(Point(0,B->calc()+A->c));
					else
					{
						tmp.push_back(Point(A->L,B->calc()+A->c));
						tmp.push_back(Point(B->L,A->calc()+B->c));
						tmp.push_back(Point(0,A->calc()+B->calc()+2*A->L*B->L));
					}
				}
		}
		sort(tmp.begin(),tmp.end());
		int tot=0;
		for(int i=1;i<(int)tmp.size();++i)
			if(tmp[i].calc()<tmp[tot].calc())
				tmp[++tot]=tmp[i];
		tmp.resize(tot+1);
		conv[d]=tmp;
	}
}
LL work()
{
	LL ans=1000000000000000000LL;
	each(x,conv[0])
		if(!x->L||adj[1].size()==1u)
			ans=min(ans,x->calc());
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	Tree_Dp(1,0);
	cout<<work()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
