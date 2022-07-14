#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
typedef long long LL;
int n,tmp[maxn],N1,N2,C1,C2,Tc;
void read()
{
	cin>>n>>N1>>N2>>C1>>C2>>Tc;
	if(N1>N2)
		swap(N1,N2),swap(C1,C2);
	if(C1<C2)
		C2=C1;
	for(int i=1;i<=n;++i)
		scanf("%d",tmp+i);
}
int calc(int p)
{
	static int rem[maxn],t[maxn],stack[maxn];
	int ans=p*Tc,top=0;
	for(int i=1,j=1,x;i<=n;++i)
	{
		t[i]=tmp[i];
		if(i>=N1)
			stack[++top]=i-N1;
		if(p>=t[i])
			p-=t[i];
		else
		{
			t[i]-=p,p=0;
			while(j+N2<=i&&t[i])
			{
				x=min(rem[j],t[i]),rem[j]-=x,t[i]-=x,ans+=C2*x;
				while(!rem[j]&&j+N2<=i)
					++j;
			}
			while(top&&t[i])
			{
				x=min(rem[stack[top]],t[i]),rem[stack[top]]-=x,t[i]-=x,ans+=C1*x;
				while(!rem[stack[top]]&&top)
					--top;
			}
			if(t[i])
				return 1<<30;
		}
		rem[i]=tmp[i];
	}
	return ans;
}
int binary(int l,int r)
{
	while(l<r)
	{
		int mid=(l+r)>>1;
		calc(mid)>=calc(mid+1)?l=mid+1:r=mid;
	}
	return calc(l);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%d\n",binary(1,n*51));
	fclose(stdin);
	fclose(stdout);
	return 0;
}
