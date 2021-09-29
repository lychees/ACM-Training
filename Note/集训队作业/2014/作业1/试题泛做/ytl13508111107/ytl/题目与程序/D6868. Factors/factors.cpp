#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
typedef map<LL,LL>::iterator it;

map<LL,LL> my;
int ss[305],u[305],all,tot[305];

const int mm=10000;
struct num{
	int e[10];
			num(int x=0):e(){
			for (int i=x;i;i/=mm) e[++e[0]]=i%mm;
			if (!e[0]) e[0]++;//Attention 为0时的处理 
		}
		void operator *= (int x){//x*mm<INF
			for (int i=1;i<=e[0];i++) e[i]*=x;
			for (int i=1;i<=e[0];i++){
				e[i+1]+=e[i]/mm;
				e[i]%=mm;
			}
			while (e[e[0]+1]) e[0]++;
		}
		void print()const{//加大进制 
			printf("%d",e[e[0]]);
			for (int i=e[0]-1;i>=1;i--){
				if (e[i]<1000) printf("0");
				if (e[i]<100) printf("0");
				if (e[i]<10) printf("0");
				printf("%d",e[i]);
			}
		}
		void operator /=(int k){
			int x=0;
			for (int i=e[0];i>=1;i--){
				x=x*mm+e[i];
				e[i]=x/k;
				x%=k;
			}
			while (e[0]>1&&!e[e[0]]) e[0]--;
		}
		LL trans(){
			LL a=0;
			for (int i=e[0];i>=1;i--) a=a*mm+e[i];
			return a;
		}
};
	bool operator < (const num &a,const num &b){
		if (a.e[0]!=b.e[0]) return a.e[0]<b.e[0];
		for (int i=a.e[0];i>=1;i--)
			if (a.e[i]!=b.e[i]) return a.e[i]<b.e[i];
		return false;	
	}
	
num INF;
num X,Y;

bool add(int k){
	num nX=X,nY=Y;
	nX*=ss[k];
	nY*=(all+1);
	nY/=(tot[k]+1);
	if (nY<INF&&nX<INF){
		all++;
		tot[k]++;
		X=nX;Y=nY;
		return true;
	}
	return false;
}
void dec(int k){
	X/=ss[k];
	Y*=tot[k];
	tot[k]--;
	Y/=all;
	all--;
}
void newAns(){
	LL x=X.trans(),y=Y.trans();
	if (x==1) return;
	it i=my.find(y);
	if (i==my.end()||(i->second)>x) my[y]=x;
}
void search(int k){
	newAns();
	int i;
	for (i=1;i<=tot[k-1];i++){
		if (add(k)) search(k+1);
		else break;
	}
	for (int j=i-1;j>=1;j--) dec(k);
}
int main(){
	freopen("factors.in","r",stdin);
	freopen("factors.out","w",stdout);
	INF.e[0]=5;
	INF.e[1]=5808;
	INF.e[2]=5477;
	INF.e[3]=368;
	INF.e[4]=3372;
	INF.e[5]=922;
	for (int i=2;i<300;i++) if (!u[i]){
		ss[++ss[0]]=i;
		for (int j=i+i;j<300;j+=i) u[j]=1;
	}
	all=0;
	X.e[0]=1;X.e[1]=1;Y.e[0]=1;Y.e[1]=1;
	tot[0]=300;
	search(1);
	
	LL a;
	while (scanf("%I64d",&a)!=EOF) printf("%I64d %I64d\n",a,my[a]);
	return 0;
}
