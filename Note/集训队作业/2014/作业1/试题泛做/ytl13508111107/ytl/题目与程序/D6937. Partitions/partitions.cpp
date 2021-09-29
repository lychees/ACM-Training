//By ytl 2013-11-13
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 55
using namespace std;


int n,m;
char a[N][N],b[N][N],c[N][N],d[N][N];

char Or(char a,char b){
	if (a!=' ') return a;
	if (b!=' ') return b;
	return ' ';
}
char And(char a,char b){
	if (a==b) return a;
	return ' ';
}
void read(int &a){
	a=0;char c=getchar();
	while (c<=32) c=getchar();
	while (c>32){
		a=a*10+c-'0';
		c=getchar();
	}
}
bool draw(){
	int tt=0;
	for (int i=2;i<=n;i++){
		for (int j=1;j<2*m+1;j+=2) if (d[i][j]=='|'&&d[i][j+1]==' '){
			int now=j+2,flag=0;
			while (d[i][now]!='|') now+=2;
			
			for (int k=j+1;k<now;k+=2) if (a[i][k]!='_'||b[i][k]!='_') {flag=1;break;}
			if (!flag){
				tt=1;
				for (int k=j+1;k<now;k+=2) d[i][k]='_';
			}
			j=now-2;
		} 
	}
	for (int j=2;j<=2*m;j++){
		for (int i=2;i<=n+1;i++) if (d[i-1][j-1]=='_'&&d[i][j]==' '){
			int now=i,flag=0;
			while (d[now][j-1]!='_') now++;
			for (int k=i;k<=now;k++) if (a[k][j]!='|'||b[k][j]!='|') {flag=1;break;} 
			if (!flag){
				tt=1;
				for (int k=i;k<=now;k++) d[k][j]='|';
			}
			i=now;
		}
	}
	return tt;
}
int main(){
	freopen("partitions.in","r",stdin);
	freopen("partitions.out","w",stdout);
	read(m);read(n);
	int cas=0;
	while (m||n){
		for (int i=1;i<=n+1;i++){
			for (int j=1;j<=2*m+1;j++) a[i][j]=getchar();
			getchar();
			for (int j=1;j<=2*m+1;j++) b[i][j]=getchar();
			scanf("\n");
		}
		for (int i=1;i<=n+1;i++)
			for (int j=1;j<=2*m+1;j++){
				c[i][j]=Or(a[i][j],b[i][j]);
				d[i][j]=' ';
			}
		for (int i=2;i<=n+1;i++) d[i][1]=d[i][2*m+1]='|';
		for (int j=2;j<=2*m;j+=2) d[1][j]=d[n+1][j]='_';	
		while (draw());
		printf("Case %d:\n",++cas);
		for (int i=1;i<=n+1;i++){
			for (int j=1;j<=2*m+1;j++) printf("%c",c[i][j]);
			printf(" ");
			for (int j=1;j<=2*m+1;j++) printf("%c",d[i][j]);
			printf("\n");
		}
		printf("\n");
		read(m);read(n);
	}			
	return 0;
}
