#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=500;
int n,d[maxn],a[maxn],ll[maxn];
char list[500];
void add()
{
	for(int i=0;i<400;i++)
		list[i]='*';
	list[1]='0';
	list[17]='1';
	list[9]='2';
	list[24]='3';
	list[5]='4';
	list[20]='5';
	list[12]='6';
	list[3]='7';
	list[18]='8';
	list[16]='9';
	list[4]='-';
	list[6]='&';
}

char ans[500];
int tot;
bool cherkC(int n,int C){
	int i,ret=0;
	for(i=1;i<=n;i++)
	{  
		int temp;
		if(ans[i]>='0'&&ans[i]<='9') temp=ans[i]-'0';
		else temp=10;
		ret+=((n-i)%10+1)*temp; 
		ret%=11;
	}
	ret%=11; 
	if(ret==C)
		return 1;
	return 0;
}
bool cherkK(int n,int K){
	int i,ret=0;
	for(i=1;i<=n;i++)
	{
		int temp;
		if(ans[i]>='0'&&ans[i]<='9') temp=ans[i]-'0';
		else temp=10;
		ret+=((n-i)%9+1)*temp;
		ret%=11;
	}
	ret%=11;
	if(ret==K) return 1;
	return 0;
}
int query()
{
	int i,j,ret=0;
	i=1;
	tot=0;
	while(i<=n)
	{
		for(j=0;j<5;j++)
		{
			ret*=2;
			if(d[i]==1)
				ret+=1;			
			i++;
		}
		if(list[ret]=='*')
			return 0;
		if(i<=n&&d[i]==1) return 0;
		ans[tot++]=list[ret];
		ret=0;
		i++;
	}
		
	if(ans[0]!='&'||ans[tot-1]!='&') return 0;
	
	int ss;
	if(ans[tot-3]=='&') return 0;
	if(ans[tot-3]=='-')
		ss=10;
	else ss=ans[tot-3]-'0';
	if(!cherkC(tot-4,ss)) return 1;
	if(ans[tot-2]=='&') return 0;
	if(ans[tot-2]=='-')
		ss=10;
	else ss=ans[tot-2]-'0';
	if(!cherkK(tot-3,ss)) return 2;
	return 3;
}

double Abs(double x){
	return x<0?-x:x;
}
bool cherk(double w)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(Abs(a[i]-w)*20<=w+1e-6) d[i]=0;
		else if(Abs(a[i]-2*w)*10<=w+1e-6) d[i]=1;
		else return 0;
	}
	return 1;
}

int main()
{
    freopen("code.in","r",stdin);
    freopen("bc.out","w",stdout);
	int i,j,cas=0;
	add();
	while(scanf("%d",&n)!=-1)
	{
		if(!n) break;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}

	//	printf("Case %d: ",++cas);

		if(n/6<3||(n-5)%6!=0) 
		{
			puts("bad code");
			continue;
		}

		for(i=1;i<=n;i++)
		{
			double w;
			w=a[i];
			if(cherk(w)) break;
			w=a[i]/0.95;
			if(cherk(w)) break;
			w=a[i]/1.05;
			if(cherk(w)) break;
		}

		if(i>n) 
		{
			puts("bad code");
			continue;
		}
		
		int tt=query();
		if(tt==3)
		{
			for(i=1;i<=tot-4;i++)
				printf("%c",ans[i]);
			puts("");
			continue;
		}
		
		for(i=1;i*2<=n;i++)
			swap(d[i],d[n-i+1]);

		tt=max(tt,query());
		if(tt==3)
		{
			for(i=1;i<=tot-4;i++)
				printf("%c",ans[i]);
			puts("");
			continue;
		}
		else if(tt==2) puts("bad K");
		else if(tt==1) puts("bad C");
		else puts("bad code");
	}
	return 0;
}
