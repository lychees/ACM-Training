#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

vector <long long> v1;
pair <int,int> e[101000];
vector < pair<int,int> > ed[101000];
map <long long,int> Map;
int coo,s[101000],cod[101000],q[101000],n,K,r[100],x,y,ans,fa[101000],tims;
int ban[101000];
long long mask[101000],f[101000];

int find(int x)
{
	++coo;
	int en=1;
	q[en]=x;cod[x]=coo;fa[x]=0;
	for (int st=1;st<=en;st++)
	{
		int x=q[st];
		for (int i=0;i<ed[x].size();i++)
		{
			int y=ed[x][i].first,c=ed[x][i].second;
			if (!ban[c] && cod[y]<coo)
			{
				fa[y]=x;
				cod[y]=coo;
				q[++en]=y;
			}
		}
	}
	if (en==1) 
	{
		ans+=(mask[x]==0);
		return -1;
	}
	for (int i=en;i>=1;i--)
	{
		int x=q[i];
		bool flag=true;
		s[x]=1;
		for (int j=0;j<ed[x].size();j++)
		{
			int y=ed[x][j].first;
			if (!ban[ed[x][j].second] && fa[y]==x) 
			{
				s[x]+=s[y];
				if (s[y]>en/2)
				{
					flag=false;
					//break;
				}
				
			}
		}
		if (flag && en-s[x]<=en/2) return x;
	}
}

long long combine(long long x,long long y)
{
	long long ret=0,ba=1;
	for (int j=1;j<=K;j++)
	{
		ret+=(x%3+y%3)%3*ba;
		x/=3;y/=3;ba*=3;
	}
	return ret;
}

void getvec(long long x,vector <long long> &v)
{
	++coo;
	v.clear();
	int en=1;q[en]=x;cod[x]=coo;f[x]=mask[x];
	v.push_back(f[x]);
	for (int st=1;st<=en;st++)
	{
		int x=q[st];
		for (int i=0;i<ed[x].size();i++)
		{
			int y=ed[x][i].first;
			if (cod[y]==coo || ban[ed[x][i].second]) continue;
			cod[y]=coo;
			f[y]=combine(f[x],mask[y]);
			v.push_back(f[y]);
			q[++en]=y;
		}
	}
}

long long comp(long long x)
{
	long long ret=0,ba=1;
	for (int j=1;j<=K;j++)
	{
		ret+=(3-x%3)%3*ba;
		x/=3;ba*=3;
	}
	return ret;
}

void dfs(int x)
{
	int sep=find(x);
	if (sep<0) return;
	Map.clear();
	int ti=++tims;
	if (mask[sep]==0) ans++;
	Map[0]++;
	for (int i=0;i<ed[sep].size();i++)
	{
		if (ban[ed[sep][i].second]) continue;
		ban[ed[sep][i].second]=ti;
		getvec(ed[sep][i].first,v1);
		for (int j=0;j<v1.size();j++) 
		{
			long long tmp=comp(combine(v1[j],mask[sep]));
			if (Map.find(tmp)==Map.end()) continue;
			ans+=Map[tmp];
		}
		for (int j=0;j<v1.size();j++) Map[v1[j]]++;
	}
	for (int i=0;i<ed[sep].size();i++)
		if (ban[ed[sep][i].second]==ti)
			dfs(ed[sep][i].first);
}

int main()
{
	while (scanf("%d",&n)!=EOF && n)
	{
		for (int i=1;i<=n;i++) ed[i].clear(),ban[i]=fa[i]=s[i]=0;
	
		scanf("%d",&K);
		for (int i=1;i<=K;i++) scanf("%d",&r[i]);
		for (int i=1;i<=n;i++)
		{
			long long x;
			scanf("%I64d",&x);
			mask[i]=0;
			for (int j=K;j>=1;j--)
			{
				int cnt=0;
				while (!(x%r[j]))
				{
					cnt++;
					x/=r[j];
				}
				mask[i]=mask[i]*3+cnt%3;
			}
		}
		for (int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			ed[x].push_back(make_pair(y,i));
			ed[y].push_back(make_pair(x,i));
			e[i]=make_pair(x,y);
		}
		ans=0;
		dfs(1);
		cout<<ans<<endl;
	}
	
	return 0;
}