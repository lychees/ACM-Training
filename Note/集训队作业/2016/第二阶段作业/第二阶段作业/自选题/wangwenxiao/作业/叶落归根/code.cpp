#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
typedef unsigned long long u64;
typedef unsigned int u32;
const u64 Maxl=-(1ull<<60);
const int Maxn=103,Maxq=10003,Maxb=103;
int n,q,ans=0,b;
u32 mod;
u32 e[Maxn][Maxn],eb[Maxn][Maxn];
u32 pf[2][Maxn][Maxn],fm[Maxb][Maxn][Maxn];

inline int get() {
	char ch;
	while (!isdigit(ch=getchar()));
	int v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return v;
}

void Mul(u32 (*f)[Maxn],u32 (*a)[Maxn],u32 (*b)[Maxn]) {
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			u64 cur=0;
			for (int k=1;k<=n;k++) {
				cur+=u64(a[i][k])*b[k][j];
				if (cur>=Maxl) cur%=mod;
			}
			f[i][j]=cur%mod;
		}
}

void Calc(u32 (*a)[Maxn],u32 (*b)[Maxn]) {
	for (int i=1;i<=n;i++) {
		u64 cur=0;
		for (int k=1;k<=n;k++) {
			cur+=u64(a[i][k])*b[k][i];
			if (cur>=Maxl) cur%=mod;
		}
		ans^=cur%mod;
	}
}

int main() {
	n=get(); q=get(); mod=get();
	b=max(1,int(sqrt(q)));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			e[i][j]=get()%mod;
	for (int i=1;i<=n;i++)
		fm[0][i][i]=1%mod;
	for (int i=1;i<b;i++)
		Mul(fm[i],fm[i-1],e);
	Mul(eb,fm[b-1],e);
	u32 (*f)[Maxn]=pf[0],(*g)[Maxn]=pf[1];
	for (int i=1;i<=n;i++)
		f[i][i]=1%mod;
	for (int t=1;t<=q;t++) {
		if (t%b==0) {
			swap(f,g);
			Mul(f,g,eb);
		}
		Calc(f,fm[t%b]);
	}
	cout<<ans<<endl;
	return 0;
}