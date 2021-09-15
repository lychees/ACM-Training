#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxm 20
#define maxn 600000
using namespace std;
int Sa[maxn],rank[maxn],height[maxn],near[maxn];
int l[maxm],r[maxm],pos[maxn],Log[maxn];
int n,m,len,sum[maxn][maxm],F[maxm][maxn];
char str[maxn];
void read()
{
	scanf("%s %d",str+1,&n);
	m=strlen(str+1),len=m;
	for(int i=1;i<=n;++i)
	{
		str[++m]='$';
		scanf("%s %d %d",str+m+1,l+i,r+i);
		for(;str[m];++m)
			pos[m]=i;
		--m;
	}
}
void sort(int *a,int *b,int *c,int n,int m)
{
	static int cnt[maxn];
	memset(cnt,0,sizeof(int)*(m+1));
	for(int i=1;i<=n;++i)
		++cnt[c[i]];
	for(int i=1;i<=m;++i)
		cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;--i)
		b[cnt[c[a[i]]]--]=a[i];
}
void make_Sa(int n)
{
	static int x[maxn],y[maxn];
	for(int i=1;i<=n;++i)
		rank[i]=i,x[i]=str[i];
	sort(rank,Sa,x,n,256);
	rank[Sa[1]]=1;
	for(int i=2;i<=n;++i)
		rank[Sa[i]]=rank[Sa[i-1]]+(x[Sa[i]]!=x[Sa[i-1]]);
	for(int i=1;i<=n;i<<=1)
	{
		for(int j=1;j<=n;++j)
			Sa[j]=j,x[j]=rank[j],y[j]=j+i<=n?rank[j+i]:0;
		sort(Sa,rank,y,n,n),sort(rank,Sa,x,n,n);
		rank[Sa[1]]=1;
		for(int j=2;j<=n;++j)
			rank[Sa[j]]=rank[Sa[j-1]]+(x[Sa[j]]!=x[Sa[j-1]]||y[Sa[j]]!=y[Sa[j-1]]);
		if(rank[Sa[n]]==n)
			return ;
	}
}
void make_Height(int n)
{
	for(int i=1,j=0;i<=n;++i)
	{
		if(j)
			--j;
		if(rank[i]!=1)
			while(str[i+j]==str[Sa[rank[i]-1]+j])
				++j;
		height[rank[i]]=j;
	}
}
int LCP(int a,int b)
{
	++a;
	int h=Log[b-a+1];
	return min(F[h][a],F[h][b-(1<<h)+1]);
}
int calc(int a,int b,int x)
{
	int L,R,l,r,id=rank[a];
	l=1,r=id;
	while(l<r)
	{
		int mid=(l+r)>>1;
		LCP(mid,id)<b-a+1?l=mid+1:r=mid;
	}
	L=l;
	l=id+1,r=m+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		LCP(id,mid)>=b-a+1?l=mid+1:r=mid;
	}
	R=--r;
	return sum[R][x]-sum[L-1][x];
}
int work()
{
	static int tol[maxm],tor[maxm];
	int ans=0;
	for(int i=1;isalpha(str[i]);++i)
	{
		int L=i,R=len+1;
		for(int j=1;j<=n;++j)
		{
			tol[j]=max(tol[j],i),tor[j]=max(tor[j],i);
			while(isalpha(str[tol[j]])&&calc(i,tol[j],j)>=l[j])
				++tol[j];
			while(isalpha(str[tor[j]])&&calc(i,tor[j],j)>r[j])
				++tor[j];
			L=max(L,tor[j]),R=min(R,tol[j]);
		}
		if(near[rank[i]])
			L=max(L,i+LCP(near[rank[i]],rank[i]));
		ans+=max(0,R-L);
	}
	return ans;
}
void Prepare()
{
	for(int i=2;i<=m;++i)
		Log[i]=Log[i-1]+(i==(i&-i));
	for(int i=1;i<=m;++i)
	{
		F[0][i]=height[i];
		for(int j=1;j<=n;++j)
			sum[i][j]=sum[i-1][j];
		++sum[i][pos[Sa[i]]];
		near[i]=Sa[i-1]<=len?i-1:near[i-1];
	}
	for(int i=1;i<=Log[m];++i)
		for(int j=1;j+(1<<i)-1<=m;++j)
			F[i][j]=min(F[i-1][j],F[i-1][j+(1<<(i-1))]);
}
int main()
{
	read();
	make_Sa(m);
	make_Height(m);
	Prepare();
	printf("%d\n",work());
	return 0;
}
