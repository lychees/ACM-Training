#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=303;
int d[maxn][maxn],n,Link[maxn],pre[maxn*2],t[maxn*2],fa[maxn],a[maxn],b[maxn],m,s[maxn];
int X[maxn*maxn*2],Y[maxn*maxn*2],F[maxn*maxn*2],tot=0;
long long sum[maxn];
inline int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
void add(int x,int y,int f)
{
	if(!f)return;
	a[x]-=f,a[y]+=f,X[++tot]=x,Y[tot]=y,F[tot]=f;
}
void work(int x,int y,int f)
{
	if(d[x][y]==1){add(y,x,f);return;}
	int tf;
	for(int i=Link[x];i;i=pre[i])
		if(d[x][t[i]]+d[t[i]][y]==d[x][y])
		{
			if(a[t[i]]<f)
			{
				tf=a[t[i]];
				add(t[i],x,tf);
				work(t[i],y,f);
				add(t[i],x,f-tf);
			}else add(t[i],x,f),work(t[i],y,f);
			break;
		}
}
int main()
{
	//freopen("tmp.in","r",stdin);
	//freopen("tmp.out","w",stdout);
	n=get(),get(),m=get();
	for(int i=1;i<=n;i++)a[i]=get(),fa[i]=i;
	for(int i=1;i<=n;i++)b[i]=get();
	for(int cnt=0,i=1;i<=m;i++)
	{
		int x=get(),y=get(),fx=getfa(x),fy=getfa(y);
		if(fx==fy)continue;else fa[fx]=fy;
		pre[++cnt]=Link[x]; Link[x]=cnt; t[cnt]=y;
		pre[++cnt]=Link[y]; Link[y]=cnt; t[cnt]=x;
	}
	for(int i=1;i<=n;i++)sum[getfa(i)]+=a[i]-b[i];
	for(int i=1;i<=n;i++)
		if(getfa(i)==i&&sum[i]!=0)return puts("NO"),0;
	for(int i=1;i<=n;i++)
	{
		int front=0,rear=1;
		s[front]=i,d[i][i]=0;
		while(front!=rear)
		{
			int p=s[front];
			for(int j=Link[p];j;j=pre[j])
				if(t[j]!=i&&!d[i][t[j]])d[i][t[j]]=d[i][p]+1,s[rear++]=t[j];
			front++;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j&&d[i][j]&&a[i]<b[i]&&a[j]>b[j])work(i,j,min(b[i]-a[i],a[j]-b[j]));
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)printf("%d %d %d\n",X[i],Y[i],F[i]);
	return 0;
}

