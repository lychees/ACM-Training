//By ytl 2013-11-14
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 50
using namespace std;

int a[N],b[N],n,val[N],FLAG;
char trans(int x){
	if (x==1) return '*';
	if (x==2) return '+';
	return '-';
}
void output(){
	for (int i=1;i<a[0];i+=2) printf("%d%c",a[i],trans(a[i+1]));
	printf("%d=\n",a[a[0]]);
}
bool can(){
	if (a[0]<=1) return false;
	memcpy(b,a,sizeof(b));
	int now=2;
	while (now<=b[0]){
		if (b[now]==1){
			b[now+1]*=b[now-1];
			for (int i=now+1;i<=b[0];i++) b[i-2]=b[i];
			b[0]-=2;
		}
		else now+=2;
	}
	now=2;
	while (now<=b[0]){
		if (b[now]==2){
			b[1]+=b[now+1];
		}else{
			b[1]-=b[now+1];
		}
		now+=2;
	}
	return b[1]==2000;
}
void search(int pos,int x){
	if (pos==n+1){
		a[++a[0]]=x;
		if (can()){
			FLAG=1;
			output();
		}
		a[0]--;
		return;
	}
	for (int i=1;i<=3;i++){
		a[++a[0]]=x;
		a[++a[0]]=i;
		search(pos+1,val[pos]);
		a[0]-=2;
	}
	if (x!=0) search(pos+1,x*10+val[pos]);
}
int main(){
	freopen("according.in","r",stdin);
	freopen("according.out","w",stdout);
	char c=getchar();
	while (c!='='){
		val[++n]=c-'0';
		c=getchar();
	}
	search(2,val[1]);	
	if (!FLAG) printf("IMPOSSIBLE\n");
	return 0;
}
