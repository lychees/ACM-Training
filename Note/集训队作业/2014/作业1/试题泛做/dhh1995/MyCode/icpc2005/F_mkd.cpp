#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int R(int x){return rand()%x*2;}
int main()
{
	freopen("F.in","w",stdout); srand(time(0));
	int Case=1000;
	while (Case--){
		int n=10,T=100; printf("%d\n",n);
		rep(i,n){
			int x=R(T),y1=R(T),y2=R(T);
			if (rand()&1) printf("%d %d %d %d\n",x,y1,x,y2);
			else printf("%d %d %d %d\n",y1,x,y2,x);
		}
		printf("%d %d %d %d\n",R(T)+1,R(T)+1,R(T)+1,R(T)+1);
	}
	puts("0");
	return 0;
}
