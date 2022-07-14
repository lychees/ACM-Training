#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define maxm 30
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int P=101;
char str[maxn];
int Log[maxn],cnt[maxn][maxm];
LL total,n,occur[maxn];
bool isGray[maxn][maxm];
ULL hashSum[maxn],power[maxn];
ULL gethash(int l,int r)
{
	return hashSum[r]-hashSum[l-1]*power[r-l+1];
}
int Count(int l,int p,int r)
{
	return cnt[r][p]-cnt[l-1][p];
}
void prepare()
{
	static LL delta[maxn];
	n=strlen(str+1);
	for(int i=2;i<=n+1;++i)
		Log[i]=Log[i-1]+(i==(i&-i));
	power[0]=1;
	for(int i=1;i<=n;++i)
	{
		isGray[i][1]=true;
		hashSum[i]=hashSum[i-1]*P+str[i]-'a';
		++total;
		for(int j=0;j<26;++j)
			cnt[i][j]=cnt[i-1][j];
		++cnt[i][str[i]-'a'];
		power[i]=power[i-1]*P;
	}
	for(int j=2;j<=Log[n+1];++j)
		for(int i=1;i+(1<<j)-2<=n;++i)
		{
			LL l=i,mid=i+(1<<(j-1))-1,r=i+(1<<j)-2;
			if(isGray[l][j-1]&&isGray[mid+1][j-1]&&Count(l,str[mid]-'a',r)==1&&gethash(l,mid-1)==gethash(mid+1,r))
			{
				isGray[l][j]=true;
				total=total+(r-l+1)*(r-l+1);
				delta[l]=delta[i]+(r-l+1)*(r-l+1),delta[r+1]=delta[r+1]-(r-l+1)*(r-l+1);
			}
		}
	for(int i=1;i<=n;++i)
		occur[i]=occur[i-1]+delta[i];
	for(int i=1;i<=n;++i)
		++occur[i];
}
LL work(LL l,LL r,int k,ULL S)
{
	LL d=r-l+1,ans=d*d;
	if(l-1-d>=1&&isGray[l-1-d][k]&&gethash(l-1-d,l-2)==S&&Count(l-1-d,str[l-1]-'a',l-2)==0)
		ans+=work(l-1-d,r,k+1,S*(power[d+1]+1)+power[d]*(str[l-1]-'a'));
	if(r+1+d<=n&&isGray[r+2][k]&&gethash(r+2,r+1+d)==S&&Count(r+2,str[r+1]-'a',r+d+1)==0)
		ans+=work(l,r+d+1,k+1,S*(power[d+1]+1)+power[d]*(str[r+1]-'a'));
	return ans;
}
void work()
{
	LL maxv=total;
	for(int i=1;i<=n;++i)
		for(int j=0;j<26;++j)
			if(str[i]-'a'!=j)
			{
				LL delta=-occur[i];
				delta+=work(i,i,1,j);
				for(int k=1;k<=18;++k)
				{
					int l=i-(1<<k)+1,r=i+(1<<k)-1;
					if(l<1||r>n)
						break;
					if(isGray[l][k]&&isGray[i+1][k]&&gethash(l,i-1)==gethash(i+1,r)&&Count(l,j,r)==0)
						delta+=work(l,r,k+1,gethash(l,i-1)*(power[r-i+1]+1)+power[r-i]*j);
				}
				maxv=max(maxv,delta+total);
			}
	cout<<maxv<<endl;
}
int main()
{
	scanf("%s",str+1);
	prepare();
	work();
	return 0;
}
