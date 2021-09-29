//By ytl 2013-11-15
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 1005
using namespace std;

void print(char a[],int n){
	for (int i=1;i<=n;i++) printf("%d",a[i]);
	printf("\n");
}

char a[N],b[N];
int lena,lenb,t1,t2;

void trans(char x,char &t1,char &t2,char &t3,char &t4){
	if (x>='0'&&x<='9') x=x-'0';
	else x=x-'A'+10;
	t1=(x&8)>>3;
	t2=(x&4)>>2;
	t3=(x&2)>>1;
	t4=x&1;
}
void read(char a[],int &len){
	len=0;
	char c=getchar();
	while (c<=32) c=getchar();
	trans(c,a[1],a[2],a[3],a[4]);
	int t=1;
	while (a[t]==0) t++;
	t++;
	for (int i=t;i<=4;i++) a[i-t+1]=a[i];
	len=4-t+1;
	c=getchar();
	while (c>32){
		trans(c,a[len+1],a[len+2],a[len+3],a[len+4]);
		len+=4;
		c=getchar();		
	}
}
string run(int level,int k){
	if (k==1){
		if (b[t2]==1){
			t2+=2;
		}else{
			t2++;
			for (int i=1;i<=4;i++)
				run(level+1,1);
		}	
		return "";
	}
	if (k==2){
		if (a[t1]==1){
			t1+=2;
		}else{
			t1++;
			for (int i=1;i<=4;i++) 
				run(level+1,2);
		}
		return "";
	}
	if (a[t1]==1){
		t1+=2;
		int l=t2;
		run(level,1);
		if (a[t1-1]==0) return "10";
		string c="";
		for (int i=l;i<t2;i++) c+=(b[i]+'0');
		return c;
	}
	if (b[t2]==1){
		t2+=2;
		int l=t1;
		run(level,2);
		if (b[t2-1]==0) return "10";
		string c="";
		for (int i=l;i<t1;i++) c+=(a[i]+'0');
		return c;		
	}
	t1++;t2++;
	string d1,d2,d3,d4;
	d1=run(level+1,0);
	d2=run(level+1,0);
	d3=run(level+1,0);
	d4=run(level+1,0);
	if (d1=="10"&&d2=="10"&&d3=="10"&&d4=="10") return "10";
	return "0"+d1+d2+d3+d4;
}
int main(){
	freopen("image.in","r",stdin);
	freopen("image.out","w",stdout);
	read(a,lena);
	read(b,lenb);
	t1=t2=1;
	string ans="1"+run(1,0);
	int len=ans.size();
	while (len%4!=0){
		ans="0"+ans;
		len++;
	}
	for (int i=0;i<len;i+=4){
		int x=0;
		for (int j=0;j<4;j++)
			x=(x<<1)|int(ans[i+j]-'0');
		printf("%c",x<10?x+'0':x-10+'A');
	}
	return 0;
}
