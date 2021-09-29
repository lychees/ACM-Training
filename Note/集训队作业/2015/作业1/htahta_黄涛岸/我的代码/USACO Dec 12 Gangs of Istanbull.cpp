#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=1000003;
int tot,n,a[maxn],b[maxn],p,ans;
inline void gmax(int &a,int b){if(a<b)a=b;}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	tot=get(),n=get();
	a[1]=get();
	for(int i=2;i<=n;i++)b[a[i]=get()]=i,gmax(p,a[i]);
	ans=min(a[1]-(tot-a[1])%2,tot-p*2);
	if(ans<=0)return puts("NO"),0;
	tot-=ans,a[1]-=ans;
	printf("YES\n%d\n",ans);
	for(int i=a[1]?1:2,k,j;;)
	{
		for(k=1;k<=a[i];k++)printf("%d\n",i);
		if(b[a[i]]==i)b[a[i]]=0;
		j=i+1;
		for(k=1;k<=a[i];k++)
		{
			tot-=2;
			while(!b[p])p--;
			if(p*2>tot)
			{
				/*int x=b[p];b[p]=0;
				printf("%d\n",x);
				a[x]--,gmax(b[a[x]],x);*/
				int x=b[p];b[p]=0;
				for(tot+=2;k<=a[i];k++)tot-=2,a[x]--,printf("%d\n",x);
				gmax(b[a[x]],x);
			}else
			{
				while(!a[j])j++;
				printf("%d\n",j);
				if(b[a[j]]==j)b[a[j]]=0;
				a[j]--,gmax(b[a[j]],j);
			}
		}
		if(!tot)break;
		for(i=j;!a[i];i++);
	}
	while(ans--)puts("1");
	return 0;
}
