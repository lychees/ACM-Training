#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#define maxn 150010
using namespace std;
int n,len,h,ans;
int a[maxn],pos[maxn],rank[maxn],b[maxn];
void read()
{
	static int sorted[maxn];
	scanf("%d %d %d",&n,&len,&h);
	for(int i=1;i<=len;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		sorted[i]=a[i];
	}
	sort(sorted+1,sorted+n+1);
	for(int i=1;i<=n;++i)
	{
		rank[i]=lower_bound(sorted+1,sorted+n+1,a[i])-sorted;
		pos[rank[i]]=a[i];
	}
	sort(b+1,b+len+1);
}
inline bool match(int *a,int *b,int l,int r)
{
	static int pre[maxn],next[maxn];
	int n=r-l+1,head=1,tail=n;
	for(int i=1;i<=n;++i)
		pre[i]=i-1,next[i]=i+1;
	for(int i=l,j;i<=r;++i)
	{
		for(j=head;j<=tail;j=next[j])
			if(a[i]+b[j]>=h)
			{
				pre[next[j]]=pre[j],next[pre[j]]=next[j];
				if(j==head)
					head=next[j];
				if(j==tail)
					tail=pre[j];
				break;
			}
		if(j>n)
			return false;
	}
	return true;
}
inline void sort(int *a,int n)
{
	static int sum[maxn];
	int maxh=0;
	for(int i=1;i<=n;++i)
		if(maxh<a[i])
			maxh=a[i];
	for(int i=1;i<=maxh;++i)
		sum[i]=0;
	for(int i=1;i<=n;++i)
		++sum[a[i]];
	int top=0;
	for(int i=1;i<=maxh;++i)
		if(sum[i])
			while(sum[i]--)
				a[++top]=i;
}
void work1()
{
	int lim=(int)sqrt(len);
	static int ta[maxn],tb[maxn],tc[maxn],use[maxn],v[maxn];
	for(int i=1;i*lim-lim+len<=n;++i)
	{
		int sa=0,sb=0,mark=1;
		for(int j=i*lim;j<=n&&j<=i*lim-lim+len;++j)
			ta[++sa]=rank[j];
		sort(ta,sa);
		for(int j=1;j<=sa;++j)
			ta[j]=pos[ta[j]];
		if(ta[1]+b[len]<h)
			continue;
		for(int j=1,k=len;j<=sa;++j)
		{
			for(;k&&ta[j]+b[k]>=h;--k);
			v[j]=++k;
		}
		if(mark==0)
			continue;
		for(int j=sa;j>=1;--j)
		{
			v[j]=max(v[j+1]+1,v[j]);
			use[v[j]]=i;
		}
		if(v[1]>len)
			continue;
		for(int j=1;j<=len;++j)
			if(use[j]!=i)
				tb[++sb]=b[j];
		int front=1,rear=0;
		for(int j=i*lim-lim+1;j<i*lim;++j)
			tc[++rear]=a[j];
		for(int j=i*lim-lim+1,k=j+len-1;j<=i*lim&&j+len-1<=n;++j)
		{
			if(match(tc,tb,front,rear))
				++ans;
			++front,tc[++rear]=a[++k];
		}
	}
}
void work2()
{
	static int s[maxn];
	for(int i=1;i<=n-len+1;++i)
	{
		int top=0;
		for(int j=i;j<=i+len-1;++j)
			s[++top]=a[j];
		sort(s+1,s+top+1);
		bool mark=true;
		for(int j=1;j<=len;++j)
			if(s[j]+b[len-j+1]<h)
			{
				mark=false;
				break;
			}
		ans+=mark;
	}
}
void work()
{
	if(len>(int)sqrt(n))
		work1();
	else
		work2();
}
int main()
{
	read();
	work();
	printf("%d\n",ans);
	return 0;
}
