#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
//#include <ctime>

using namespace std;

#define maxn 3*10010
#define maxm 500010

int set[300][maxn];
int fa[maxn];
int Find1(int id,int i)
{
	if(id==set[i][id])
		return id;
	return set[i][id]=Find1(set[i][id],i);
}
int Find2(int id)
{
	if(id==fa[id])
		return id;
	return fa[id]=Find2(fa[id]);
}

vector<int>edge[maxn];
vector<int>que[maxn];
vector<int>R[maxn];
int n,m,q;
int num=0;
int ll[maxn],rr[maxn];
int sccnum[300];
int ans[maxn];
int first[maxn];
int main()
{
	int T;
	//freopen("input.txt","r",stdin);
	//freopen("ans.txt","w",stdout);
	scanf("%d",&T);
	int Cas=0;
//	int ST,ED;
//	ST=clock();
	while(T--)
	{
		printf("Case #%d:",++Cas);
		puts("");
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++)
		{
			edge[i].clear();
			que[i].clear();
			R[i].clear();
		}
		for(int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		scanf("%d",&q);
		for(int i=1;i<=q;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			que[l].push_back(i);
			R[l].push_back(r);
		}
		num=(int)sqrt(n);
		memset(sccnum,0,sizeof(sccnum));
		memset(first,-1,sizeof(first));
		int cnt=0,top=1;
		for(int i=1;i<=n;i++)
		{
			cnt++;
			cnt%=num+1;
			if(cnt==0)
			{
				cnt++;
				top++;
			}
			rr[top]=i;
		}
		for(int i=1;i<=n;i++)
			for(int j=0;j<=top;j++)
				set[j][i]=i;

		rr[0]=0;
		int run_clock=0;
		for(int i=n;i>=1;i--)
		{
			for(int k=1;k<=top;k++)
			{
				if(i>rr[k])
					continue;
				sccnum[k]++;
				int inc=0;
				for(int j=0;j<edge[i].size();j++)
				{
					int u=i,v=edge[i][j];
					if(v>i)
					{
						if(i<=rr[k] && v<=rr[k])
						{
							u=Find1(u,k);
							v=Find1(v,k);
							if(u!=v)
							{
								inc++;
								set[k][v]=u;
							}
						}
					}
				}
				sccnum[k]-=inc;
			}
			for(int j=0;j<R[i].size();j++)
			{
				int r=R[i][j];
				run_clock++;
				int k;
				for(k=0;k<top;k++)
					if(rr[k]<r && r<=rr[k+1])
						break;
				int inc=0;
			 	for(int g=max(rr[k]+1,i+1);g<=r;g++)
			 	{
			 		if(run_clock!=first[g])
			 		{
			 			first[g]=run_clock;
			 			fa[g]=g;
			 		}
			 		for(int f=0;f<edge[g].size();f++)
			 		{
			 			int v=edge[g][f];
			 			if(v>=i && v<=r)
			 			{
			 				v=Find1(v,k);
			 				if(run_clock!=first[v])
			 				{
			 					first[v]=run_clock;
			 					fa[v]=v;
			 				}
			 				if(Find2(g)!=Find2(v))
			 				{
			 					fa[Find2(g)]=Find2(v);
			 					//if(r==9 && i==8)
			 					//	cout<<g<<" "<<edge[g][f]<<endl;
			 					inc++;
			 				}

			 			}
			 		}
			 	}
			 	//if(r==9 && i==8)
			 		//cout<<sccnum[k]<<" "<<r-max(rr[k],i-1)<<" "<<inc<<endl;
			 	ans[que[i][j]]=sccnum[k]+r-max(rr[k],i-1)-inc;
			}
		}
		for(int i=1;i<=q;i++)
			printf("%d\n",ans[i]);
	}
	fclose(stdin);
	fclose(stdout);
	//cout<<clock()-ST<<endl;
}
