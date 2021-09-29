#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,ans,res,n,m,z; char ch; multiset<int> s;
struct node{
	int x,y;
	bool operator < (const node &A) const{return y<A.y;}
	void read(){scanf("%d%d%c",&x,&y,&ch); if (ch==':'){scanf("%d",&z); y=y*60+z-840;}}
}a[1005],b[1005];
int main()
{
	while (scanf("%d",&n),n){
		ans=n,res=0; rep(i,n) a[i].read(),res+=a[i].x; sort(a,a+n);
		scanf("%d",&m); rep(i,m) b[i].read(); sort(b,b+m);
		int i=0; s.clear();
		rep(j,m){
			while (i<n && a[i].y<=b[j].y) s.insert(a[i].x),++i;
			multiset<int>::iterator it=s.upper_bound(b[j].x);
			if (it!=s.begin()) --ans,res-=*--it,s.erase(it);
		}
		printf("Trial %d: %d %d\n\n",++Case,ans,res);
	}
	return 0;
}
