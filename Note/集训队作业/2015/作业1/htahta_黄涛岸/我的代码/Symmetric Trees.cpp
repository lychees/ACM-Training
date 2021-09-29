#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define x first
#define y second
using namespace std;
typedef unsigned long long LL;
const int maxn=10003;
LL hash[maxn];
pair<LL,int> a[maxn];
int col[maxn],n,Link[maxn],pre[maxn*2],t[maxn*2],root;
bool haveans,g;
LL gethash(int x,int pa)
{
	LL h=col[x];
	for(int i=Link[x];i;i=pre[i])
		if(t[i]!=pa)h*=gethash(t[i],x);
	h=(h*47231+1237)^783126421878ll;
	if(g)hash[x]=h;
	return h;
}
int dfs(int x,int pa)
{
	int size=1;
	for(int i=Link[x];i;i=pre[i])
		if(t[i]!=pa)size+=dfs(t[i],x);
	if(size*2>=n&&!root)root=x,g=1,gethash(x,0);
	if(size*2==n)g=0,haveans=gethash(x,pa)==hash[pa];
	return size;
}
bool dp(int x,int pa)
{
	int cnt=0,Tc=0,c[5];
	for(int i=Link[x];i;i=pre[i])
		if(t[i]!=pa)a[++cnt]=make_pair(hash[t[i]],t[i]);
	sort(a+1,a+1+cnt);
	for(int i=1;i<=cnt&&Tc<3;i++)
		if(i==cnt||a[i].x!=a[i+1].x)c[++Tc]=a[i].y;else i++;
	if((!pa&&Tc>2)||(pa&&Tc>1))return 0;
	for(int i=1;i<=Tc;i++)
		if(!dp(c[i],x))return 0;
	return 1;
}
int main()
{
	int T;scanf("%d",&T);
	for(int _=1;_<=T;_++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf(" %c",col+i),Link[i]=0;
		for(int i=1,tot=0;i<n;i++)
		{
			int x,y;scanf("%d%d",&x,&y);
			pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y;
			pre[++tot]=Link[y]; Link[y]=tot; t[tot]=x;
		}
		root=haveans=0,dfs(1,0);
		printf("Case #%d: ",_);
		puts(haveans||dp(root,0)?"SYMMETRIC":"NOT SYMMETRIC");
	}
	return 0;
}
