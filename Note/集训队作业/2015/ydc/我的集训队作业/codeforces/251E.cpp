#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cassert>
#define maxn 200010
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define mod 1000000007
using namespace std;
typedef long long LL;
vector<int> adj[maxn];
vector< pair<int,int> > hash[maxn];
int n,m,dp[maxn],near[maxn],size[maxn];
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
void read()
{
	scanf("%d",&n);
	m=n,n*=2;
	for(int i=2,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}
int g(int a,int b)
{
	if(a>b)
		swap(a,b);
	if((size[a]+size[b])&1)
		return 0;
	else if(adj[a].size()==1u&&adj[b].size()==1u)
	{
		each(x,hash[a])
			if(x->first==b)
				return x->second;
		int ans=g(adj[a][0],adj[b][0]);
		hash[a].push_back(make_pair(b,ans));
		return ans;
	}
	else if(adj[a].size()==2u||adj[b].size()==2u)
		return 0;
	else if(adj[a].size()==1u)
		return dp[adj[a][0]];
	else if(adj[b].size()==1u)
		return dp[adj[b][0]];
	else
		return 1;
}
void Tree_Dp(int p)
{
	near[p]=-1,size[p]=1;
	int cnt=0,num;
	each(x,adj[p])
	{
		adj[*x].erase(find(adj[*x].begin(),adj[*x].end(),p));
		Tree_Dp(*x);
		size[p]+=size[*x];
		if(adj[*x].size()==2u)
			near[p]=*x,++cnt,num=x-adj[p].begin();
		else if(near[*x]!=-1)
			near[p]=near[*x],++cnt,num=x-adj[p].begin();
	}
	if(cnt==2||size[p]%2)
		return ;
	else if(cnt==0)
	{
		if(adj[p].size()==1u)
			dp[p]=size[p]>>1;
		else
		{
			int x=adj[p][0],y=adj[p][1];
			if(size[x]>size[y])
				swap(x,y);
			dp[p]=max(1,(size[y]-size[x]-1)/2)+(size[y]-size[x]+1)/2;
		}
	}
	else if(adj[p].size()==1u)
	{
		if(adj[adj[p][0]].size()==1u)
			add(dp[p],dp[adj[adj[p][0]][0]]);
		int v=near[p],L=size[adj[p][num]]-size[v]+2;
		for(int i=0;i<=1;++i)
		{
			int a=adj[v][i],b=adj[v][i^1];
			if(adj[a].size()!=2u)
			{
				if(near[a]!=-1)
					continue;
				if(size[a]==L)
					add(dp[p],dp[b]);
				if(size[a]==L-2)
					add(dp[p],dp[b]);
			}
			else
			{
				for(int j=0;j<=1;++j)
				{
					int c=adj[a][j],d=adj[a][j^1];
					if(near[c]!=-1||adj[c].size()==2u)
						continue;
					if(size[c]+1==L)
						add(dp[p],g(b,d));
				}
			}
		}
	}
	else
	{
		if(adj[adj[p][num^1]].size()==1u)
			dp[p]=g(adj[p][num],adj[adj[p][num^1]][0]);
		else
			dp[p]=dp[adj[p][num]];
		if(adj[p][num]!=near[p])
			add(dp[p],g(adj[adj[p][num]][0],adj[p][num^1]));
	}
}
int work(int L,int R,int D)
{
	if(adj[D].size()==0u)
		return (LL)dp[L]*dp[R]%mod;
	else if(adj[D].size()==1u)
		return ((LL)dp[L]*g(R,adj[D][0])+(LL)dp[R]*g(L,adj[D][0]))%mod;
	else
		return ((LL)g(L,adj[D][0])*g(R,adj[D][1])+(LL)g(L,adj[D][1])*g(R,adj[D][0]))%mod;
}
int work()
{
	if(m==1)
		return 2;
	for(int i=1;i<=n;++i)
		if(adj[i].size()>3u)
			return 0;
	int a[3];
	for(int i=1;i<=n;++i)
		if(adj[i].size()==3u)
		{
			a[0]=adj[i][0],a[1]=adj[i][1],a[2]=adj[i][2];
			adj[a[0]].erase(find(adj[a[0]].begin(),adj[a[0]].end(),i));
			adj[a[1]].erase(find(adj[a[1]].begin(),adj[a[1]].end(),i));
			adj[a[2]].erase(find(adj[a[2]].begin(),adj[a[2]].end(),i));
			Tree_Dp(a[0]),Tree_Dp(a[1]),Tree_Dp(a[2]);
			int ans=0;
			sort(a,a+3);
			do
			{
				add(ans,work(a[0],a[1],a[2]));
			}while(next_permutation(a,a+3));
			return ans*2%mod;
		}
	return (2LL*m*m-2LL*m+4)%mod;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	cout<<work()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
