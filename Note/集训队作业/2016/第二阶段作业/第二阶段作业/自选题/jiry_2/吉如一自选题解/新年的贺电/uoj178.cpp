#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
char ch[20000];
unsigned int w[2000];
int f[2000],n,a[2000],tot,fir,Q,ans[2000],pd[10],sign;
void print(int k){
	//cout<<"print "<<k<<endl;
	int A[20],len=10;
	memset(A,0x00,sizeof A);
	for (int i=1;i<=10;i++)
		if (k&(1<<i-1)) A[i]=1;
	tot+=10;
	for (int i=10;i>=1;i--) putchar(A[i]+'0');
}
void print(int k1,int k2){
	int A[20],len=0;
	memset(A,0x00,sizeof A);
	while (k1){
		len++; A[len]=k1&1; k1>>=1;
	}
	len=max(len,k2);
	tot+=len+1;
	if (len>k2) tot+=len-k2;
	for (int i=k2+1;i<=len;i++) putchar('0'); 
	putchar('1');
	for (int i=len;i;i--) putchar(A[i]+'0');
}
int calc(unsigned int K){
	int num=0; while (K) num+=(K&1),K>>=1; return num;
}
int calc2(unsigned int K){
	int num=0; while (K) num^=(K&7),K>>=3; return num;
}
void get(int l,int r){
	if (r-l+1==8){
		int k1=(rand()<<16)+rand(),ti=1,lim=7;
		while (1){
			sign++; int flag=0;
			for (int i=l;i<=r;i++) pd[calc2(w[a[i]]&k1)]=sign;
			for (int i=0;i<8;i++) if (pd[i]!=sign) flag=1;
			if (flag){
				ti++; k1=(rand()<<16)+rand(); continue;
			}
			break;
		}
		print(ti,lim);
		for (int i=0;i<8;i++)
			for (int j=l;j<=r;j++) if (calc2(w[a[j]]&k1)==i) print(f[a[j]]);
		return;
	}
	int len=r-l+1; int k1=rand(),ti=1,lim=0;
	while ((1<<lim)!=len) lim++; lim=(lim+2)/2;
	while (1){
		int num=0;
		for (int i=l;i<=r;i++){
			int k3=calc(w[a[i]]&k1)%2;
			if (k3==0) num++;
		}
		if (num!=len/2){
			ti++; k1=rand(); continue;
		}
		int now=l;
		for (int i=l;i<=r;i++){
			int k3=calc(w[a[i]]&k1)%2;
			if (k3==0) swap(a[i],a[now]),now++;
		}
		break;
	}
	//cout<<endl<<ti<<" "<<k1<<endl;
	print(ti,lim); int mid=l+r>>1;
	get(l,mid); get(mid+1,r);
}
void solve1(){
	srand(233);
	n=1024; for (int i=1;i<=n;i++) scanf("%u%d",&w[i],&f[i]);
	for (int i=1;i<=n;i++) a[i]=i;
	get(1,n); putchar('\n');
}
int getin(){
	return ch[++fir]-'0';
}
int readint(){
	int now=0;
	for (int i=1;i<=10;i++) now=now*2+getin();
	return now;
}
int readint(int lim){
	while (getin()!=1) lim++;
	int now=0;
	for (int i=1;i<=lim;i++) now=now*2+getin();
	return now;
}
void solve(int l,int r,int L,int R){
//cout<<"solve "<<l<<" "<<r<<" "<<L<<" "<<R<<endl;
	if (r-l+1==8){
		int ti=readint(7);
		for (int i=0;i<8;i++) pd[i]=readint();
		int k1=0;
		for (int i=1;i<=ti;i++) k1=(rand()<<16)+rand();
		for (int i=L;i<=R;i++) ans[a[i]]=pd[calc2(w[a[i]]&k1)];
		return;
	}
	int lim=0,len=r-l+1;
	while ((1<<lim)!=len) lim++; lim=(lim+2)/2;
	int ti=readint(lim),k1=0;
	for (int i=1;i<=ti;i++) k1=rand();
//	cout<<ti<<" "<<k1<<endl;
	int now=L;
	for (int i=L;i<=R;i++){
		int k3=calc(w[a[i]]&k1)%2;
		if (k3==0) swap(a[i],a[now]),now++;
	}
	int mid=(l+r)>>1;
	solve(l,mid,L,now-1);
	solve(mid+1,r,now,R);
}
void solve2(){
	scanf("%s",ch+1); fir=0; n=1024;
	scanf("%d",&Q); srand(233);
	for (int i=1;i<=Q;i++) scanf("%u",&w[i]);
	for (int i=1;i<=Q;i++) a[i]=i;
	solve(1,n,1,Q);
	for (int i=1;i<=Q;i++) printf("%d\n",ans[i]);
}
int main(){
//	freopen("decode.in","r",stdin);
//	freopen("decode.out","w",stdout);
	scanf("%s",ch+1);
	if (ch[1]=='e') solve1(); else solve2();
	return 0;
}
