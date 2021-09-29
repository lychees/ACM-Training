#include<bits/stdc++.h>
using namespace std;
struct node
{
	int son[26],fa,len;
}a[600001];int cnt=1,last=1;
int rcnt[600001],rmax[600001],in[600001],q[600001];
bool v[600001];
void add(int x,int pos)
{
	int p=last,np=++cnt;
	a[np].len=a[p].len+1;rcnt[np]=1;rmax[np]=pos;
	for(;p&&!a[p].son[x];p=a[p].fa)a[p].son[x]=np;
	if(!p)a[np].fa=1;
	else if(a[a[p].son[x]].len==a[p].len+1)a[np].fa=a[p].son[x];
	else 
	{
		int q=a[p].son[x],nq=++cnt;
		a[nq]=a[q];a[nq].len=a[p].len+1;
		a[q].fa=a[np].fa=nq;
		for(;p&&a[p].son[x]==q;p=a[p].fa)a[p].son[x]=nq;
	}
	last=np;
}
char s[300010];int n;long long ans;
void getright()
{
	for(int i=2;i<=cnt;i++)in[a[i].fa]++;
	int l=0,r=0;
	for(int i=1;i<=cnt;i++)if(!in[i])q[++r]=i;
	while(l<r)
	{
		int x=q[++l];
		rcnt[a[x].fa]+=rcnt[x];
		rmax[a[x].fa]=max(rmax[a[x].fa],rmax[x]);
		if(!--in[a[x].fa])q[++r]=a[x].fa;
	}
}
int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;++i)add(s[i]-'a',i);
	getright();
	int now=1,len=0;
	for(int i=n;i;i--)
	{
		int x=s[i]-'a';
		while(now&&!a[now].son[x])now=a[now].fa,len=a[now].len;
		if(!now)now=1,len=0;
		else now=a[now].son[x],++len;
		if(rmax[now]<i+len)
		{
			if(rmax[now]>=i)ans=max(ans,(long long)rcnt[now]*(rmax[now]-i+1));
			for(int j=a[now].fa;j&&!v[j];j=a[j].fa)
			{
				int t=a[j].len;
				if(rmax[j]<i+t&&rmax[j]>=i)ans=max(ans,(long long)rcnt[j]*(rmax[j]-i+1));
				v[j]=true;
			}
		}
//		printf("%d %lld\n",i,ans);
	}
	printf("%lld\n",ans);
}
