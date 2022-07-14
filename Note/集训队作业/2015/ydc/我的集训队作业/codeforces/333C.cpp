#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<ctime>
#include<bitset>
#define maxn 10010
#define maxm 300010
using namespace std;
int sola[maxn][4],solb[maxn][4];
int n,m,cnt1,cnt2;
int use[maxn],id;
bool Insert(int p)
{
	if(use[p]==id)
		return false;
	use[p]=id;
	return true;
}
void calc(int p,int k,int v[])
{
	for(int i=1;i<=k;i++)
		v[k-i+1]=p%10,p/=10;
}
void FindDivisor(int a,int sol[maxn][4],int &cnt)
{
	static int digit[10];
	++id;
	for(int i=1;i<=9;i++)
		if(a%i==0)
			for(int j=1;j<=9;j++)
				if(a/i%j==0)
					for(int k=1;k<=9;k++)
						if(a/(i*j)%k==0)
						{
							int h=a/(i*j);
							if(Insert(i*1000+j*100+k*10+h))
							{
								cnt++;
								sol[cnt][0]=i,sol[cnt][1]=j,sol[cnt][2]=k,sol[cnt][3]=h;
							}
						}
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			for(int k=1;k<=9;k++)
				for(int h=1;h<=9;h++)
					if((i+j)*(k+h)==a||i*j+k+h==a||i*j*k+h==a)
						if(Insert(i*1000+j*100+k*10+h))
						{
							cnt++;
							sol[cnt][0]=i,sol[cnt][1]=j,sol[cnt][2]=k,sol[cnt][3]=h;
						}
	for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
					for(int k=1;k<=99;k++)
						if(i*j*k==a||i+j+k==a||abs(i+j-k)==a)
						{
							if(Insert(i*1000+j*100+k))
							{
								cnt++;
								sol[cnt][0]=i,sol[cnt][1]=j;
								sol[cnt][2]=digit[1],sol[cnt][3]=digit[2];
							}
							if(Insert(i*1000+k*10+j))
							{
								cnt++;
								sol[cnt][0]=i;
								calc(k,2,digit);
								sol[cnt][1]=digit[1],sol[cnt][2]=digit[2],sol[cnt][3]=j;
							}
							if(Insert(k*100+i*10+j))
							{
								cnt++;
								calc(k,2,digit);
								sol[cnt][0]=digit[1],sol[cnt][1]=digit[2],sol[cnt][2]=i,sol[cnt][3]=j;
							}
						}
	for(int i=1;i<=99;i++)
			for(int j=1;j<=99;j++)
				if(i*j==a||i+j==a||abs(i-j)==a)
				{
					if(Insert(i*100+j))
					{
						cnt++;
						calc(i,2,digit);
						sol[cnt][0]=digit[1],sol[cnt][1]=digit[2];
						calc(j,2,digit);
						sol[cnt][2]=digit[1],sol[cnt][3]=digit[2];
					}
				}
	for(int i=1;i<=9;i++)
			for(int j=1;j<=999;j++)
				if(i*j==a||i+j==a)
				{
					if(Insert(i*1000+j))
					{
						cnt++;
						sol[cnt][0]=i;
						calc(j,3,digit);
						sol[cnt][1]=digit[1],sol[cnt][2]=digit[2],sol[cnt][3]=digit[3];
					}
					if(Insert(j+i))
					{
						cnt++;
						calc(j,3,digit);
						sol[cnt][0]=digit[1],sol[cnt][1]=digit[2],sol[cnt][2]=digit[3],sol[cnt][3]=i;
					}
					break;
				}
	if(Insert(a))
	{
		cnt++;
		calc(a,4,digit);
		sol[cnt][0]=digit[1],sol[cnt][1]=digit[2],sol[cnt][2]=digit[3],sol[cnt][3]=digit[4];
	}
}
bool hash[100000010];
void Find(int a,int b)
{
	if(m==0)
		return ;
	cnt1=0,cnt2=0;
	FindDivisor(a,sola,cnt1);
	FindDivisor(b,solb,cnt2);
	for(int i=1;i<=cnt1;i++)
		for(int j=1;j<=cnt2;j++)
		{
			int ans=0;
			for(int k=0;k<4;k++)
				ans=ans*10+sola[i][k];
			for(int k=0;k<4;k++)
				ans=ans*10+solb[j][k];
			if(hash[ans]!=0)
				continue;
			m--;
			printf("%08d\n",ans);
			hash[ans]=1;
			if(m==0)
				return ;
		}
}
void work()
{
	for(int i=1;i<=9999;i++)
		Find(i,abs(n-i));
	for(int i=1;i<=9999;i++)
		if(n%i==0&&n/i!=n-i)
			Find(i,n/i);
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d",&n,&m);
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
