#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
const int N=255;
int CT,n,lc[N],rc[N],val[N],siz[N];
int f[N][2][3];

inline int merge(int a,int b,bool c)
{return a==-1?b:(b==-1?a:(a<b)^c?b:a);}

int tdfs(int x)
{
	memset(f[x],-1,sizeof(f[0]));
	if(~val[x])return siz[x]=0;
	siz[x]=1+tdfs(lc[x])+tdfs(rc[x]);
	if(siz[rc[x]]&1)swap(lc[x],rc[x]);
	return siz[x];
}

int dp(int x,int p,int s)
{
	if(~val[x])return val[x];
	if(siz[x]==1)return merge(val[lc[x]],val[rc[x]],p^(s==2));
	int &res=f[x][p][s],u,v;
	if(~res)return res;
	if(s)//skip
	{
		if(siz[x]&1)//odd
		{
			if(s==1)res=dp(x,!p,0);//use the ship and he play with no skip
			if(siz[lc[x]]&1)//lc=rc=odd
			{
				res=merge(res,merge(dp(lc[x],p,0),dp(rc[x],!p,siz[lc[x]]==1&&s==1?2:1),!p),p);
				res=merge(res,merge(dp(rc[x],p,0),dp(lc[x],!p,siz[rc[x]]==1&&s==1?2:1),!p),p);
			}
			else//lc=rc=even
			{
				if(siz[rc[x]])
					res=merge(res,merge(dp(lc[x],!p,0),dp(rc[x],p,siz[lc[x]]==0&&s==1?2:1),!p),p);
				if(siz[lc[x]])
					res=merge(res,merge(dp(rc[x],!p,0),dp(lc[x],p,siz[rc[x]]==0&&s==1?2:1),!p),p);
			}
		}
		else
			res=merge(dp(rc[x],p,0),dp(lc[x],p,siz[rc[x]]==0&&s==1?2:1),p);
	}
	else
	{
		if(siz[x]&1)
			if(siz[lc[x]]&1)
				res=merge(dp(lc[x],p,1),dp(rc[x],p,1),p);
			else
				res=merge(dp(lc[x],p,0),dp(rc[x],p,0),p);
		else
		{
			u=merge(dp(lc[x],p,0),dp(rc[x],!p,0),!p);
			v=merge(dp(lc[x],!p,1),dp(rc[x],p,1),!p);
			res=merge(u,v,p);
		}
	}
	return res;
}

int main()
{
	for(scanf("%d",&CT);CT--;)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%d",val+i);
			if(val[i]==-1)scanf("%d%d",lc+i,rc+i);
		}
		tdfs(0);
		printf("%d\n",dp(0,0,0));
	}
	return 0;
}
