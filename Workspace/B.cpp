#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,p,k,head[160],rd[160],dp[160][160],siz[160],ans=0x3f3f3f;
struct edge {int to,next;} ed[330];
void adde(int u,int v){ed[++k].to=v;ed[k].next=head[u];head[u]=k;}

void dfs1(int u,int fa)
{
	siz[u]++;
	for(int i=head[u];i;i=ed[i].next)
	{
		int v=ed[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
	}
	dp[u][siz[u]]=1;//如果切掉整棵子树，只需切掉与父节点的连边
	dp[u][0]=0;//不切
}

void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=ed[i].next)
	{
		int v=ed[i].to;
		if(v==fa) continue;
		dfs2(v,u);
		for(int j=siz[u]-1;j;j--)//我切多少
		for(int k=0;k<=j ;k++)//我的儿子切多少
		dp[u][j]=min(dp[u][j],dp[u][j-k]+dp[v][k]);
		//我切j个节点切的最少边数=min 我切j-k个节点的最少边数+我的儿子切k个节点的最少边数
	}
	if(siz[u]-p>=0)//有那么多节点
	ans=min(ans,dp[u][siz[u]-p]+bool(fa));
	//min 切掉siz[u]-p个节点(剩P个节点)的最少边数+分开我与父亲的边
}

int main()
{
	scanf("%d%d",&n,&p);
	memset(dp,0x3f3f3f,sizeof(dp));//初始化为最大值
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adde(u,v);adde(v,u);
	}
	dfs1(1,1);//求siz数组 & 初始化
	dp[1][siz[1]]=0;//根节点不需要与父节点分开  （没有父亲。。。）
	dfs2(1,0);//树形dp
	printf("%d",ans);
	return 0;
}
