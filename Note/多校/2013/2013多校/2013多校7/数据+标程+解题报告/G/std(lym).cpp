#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

char player1[111];
char player2[111];
int sg[23333];
int stones[111111];
int b[111];

int main(void)
{
	int T = 0, n, m;
	while(scanf("%d%d%s%s",&n,&m,player1,player2) != EOF)
	{
		for(int i = 0;i < n;i++) scanf("%d",&stones[i]);
		for(int i = 0;i < m;i++) scanf("%d",&b[i]);
		
		int mx = *max_element(b,b+m);
		int mn = *min_element(b,b+m);
		int base = mx*mx;
		int limit = base+mn+5;
		memset(sg,-1,sizeof(int)*(limit+10));
		sg[0] = 0;
		for(int i = 0;i < m;i++)
		{
			int x = b[i];
			for(int j = 0;j <= limit;j++)
			{
				if(sg[j] < 0) continue;
				if(x+j <= limit && sg[x+j] < sg[j]+1) sg[x+j] = sg[j]+1;
			}
		}
		
		//for(int i = 0;i <= limit;i++) printf("sg[%d] = %d\n",i,sg[i]);
		
		bool fail = false;
		int result = 0;
		for(int i = 0;i < n;i++)
		{
			if(stones[i] <= limit)
			{
				if(sg[stones[i]] < 0) fail = true;
				else result ^= sg[stones[i]];
			}
			else
			{
				int down = (stones[i] - base)/mn*mn;
				if(sg[stones[i]-down] < 0) fail = true;
				else result ^= down/mn + sg[stones[i]-down];
			}
		}
		if(fail) puts(player2);
		else puts(result ? player1 : player2);
		//else printf("%d\n",result);
	}
	while(getchar() != EOF);
	return 0;
}
