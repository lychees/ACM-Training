#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;
#define maxn 101005
#define max2n 201005
typedef __int64 ll;
int wa[maxn],wb[maxn],wv[maxn],WS[maxn],fg[maxn];
#define max(x,y) ((x)>(y)?(x):(y))
int cmp(int *r,int a,int b,int k)
{
    return r[a]==r[b]&&r[a+k]==r[b+k];
}
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++)WS[i]=0;
    for(i=0;i<n;i++)WS[x[i]=r[i]]++;
    for(i=1;i<m;i++)WS[i]+=WS[i-1];
    for(i=n-1;i>=0;i--)sa[--WS[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0;i<n;i++)wv[i]=x[y[i]];
        for(i=0;i<m;i++)WS[i]=0;
        for(i=0;i<n;i++)WS[wv[i]]++;
        for(i=1;i<m;i++)WS[i]+=WS[i-1];
        for(i=n-1;i>=0;i--)sa[--WS[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
        {
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
    }
    return ;
}
int rk[maxn],height[maxn];
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++)rk[sa[i]]=i;
    for(i=0;i<n;height[rk[i++]]=k)
    {
        for(k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];k++);
    }
    return ;
}
int arr[maxn],SA[maxn],q[maxn],LV[maxn];
char str[maxn],ss[5];
int data[2*maxn];
ll c[2*maxn];
int lowbit(int x){return x&(-x);}
ll getsum(int x)
{
	ll r=0;
	while(x>0)
	{
		r+=c[x];
		x-=lowbit(x);
	}
	return r;
}
void up(int x,int v)
{
	while(x<max2n)
	{
		c[x]+=v;
		x+=lowbit(x);
	}
}
const int N = 100005;
struct PP
{
	int a[N],b[N],rk[20][N],sum[20][N],n;
	
	void build(int L,int R,int d)
	{
		if(L==R)return ;
		int mid=(L+R)/2,i,j=L,k=mid+1;
		for(i=L;i<=R;i++)
		{
			if(rk[d][i]<=mid)
			{
				rk[d+1][j++]=rk[d][i];
				sum[d][i]=sum[d][i-1]+1;
			}
			else
			{
				rk[d+1][k++]=rk[d][i];
				sum[d][i]=sum[d][i-1];
			}
		}
		build(L,mid,d+1);
		build(mid+1,R,d+1);
	}
	int k_th(int L,int R,int k)
	{
		int d=0,l=1,r=n,mid;
		while(1)
		{
			if(l==r)return a[b[rk[d][l]]];
			mid=(l+r)/2;
			if(sum[d][l+R-1]-sum[d][l+L-2]>=k)
			{
				L=sum[d][l+L-2]-sum[d][l-1]+1;
				R=sum[d][l+R-1]-sum[d][l-1];
				r=mid;
			}
			else
			{    
				k-=(sum[d][l+R-1]-sum[d][l+L-2]);
				L=L-(sum[d][l+L-2]-sum[d][l-1]);
				R=R-(sum[d][l+R-1]-sum[d][l-1]);
				l=mid+1;
			}
			d++;
		}
	}
}tree;
bool cmpp(int x,int y){if(tree.a[x]==tree.a[y])return x<y;return tree.a[x]<tree.a[y];}
void init(int n)
{
	tree.n=n;
	int i;
	for(i=1;i<=n;i++)
	{
		tree.a[i]=fg[n-2-SA[i-1]];
	}
    for(i=1;i<=n;i++)tree.b[i]=i;
    sort(tree.b+1,tree.b+1+n,cmpp);
    for(i=1;i<=n;i++)tree.rk[0][tree.b[i]]=i;
    tree.build(1,n,0);
}
int main()
{
    int m,n,i,k,ca;
	//for(ca=0;ca<10;ca++)
    while(~scanf("%d%d%d",&n,&m,&k))
	{
		memset(LV,0,sizeof(LV));
		memset(fg,0,sizeof(fg));
		memset(c,0,sizeof(c));
		memset(height,0,sizeof(height));
		
    
		scanf("%s",str);

		for(i=0;i<n;i++)arr[i]=str[i];
    
		for(i=1;i<=m;i++)
		{
			scanf("%d",&data[i]);
			if(data[i]==1)
			{
				scanf("%s",ss);
				str[n]=ss[0];
				fg[n]=i;
				n++;
			}
		}
		for(i=0;i<n;i++)arr[n-1-i]=str[i];
		arr[n]=0;
		for(i=0;i<n;i++)
		{
			LV[i]=n-i;
		}
        
		da(arr,SA,n+1,500);
		calheight(arr,SA,n);
		init(n+1);
		

		height[n+1]=0;
		int t=0,w=1;
		q[0]=n+1;
		for(i=n;i>=0;i--)
		{
			int len=LV[SA[i]];
			while(t<w&&height[q[w-1]]>=height[i])
			{
				if(len>height[q[w-1]])
				{
				  if(q[w-1]-i>=k)
				  {
					  int tp=tree.k_th(i+1,q[w-1],k);
					  up(tp+1,len-height[q[w-1]]);
				  }
				}
				if(len>height[q[w-1]])len=height[q[w-1]];
				w--;
			}
			if(t<w&&len>height[i])
			{
				if(q[w-1]-i>=k)
				{
					int tp=tree.k_th(i+1,q[w-1],k);
					up(tp+1,len-height[i]);
				}
			
			}
			q[w++]=i;
		}
		for(i=1;i<=m;i++)
		{
			if(data[i]==2)
			{
				printf("%I64d\n",getsum(i));
			}
		}
	}
    return 0;
}
