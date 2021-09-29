#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
long long K;
int x[60][60],n=28,m=21;
int main(){	
	int t; scanf("%d",&t);
	for (;t;t--){
		scanf("%I64d",&K);
		memset(x,0x00,sizeof x);
		for (int i=1;i<=8;i++)
			for (int j=1;j<=8;j++) x[i][j]=1;
		int num=0;
		while (K){
			int k1=K%8; num++; 
			for (int i=1;i<=k1;i++) x[i][8+num]=1;
			K/=8;
		}
		for (int i=9;i<n;i++) x[i][i+1]=1;
		printf("%d %d\n",n,m);
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++) putchar(x[i][j]+'0'); cout<<endl;
		}
	}
	return 0;
}
