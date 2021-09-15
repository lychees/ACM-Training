#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<ctime>
#define MAXN 20
using namespace std;
typedef long long LL;
int n,m,k;
char choose[MAXN],ans[MAXN],F[MAXN];
LL digit[MAXN][10],now;
const char a[]={"BT"};
void read()
{
	scanf("%d %d %d %s",&n,&m,&k,choose+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=8;j++)
		{
			scanf("%I64d",&digit[i][j]);
			if(j&1)  digit[i][j]++;
		}
}
LL Run(int p,LL now,char a,char b)
{
	if(a=='T'&&b=='T')  return (now*digit[p][1]+digit[p][2])%m;
	if(a=='T'&&b=='B')  return (now*digit[p][3]+digit[p][4])%m;
	if(a=='B'&&b=='T')  return (now*digit[p][5]+digit[p][6])%m;
	if(a=='B'&&b=='B')  return (now*digit[p][7]+digit[p][8])%m;
}
bool DFSCOW(int,LL,char);
bool DFSMAN(int p,LL run)
{
	if(p>n)  return min(run,m-run)<=k;
	int k=rand()&1;
	return DFSCOW(p,run,a[k])||DFSCOW(p,run,a[k^1]);
}
bool DFSCOW(int p,LL run,char now)
{
	int k=rand()&1;
	return DFSMAN(p+1,Run(p,run,now,a[k]))&&DFSMAN(p+1,Run(p,run,now,a[k^1]));
}
int main()
{
	read();
	for(int i=1;i<=n;i++)
	{
		if(DFSCOW(i,now,'B'))
		{
			printf("B");
			now=Run(i,now,'B',choose[i]);
		}
		else
		{
			printf("T");
			now=Run(i,now,'T',choose[i]);
		}
	}
	printf("\n");
	return 0;
}
