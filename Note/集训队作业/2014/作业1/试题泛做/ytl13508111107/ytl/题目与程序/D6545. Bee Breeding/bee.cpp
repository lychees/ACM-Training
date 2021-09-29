#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int xo[]={-1,-1,0,1,1,0};
const int yo[]={0,1,1,0,-1,-1};
void trans(int a,int &x,int &y){
	if (a==1) {x=0;y=0;return;}
	int id=1,cir;
	for (cir=0;;cir++){
		id+=cir*6;
		if (a<=id) break;
	}
	id=id-cir*6+1;
	x=cir-1;y=-cir;
	if (id==a) return; 
	for (int i=1;i<=cir-1;i++){
		x+=xo[0];y+=yo[0];
		id++;
		if (id==a) return;
	}
	for (int j=1;j<6;j++)
		for (int i=1;i<=cir;i++){
			x+=xo[j];y+=yo[j];
			id++;
			if (id==a) return;
		}
}
void work(int a,int b){
	int xa,ya,xb,yb,ox,oy;
	trans(a,xa,ya);
	trans(b,xb,yb);
	ox=xa-xb;
	oy=ya-yb;
	printf("The distance between cells %d and %d is %d.\n",a,b,ox*oy>0?abs(ox+oy):max(abs(ox),abs(oy)));
}
int main(){
	freopen("bee.in","r",stdin);
	freopen("bee.out","w",stdout);
	int a,b;
	while (scanf("%d%d",&a,&b)!=EOF&&(a||b)) work(a,b);	
	return 0;
}
