#include<iostream>
int R(int x){return rand()%x+1;}
int main()
{
	freopen("J.in","w",stdout); srand(time(0));
	int T=10;
	while (T--){
		int n=R(100)+1,m=R(n*R(10));
		printf("%d %d\n",n,m);
		while (m--){
			int x=R(n),y=R(n);
//			while (x==y) y=R(n);
			printf("%d %d\n",x,y);
		}
		puts("");
	}
	puts("0 0"); return 0;
}
