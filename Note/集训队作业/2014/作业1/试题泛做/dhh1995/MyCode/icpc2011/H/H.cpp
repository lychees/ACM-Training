#include<cstdio>
#include<algorithm>
using namespace std;
#define N 100005
int n,m,x,y,l,cnt,D,top,now,Case,root,w;
int dfn[N],low[N],stack[N],son[N],ed[N],next[N],num[N],flag[N];
bool b[N],instack[N];
long long ans;
void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++D; instack[x]=1; stack[++top]=x;
	for (int p=son[x];p;p=next[p]){
		int y=ed[p]; if (y==fa) continue;
		if (!dfn[y]){
			tarjan(y,x),low[x]=min(low[x],low[y]);
			if (low[y]>=dfn[x]){
				int k; now++; b[x]=1; if (x==root) w++;
				do k=stack[top--],instack[k]=0,flag[now]+=b[k],num[now]++; while (k!=y);
				}
			}
		else if (instack[y]) low[x]=min(low[x],dfn[y]);
		}
}
int main()
{
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
	while (scanf("%d",&m),m){
		n=cnt=l=D=top=now=0,ans=1;
		for (int i=1;i<=m;i++)
			scanf("%d%d",&x,&y),n=n>x?n:x,n=n>y?n:y,
			ed[++l]=y,next[l]=son[x],son[x]=l,
			ed[++l]=x,next[l]=son[y],son[y]=l;
		for (int i=1;i<=n;i++){
			root=i,w=0;
			if (!dfn[i]) tarjan(i,0);
			if (w==1) flag[now]--;
			}
		for (int i=1;i<=now;i++){
			if (!flag[i]) cnt++,ans*=num[i];
			num[i]=flag[i]=0;
			}
		if (!cnt) printf("Case %d: 2 %lld\n",++Case,1LL*n*(n-1)/2);
		else printf("Case %d: %d %lld\n",++Case,cnt,ans);
		for (int i=1;i<=n;i++) instack[i]=b[i]=son[i]=dfn[i]=0;
		}
	return 0;
}
