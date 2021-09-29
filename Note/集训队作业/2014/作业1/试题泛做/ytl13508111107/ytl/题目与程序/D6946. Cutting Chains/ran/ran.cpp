#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int minn=1,maxn=15,T=10,n,m;

int rand(int x){
	return rand()*rand()%x;
}

void work(){
	n=minn+rand(maxn-minn+1);m=rand(n*n);
	printf("%d  ",n);
	for (int i=1;i<=m;i++){
		int a,b;
		do{
			a=rand(n)+1,b=rand(n)+1;
		}while (a==b);
		printf("%d %d  ",a,b);
	}
	printf("-1 -1\n");
}
int main(){
	freopen("cutting.in","w",stdout);
	for (int i=1;i<=T;i++) work();	
	printf("0\n");
	return 0;
}
