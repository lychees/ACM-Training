#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int MaxP=200*50;
char s[20];
int n,m,i,j,k,P,sum,delta,min;
int list[50][2];
int a[MaxP+1];

int main()
{
	freopen("G.in","r",stdin);
	freopen("std.out","w",stdout);
	while(scanf("%d",&n)&&n)
	{
		sum=0;P=0;
		for(i=0;i<n;i++)
		{
			scanf("%s %d",s,&m);
			if(s[0]=='C')
				continue;
			if(s[0]=='P')
				P+=m;
			else
			{
				if(P&&sum)
				{
					list[sum][0]=2;
					list[sum][1]=P;
					sum++;
				}
				if(s[0]=='I')
					list[sum][0]=0;
				else
					list[sum][0]=1;
				list[sum][1]=m;
				sum++;
				P=0;
			}
		}
		memset(a,0,sizeof(a));
		delta=0;min=0;P=0;
		for(i=0;i<sum;i++)
		{
			if(list[i][0]==0)
				delta+=list[i][1];
			if(list[i][0]==1)
				delta-=list[i][1];
			if(min>delta)
				min=delta;
			if(list[i][0]!=2)
				continue;
			P++;
			for(j=1;j<=list[i][1];j++)
				if(j>delta&&list[i][1]%j==0)
					a[j-delta]++;
		}
		if(P==0)
			printf("SIZE >= %d\n",1-min);
		else
		{
			k=0;
			for(i=1-min;i<=MaxP;i++)
				if(a[i]==P)
				{
					if(k)
						printf(" ");
					k=i;
					printf("%d",k);
				}
			if(!k)
				printf("IMPOSSIBLE");
			printf("\n");
		}
	}
	return 0;
}
