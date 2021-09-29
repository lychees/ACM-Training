//By ytl 2013-11-28
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int LIM;
double X,P,R;

double calc(int A,int B){
	return (pow(R,A)-1)*(A*(1-X)+B)/(pow(R,A+B)-1)-A*(1-X);
}
double ask(int B){
	int l=1,r=LIM,mid;
	while (l<r){
		mid=(l+r)>>1;
		double x1=calc(mid,B);
		double x2=calc(mid+1,B);
		if (x1<x2) l=mid+1;else r=mid;	
	}
	return calc(l,B);
}

double work(){
	int l=1,r=LIM,mid;
	while (l<r){
		mid=(l+r)>>1;
		double x1=ask(mid);
		double x2=ask(mid+1);
		if (x1<x2) l=mid+1;else r=mid;
	}
	return ask(l);
}
int main(){
	freopen("hey.in","r",stdin);
	freopen("hey.out","w",stdout);
	scanf("%lf%lf",&X,&P);
	if (X==0||P==0){
		printf("0\n");
		return 0;
	}
	P/=100;X/=100;
	R=(1-P)/P;
    LIM=(int)(10/log10(R));
	printf("%.10lf",max(0.0,work()));
	return 0;
}
