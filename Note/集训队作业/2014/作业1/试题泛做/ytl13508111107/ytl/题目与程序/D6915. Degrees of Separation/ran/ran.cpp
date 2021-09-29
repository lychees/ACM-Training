#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#define N 55
using namespace std;

int minn=2,maxn=50,n,m,maxL=6,minL=10,T=10;

set<string> my;
string name[N];
int rand(int x){
	return rand()*rand()%x;
}
void inform(string &a){
	int len=minL+rand(maxL-minL+1);
	do{
		a.clear();
		for (int i=1;i<=len;i++){
			char ch='a';
			if (rand(2)) ch='A';
			ch+=rand(26);
			a+=ch;
		}
	}while (my.find(a)!=my.end());
	my.insert(a);
}
void init(){
	my.clear();
}
void work(){
	init();
	n=minn+rand(maxn-minn+1);m=rand(n*n)+1;
	printf("%d  %d\n",n,m);
	for (int i=1;i<=n;i++) inform(name[i]);
	for (int i=1;i<=m;i++){
		int a,b;
		a=rand(n)+1;b=rand(n)+1;
		cout<<name[a]<<"  "<<name[b]<<"  ";		
	}
	printf("\n");
}
int main(){
	srand(time(NULL));
	freopen("degree.in","w",stdout);
	for (int i=1;i<=T;i++) work();
	printf("0 0\n");
	return 0;
}
