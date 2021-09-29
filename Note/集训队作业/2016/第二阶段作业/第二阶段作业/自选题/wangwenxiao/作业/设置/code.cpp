#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
const int Maxn=300005;
int n,m,tot;
int a[Maxn];
LL ans=0;

inline int get() {
	char ch;
	while (!isdigit(ch=getchar()));
	int v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return v;
}

struct Element{
	int *val;
	bool operator <(const Element &rhs)const{
		for (int i=1;i<m;i++)
			if (val[i]!=rhs.val[i])
				return val[i]<rhs.val[i];
		return false;
	}
}e[Maxn];

struct info{
	LL val;
	int i,lv;
	info(LL val,int i,int lv):val(val),i(i),lv(lv){}
	bool operator >(const info &rhs)const{
		return val>rhs.val;
	}
};
priority_queue <info,vector<info>,greater<info> > H;

int main() {
	n=get(); m=get(); tot=get();
	for (int i=1;i<=n;i++) {
		e[i].val=a+(i-1)*m;
		for (int j=0;j<m;j++)
			e[i].val[j]=get();
		sort(e[i].val,e[i].val+m);
		for (int j=m-1;j>=1;j--)
			e[i].val[j]-=e[i].val[j-1];
		ans+=e[i].val[0];
	}
	if (m==1) return cout<<ans<<endl,0;
	sort(e+1,e+n+1);
	--tot;
	H.push(info(ans+e[1].val[1],1,1));
	while (tot--) {	
		info cur=H.top();
		H.pop();
		ans^=cur.val;
		if (cur.lv>0&&cur.i<n)
			H.push(info(cur.val+e[cur.i+1].val[1],cur.i+1,1));
		if (cur.lv+1<m)
			H.push(info(cur.val+e[cur.i].val[cur.lv+1],cur.i,cur.lv+1));
		if (cur.lv==1&&cur.i<n)
			H.push(info(cur.val-e[cur.i].val[1]+e[cur.i+1].val[1],cur.i+1,1));
	}
	cout<<ans<<endl;
	return 0;
}
