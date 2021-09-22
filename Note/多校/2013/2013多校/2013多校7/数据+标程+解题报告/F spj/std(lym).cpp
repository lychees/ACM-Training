#include <stdio.h>
#include <string.h>

int main(void)
{
//	freopen("1006.in","r",stdin);
//	freopen("10060.out","w",stdout);
	int T = 0, N, M;
	while(scanf("%d %d",&N,&M) != EOF)
	{
		for(int i = 0;i < M;i++)
		{
			int fst = i%N;
			// begin with M%N, (i/N)-th, cyclic.
			int sec = 0;
			int bg = M%N;
			int remain = N;
			if(M%N <= fst) remain--;
			if(i/N < remain-bg) sec = bg + i/N + (bg + i/N >= fst && bg <= fst);
			else
			{
				sec = (i/N-(remain-bg))%(N-1);
				if(sec >= fst) sec++;
			}
			printf("%d %d\n",fst+1,sec+1);
			for(int j = 0;j < N;j++)
			{
				if(j == fst || j == sec) continue;
				printf(" %d",j+1);
			}
			puts("");
		}
	}
//	while(getchar() != EOF);
	return 0;
}
