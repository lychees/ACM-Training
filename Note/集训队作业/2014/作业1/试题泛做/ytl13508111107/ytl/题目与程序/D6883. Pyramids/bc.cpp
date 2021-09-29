#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>
#ifndef _GLIBCXX_DEBUG
#define NDEBUG
#endif
#include <cassert>
#include <complex>
#include <set>
using namespace std;
string filename(__FILE__,string(__FILE__).find(".cpp"));
#define PB push_back
#define MP make_pair
#define SIZE(a) ((int)a.size())
#define REP(x,a) for(typeof(a.begin()) x=a.begin();x!=a.end();x++)
#define ACS(a,b) (a?a->b:0)
#define EACS(a,b,c) (a?a->b:c)
#define ft first
#define sd second
const int INF=0x3f3f3f3f;
const long long INFLL=0x3f3f3f3f3f3f3f3fLL;
template<class T>
inline bool tension(T &a,const T &b)
{
	if(b<a){
		a=b;
		return true;
	}
	return false;
}
template<class T>
inline bool relax(T &a,const T &b)
{
	if(a<b){
		a=b;
		return true;
	}
	return false;
}

const int maxc=1000000;
#define maxn 400
int g[maxc+10];
struct NODE
{
	int w,id;
	inline bool operator<(const NODE &b) const
	{
		if(w==b.w){
			return id<b.id;
		}else{
			return w<b.w;
		}
	}
}a[maxn];
int sum,ap;
int p[maxn];
unsigned long long f[maxc+10];
int main()
{

	freopen("pyramids.in","r",stdin);
	freopen("bc.out","w",stdout);		
	int i,j;
	int num=1;
	for(i=2;;i++){
		num+=i*i;
		if(num>maxc) break;
		a[++ap].w=num;
		a[ap].id=i*2+1;
	}
	num=4;
	for(i=4;;i+=2){
		num+=i*i;
		if(num>maxc) break;
		a[++ap].w=num;
		a[ap].id=i*2;
	}
	num=1;
	for(i=3;;i+=2){
		num+=i*i;
		if(num>maxc) break;
		a[++ap].w=num;
		a[ap].id=i*2;
	}
	sort(a+1,a+ap+1);
	
	for(i=1;i<=maxc;i++) g[i]=7;
	g[0]=0;
	
	for(i=1;i<=ap;i++){
		sum+=a[i].w;
		int s=a[i].w;
		int t=min(sum,maxc);
		
		for(j=t;j>=s;j--){
			if(g[j]>=g[j-a[i].w]+1){
				f[j]=f[j-a[i].w]<<10|i;
				g[j]=g[j-a[i].w]+1;
			}
		}
		//cerr<<i<<endl;
	}
	
	int CN=0,c;
	while(scanf("%d",&c)!=EOF){
		if(c==0) break;
		if(g[c]==7){
			printf("impossible\n");
		}else{
			unsigned long long res=f[c];
			while(res){
				int id=res&(~((~0u>>10)<<10));
				if(a[id].id&1){
					printf("%dH ",a[id].id/2);
				}else{
					printf("%dL ",a[id].id/2);
				}
				res>>=10;
			}
			printf("\n");
		}
	}
	return 0;
}
