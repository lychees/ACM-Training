#include <iostream>
using namespace std;

int rand(int x){
	return rand()*rand()%x;
}
int main(){
	srand(time(NULL)); 
	freopen("box.in","w",stdout);
	int minn=1,maxn=6,h=1000;
	int n=minn+rand(maxn-minn+1);
	printf("%d\n",n);
	int x1=rand(2*h)-h,x2=rand(2*h)-h,y1=rand(2*h)-h,y2=rand(2*h)-h,z1=rand(2*h)-h,z2=rand(2*h)-h;
	if (x1>x2) swap(x1,x2);
	if (y1>y2) swap(y1,y2);
	if (z1>z2) swap(z1,z2);
	printf("%d %d %d\n%d %d %d\n",x1,y1,z1,x2,y2,z2);
	for (int i=1;i<=n;i++){
		printf("%d %d %d\n",x1+rand(x2-x1+1),y1+rand(y2-y1+1),z1+rand(z2-z1+1));
	}
	return 0;
}
