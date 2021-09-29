#include<iostream>
int R(int x){return rand()%x+1;}
int main()
{
	freopen("G.in","w",stdout); srand(time(0));
	int T=10;
	while (T--){
		int n=R(10);
		printf("%d\n",n);
		while (n--){
			int z=R(4);
			if (z==1) printf("IN %d\n",R(20));
			if (z==2) printf("OUT %d\n",R(20));
			if (z==3) printf("COLLECT %d\n",R(200));
			if (z==4) printf("PAY %d\n",R(2000));
		}
	}
	puts("0");
}
