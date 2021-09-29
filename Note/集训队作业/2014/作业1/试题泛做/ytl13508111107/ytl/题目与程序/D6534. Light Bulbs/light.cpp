//By ytl 2013-11-14
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 805
using namespace std;

void print(int a[],int n){
	for (int i=1;i<=n;i++) printf("%d ",a[i]);printf("\n");
}

int n,Tot,x[N],y[N];
namespace HP{
	const int mm=10;
	struct num{
		int e[N];
		num(int x=0):e(){
			for (int i=x;i;i/=mm) e[++e[0]]=i%mm;
			if (!e[0]) e[0]++;
		}
		void read(){
			e[0]=0;
			char c=getchar();
			while (c<=32) c=getchar();
			while (c>32){
				e[++e[0]]=c-'0';
				c=getchar();
			}
			reverse(e+1,e+e[0]+1);
		}
		void print()const{
			for (int i=e[0];i>=1;i--) printf("%d",e[i]);
		}
		void operator += (int k){
			e[1]+=k;
			int i=1;
			while (e[i]>mm){
				e[i+1]+=e[i]/mm;
				e[i]%=mm;
				i++; 
			}
			while (e[e[0]+1]>0) e[0]++;
		}
		void operator *= (int x){
			for (int i=1;i<=e[0];i++) e[i]*=x;
			for (int i=1;i<=e[0];i++){
				e[i+1]+=e[i]/mm;
				e[i]%=mm;
			}
			if (e[e[0]+1]) e[0]++;
		}
		int operator %(int k){
			int x=0;
			for (int i=e[0];i>=1;i--){
				x=x*mm+e[i];
				x%=k;
			}
			return x;
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
	};
	bool operator == (const num &a,const num &b){
		if (a.e[0]!=b.e[0]) return false;
		for (int i=1;i<=a.e[0];i++) if (a.e[i]!=b.e[i]) return false;
		return true;
	}
	inline bool operator < (const num &a,const num &b){
		if (a.e[0]!=b.e[0]) return a.e[0]<b.e[0];
		for (int i=a.e[0];i>=1;i--)
			if (a.e[i]!=b.e[i]) return a.e[i]<b.e[i];
		return false;	
	}
	inline num min(const num &a,const num &b){return a<b?a:b;}

}
using namespace HP;

void trans(num &a,int x[N]){
	for (int i=1;i<=500;i++) x[i]=0;
	x[0]=0;
	while (!(a.e[0]==1&&a.e[1]==0)){
		x[++x[0]]=a%2;
		a/=2;
	}
}

num Ans,a,b;

void run(int a){
	num ans;int tot=0;
	for (int i=1;i<=n;i++) x[i]=0;
	if (a==1){
		tot++;
		ans+=1;
		x[1]=x[2]=1;
	} 
	for (int i=2;i<=n;i++){
		ans*=2;
		if (x[i-1]!=y[i-1]){
			tot++;
			ans+=1;
			x[i-1]^=1;
			x[i]^=1;
			x[i+1]^=1;
		}
	}
	if (x[n]==y[n]&&tot<Tot){
		Tot=tot;
		Ans=ans;
	}
}
int main(){
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	int cas=0;
	while (1){
		Tot=800;
		a.read();b.read();
		if (a==num(0)&&b==num(0)) break;
		trans(a,x);trans(b,y);
		n=max(x[0],y[0]);
		reverse(x+1,x+n+1);
		reverse(y+1,y+n+1);
		for (int i=1;i<=n;i++) y[i]^=x[i];
		run(0);
		run(1);
		if (Tot!=800){
			printf("Case Number %d: ",++cas);
			Ans.print();
			printf("\n");
		}else printf("Case Number %d: impossible\n",++cas);
		printf("\n");
	}
	return 0;
}
