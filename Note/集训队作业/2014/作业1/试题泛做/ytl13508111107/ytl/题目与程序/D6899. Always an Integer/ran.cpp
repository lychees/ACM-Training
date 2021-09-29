#include <iostream>
using namespace std;

int xi[200],k=10,h=10,tt=100;

int randM(){
	return rand()%h;
	return rand()|(rand()<<15)|((rand()&1)<<30);
}

void work(){
	for (int i=0;i<=100;i++) xi[i]=0;
	for (int i=1;i<=k;i++) xi[rand()%100]=randM();
	printf("(");
	int flag=0;
	for (int i=100;i>=2;i--) if (xi[i]){
		if (xi[i]==1) printf("+n^%d",i);
		else if (xi[i]==-1) printf("-n^%d",i);
		else{
			if (flag&&xi[i]>0) printf("+");
			if (xi[i]<0) printf("-");
			printf("%dn^%d",xi[i],i);
		}
		flag=1;
	}
	if (xi[1]){
		if (xi[1]==1) printf("+n");
		else if (xi[1]==-1) printf("-n");
		else if (xi[1]>0) printf("+%dn",xi[1]);
		else if (xi[1]<0) printf("-%dn",xi[1]);
	}
	if (xi[0]>0) printf("+");
	if (xi[0]<0) printf("-");
	if (xi[0]) printf("%d",xi[0]);
	int x=randM();
	while (!x) x=randM();
	printf(")/%d\n",x);
}
int main(){
	srand(time(NULL));
	freopen("always.in","w",stdout);
	for (int i=1;i<=tt;i++) work();
	printf(".\n");
 	return 0;
}
