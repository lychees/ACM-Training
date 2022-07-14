#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 50010
#define mod 1000000007
using namespace std;
typedef long long LL;
struct trie
{
	int son[2],sum[32],size;
	void clear()
	{
		son[0]=son[1]=size=0;
	}
}tree[maxn*32];
int n,a[maxn],tot;
LL m;
inline void Read(int &digit)
{
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	scanf("%d %I64d",&n,&m);
	for(int i=1;i<=n;++i)
		Read(a[i]);
}
LL getsum(LL p)
{
    LL ans=0;
    for(int i=1,now;i<=n;++i)
    {
        int val=0,y=a[i];
        now=1;
        for(int j=30;j>=1;--j)
        {
            int x=y>>(j-1)&1;
            if(!(p>>(j-1)&1))
            {
                int a=tree[now].son[x^1];
                now=tree[now].son[x];
                if(a)
                {
                    ans+=tree[a].size*((LL)val<<j);
                    for(int k=j;k>=1;--k)
                    {
                        if(y>>(k-1)&1)
                            ans+=(LL)(tree[a].size-tree[a].sum[k])<<(k-1);
                        else
                            ans+=(LL)tree[a].sum[k]<<(k-1);
                    }
                }
                val<<=1;
            }
            else
            {
                now=tree[now].son[x^1];
                val=val<<1|1;
            }
            if(now==0)
                break;
        }
	}
	return ans;
}
int work()
{
	tot=1;
	for(int i=1;i<=n;++i)
	{
		int now=1;
		for(int j=30;j>=1;--j)
		{
			int x=a[i]>>(j-1)&1;
			if(!tree[now].son[x])
				tree[now].son[x]=++tot;
			now=tree[now].son[x];
			++tree[now].size;
			for(int k=j;k>=1;--k)
				tree[now].sum[k]+=a[i]>>(k-1)&1;
		}
	}
	static int now[maxn];
	for(int i=1;i<=n;++i)
		now[i]=1;
	LL v=0;
	m*=2;
	for(int i=30;i>=1;--i)
	{
		LL sum=0;
		for(int j=1;j<=n;++j)
        {
            int x=a[j]>>(i-1)&1;
			sum+=tree[tree[now[j]].son[x^1]].size;
        }
		if(sum<m)
		{
			for(int j=1;j<=n;++j)
			{
				int x=a[j]>>(i-1)&1,p=a[j];
				now[j]=tree[now[j]].son[x];
			}
			v<<=1,m-=sum;
		}
		else
		{
			for(int j=1;j<=n;++j)
			{
				int x=a[j]>>(i-1)&1;
				now[j]=tree[now[j]].son[x^1];
			}
			v=v<<1|1;
		}
	}
	return (getsum(v)/2+m/2*v)%mod;
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%d\n",work());
	return 0;
}
