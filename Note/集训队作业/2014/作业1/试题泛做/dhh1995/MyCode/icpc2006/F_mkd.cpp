#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
bool b[28];
int main()
{
	freopen("F.in","w",stdout); srand(time(0));
	int T=1000,n,R;
	while (T--){
		int n=6,R=rand()%120; if (rand()&1) R=-R;
		rep(i,26) b[i]=0;
		printf("%d %d",n,R);
		rep(i,n){
			int x=rand()%26;
			while (b[x]) x=rand()%26;
			b[x]=1;
			printf(" %c %d",x+65,rand()%115+6);
		}
		puts("");
	}
	puts("0");
	return 0;
}
