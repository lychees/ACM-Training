#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
typedef unsigned long long u64;
const int N=18,mod=4186183,g=5;
int n,k;
int q[1<<N],cnt[mod],gi[mod];

inline int get() {
	char ch;
	while (!isdigit(ch=getchar()));
	int v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return v;
}

int main() {
	n=1<<get(); k=get()%(mod-1);
	for (int i=0;i<n;i++) q[i]=get();
	cnt[gi[0]=mod-1]=1;
	for (int i=0,c=1,j=0;i<mod-1;i++) {
		gi[c]=i;
		c=c*g%mod;
		++cnt[j];
		if ((j+=k)>=mod-1) j-=mod-1;
	}
	for (int d=1;d<n;d<<=1)
		for (int i=0;i<n;i+=d<<1)
			for (int j=i;j<i+d;j++)
				if ((q[j]+=q[j+d])>=mod)
					q[j]-=mod;
	int ans=1;
	for (int i=0;i<n;i++)
		ans=u64(ans)*cnt[gi[q[i]]]%mod;
	cout<<ans<<endl;
	return 0;
}
