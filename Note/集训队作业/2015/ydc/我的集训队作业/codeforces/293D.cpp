#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 100010
#define maxm 2000010
#define eps 1e-13
using namespace std;
typedef long long LL;
typedef long double ld;
int dcmp(ld p)
{
	if(abs(p)<eps)
		return 0;
	return p>eps?1:-1;
}
vector<ld> L[maxm];
int n;
void read()
{
	scanf("%d",&n);
	static LL x[maxn],y[maxn];
	for(int i=1;i<=n;++i)
	{
		cin>>x[i]>>y[i];
		x[i]+=1000001,y[i]+=1000001;
	}
	for(int i=1;i<=n;++i)
	{
		if(x[i]==x[i%n+1])
			L[x[i]].push_back(y[i]),L[x[i]].push_back(y[i%n+1]);
		else
		{
			ld k=1.0*(y[i%n+1]-y[i])/(x[i%n+1]-x[i]),b=y[i]-x[i]*k;
			for(int j=min(x[i],x[i%n+1]);j<=max(x[i],x[i%n+1]);++j)
			{
				ld vy=k*j+b;
				if(dcmp(k)>=0)
					L[j].push_back(vy);
				else
					L[j].push_back(vy);
			}
		}
	}
}
LL sum2(int n)
{
	LL a=n,b=n+1,c=2*n+1;
	if(a%2==0)
		a/=2;
	else
		b/=2;
	if(a%3==0)
		a/=3;
	else if(b%3==0)
		b/=3;
	else
		c/=3;
	return a*b*c;
}
ld work()
{
	LL total=0;
	for(int i=1;i<=2000005;++i)
		if(L[i].size()>1u)
		{
			sort(L[i].begin(),L[i].end());
			L[i].resize(unique(L[i].begin(),L[i].end())-L[i].begin());
			if(L[i].size()>1u)
			{
				LL l=ceil(L[i][0]-eps),r=floor(L[i][L[i].size()-1u]+eps);
				total+=r-l+1;
			}
			else if(L[i].size())
				++total;
		}
	ld sumx1=0,sumy1=0,sumx2=0,sumy2=0,v=1.0/total;
	for(int i=1;i<=2000005;++i)
	{
		if(L[i].size()>1u)
		{
			LL l=ceil(L[i][0]-eps),r=floor(L[i][L[i].size()-1u]+eps);
			sumx1+=v*(r-l+1)*i,sumx2+=v*(r-l+1)*i*i;
			sumy1+=v*(l+r)*(r-l+1)/2,sumy2+=v*(sum2(r)-sum2(l-1));
		}
		else if(L[i].size()==1u)
		{
			LL y=floor(L[i][0]+eps);
			sumx1+=v*i,sumx2+=v*i*i;
			sumy1+=v*y,sumy2+=v*y*y;
		}
	}
	return (sumx2+sumy2-sumx1*sumx1-sumy1*sumy1)/v/(total-1);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%.10f\n",(double)work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
