#include <stdio.h>
#include <stdlib.h>
#define p 1000000000
using namespace std;

int n,i,j,k,l,ll,rr,val;
int a[500005],l1[500005],l2[500005];
int ans[1050000],sum[1050000],Max[1050000],Min[1050000],MaxL[1050000],MinL[1050000],L[1050000];
int Maxc[1050000],Minc[1050000],addL[1050000];
int Ans;

void C(int x,int len,int maxc,int minc,int addl)
{
	if(maxc)
	{
		Maxc[x]=maxc;
		Max[x]=(long long)maxc*len%p;
		MaxL[x]=(long long)maxc*L[x]%p;
		sum[x]=(long long)maxc*Min[x]%p;
		ans[x]=(long long)maxc*MinL[x]%p;
	}
	if(minc)
	{
		Minc[x]=minc;
		Min[x]=(long long)minc*len%p;
		MinL[x]=(long long)minc*L[x]%p;
		sum[x]=(long long)minc*Max[x]%p;
		ans[x]=(long long)minc*MaxL[x]%p;
	}
	if(addl)
	{
		addL[x]+=addl;
		L[x]=(L[x]+(long long)len*addl)%p;
		MaxL[x]=(MaxL[x]+(long long)Max[x]*addl)%p;
		MinL[x]=(MinL[x]+(long long)Min[x]*addl)%p;
		ans[x]=(ans[x]+(long long)sum[x]*addl)%p;
	}
}

void Down(int x,int len)
{
	C(x<<1,len,Maxc[x],Minc[x],addL[x]);
	C(x<<1|1,len,Maxc[x],Minc[x],addL[x]);
	Maxc[x]=Minc[x]=addL[x]=0;
}

void update(int x)
{
	ans[x]=ans[x<<1]+ans[x<<1|1];if(ans[x]>=p)ans[x]-=p;
	sum[x]=sum[x<<1]+sum[x<<1|1];if(sum[x]>=p)sum[x]-=p;
	Max[x]=Max[x<<1]+Max[x<<1|1];if(Max[x]>=p)Max[x]-=p;
	Min[x]=Min[x<<1]+Min[x<<1|1];if(Min[x]>=p)Min[x]-=p;
	MaxL[x]=MaxL[x<<1]+MaxL[x<<1|1];if(MaxL[x]>=p)MaxL[x]-=p;
	MinL[x]=MinL[x<<1]+MinL[x<<1|1];if(MinL[x]>=p)MinL[x]-=p;
	L[x]=L[x<<1]+L[x<<1|1];if(L[x]>=p)L[x]-=p;
}

void Cmax(int x,int l,int r)
{
	if(l>=ll&&r<=rr)
	{
		C(x,r-l+1,val,0,0);
		return;
	}
	int mid=l+r>>1;
	Down(x,r-mid);
	if(rr<=mid)Cmax(x<<1,l,mid);
	else if(ll>mid)Cmax(x<<1|1,mid+1,r);
		else Cmax(x<<1,l,mid),Cmax(x<<1|1,mid+1,r);
	update(x);
}

void Cmin(int x,int l,int r)
{
	if(l>=ll&&r<=rr)
	{
		C(x,r-l+1,0,val,0);
		return;
	}
	int mid=l+r>>1;
	Down(x,r-mid);
	if(rr<=mid)Cmin(x<<1,l,mid);
	else if(ll>mid)Cmin(x<<1|1,mid+1,r);
		else Cmin(x<<1,l,mid),Cmin(x<<1|1,mid+1,r);
	update(x);
}

void CL(int x,int l,int r)
{
	if(l>=ll&&r<=rr)
	{
		C(x,r-l+1,0,0,1);
		return;
	}
	int mid=l+r>>1;
	Down(x,r-mid);
	if(rr<=mid)CL(x<<1,l,mid);
	else if(ll>mid)CL(x<<1|1,mid+1,r);
		else CL(x<<1,l,mid),CL(x<<1|1,mid+1,r);
	update(x);
}

char ch;
void read(int &x)
{
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
}

int main()
{
	scanf("%d",&n);
	for(l=1;l<n;l*=2);
	for(i=1;i<=n;++i)read(a[i]);
	l1[1]=l2[1]=1;
	for(i=2;i<=n;++i)
	{
		for(j=i-1;j;j=l1[j]-1)if(a[j]<a[i])break;
		l1[i]=j+1;
		for(j=i-1;j;j=l2[j]-1)if(a[j]>a[i])break;
		l2[i]=j+1;
	}
	for(i=1;i<=n;++i)
	{
		ll=l1[i];rr=i;val=a[i];Cmin(1,1,l);
		ll=l2[i];rr=i;val=a[i];Cmax(1,1,l);
		ll=1;rr=i;CL(1,1,l);
		Ans+=ans[1];if(Ans>=p)Ans-=p;
	}
	printf("%d\n",Ans);
}
