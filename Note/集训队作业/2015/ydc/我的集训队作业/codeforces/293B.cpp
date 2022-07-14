#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#define maxn 15
#define mod 1000000007
using namespace std;
typedef long long LL;
map<int,int> dp[2];
bool occur[maxn];
int nRow,nCol,m,col[maxn][maxn];
void read()
{
	static int tmp[maxn][maxn];
	scanf("%d %d %d",&nRow,&nCol,&m);
	if(nRow+nCol-1>m)
	{
		printf("0\n");
		exit(0);
	}
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
		{
			scanf("%d",&col[i][j]);
			occur[col[i][j]]=true;
		}
	if(nRow<nCol)
	{
		for(int i=1;i<=nRow;++i)
			for(int j=1;j<=nCol;++j)
				tmp[j][i]=col[i][j];
		memset(col,0,sizeof(col));
		swap(nRow,nCol);
		for(int i=1;i<=nRow;++i)
			for(int j=1;j<=nCol;++j)
				col[i][j]=tmp[i][j];
	}
}
int get(int p,int k)
{
	return p>>(3*(k-1))&7;
}
int calc(int p,int k)
{
	return p<<(3*(k-1));
}
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
void Dp()
{
	int cur=0,S=0;
	for(int i=1;i<=m;++i)
		S|=calc(nCol+1,i);
	dp[cur][S]=1;
	for(int i=1;i<=nRow;++i)
		for(int j=1;j<=nCol;++j)
		{
			cur^=1,dp[cur].clear();
			for(map<int,int>::iterator it=dp[cur^1].begin();it!=dp[cur^1].end();++it)
			{
				bool mark=true;
				if(!col[i][j])
					for(int k=1;k<=m;++k)
					{
						if((occur[k]||mark)&&get(it->first,k)>j)
							add(dp[cur][it->first^calc(get(it->first,k)^j,k)],it->second);
						if(!occur[k]&&get(it->first,k)>nCol)
							mark=false;
					}
				else if(get(it->first,col[i][j])>j)
					add(dp[cur][it->first^calc(get(it->first,col[i][j])^j,col[i][j])],it->second);
			}
		}
	int ans=0,cnt=count(occur+1,occur+m+1,false);
	for(map<int,int>::iterator it=dp[cur].begin();it!=dp[cur].end();++it)
	{
		int tmp=cnt,val=it->second;
		for(int i=1;i<=m;++i)
			if(!occur[i]&&get(it->first,i)<=nCol)
				val=(LL)val*(tmp--)%mod;
		add(ans,val);
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Dp();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
