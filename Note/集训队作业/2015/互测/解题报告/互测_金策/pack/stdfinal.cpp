#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<bitset>
#include<ctime>
#define MAXN 2016
using namespace std;
int n,m;
class bs{
#define SZ 64
	private:
		unsigned int a[SZ];
	public:
		bs operator^(const bs&y)const{
			bs tmp;
			for (int i=0;i<SZ;i++)tmp.a[i]=a[i]^y.a[i];
			return tmp;
		}
		void operator^=(const bs&y){
			for (int i=0;i<SZ;i++)a[i]^=y.a[i];
		}
		bs operator&(const bs&y)const{
			bs tmp;
			for (int i=0;i<SZ;i++)tmp.a[i]=a[i]&y.a[i];
			return tmp;
		}
		bool operator[](const int x)const{
			return (a[x>>5]>>(x&31))&1;
		}
		void set(int pos,int v){
			((a[pos>>5]>>(pos&31))&1)^v?a[pos>>5]^=1<<(pos&31):0;
		}
		bool none()const{
			for (int i=0;i<SZ;i++)if(a[i])return 0;
			return 1;
		}
		void clear(){
			memset(a,0,sizeof(a));
		}
		bool count()const{
			unsigned int t=0;
			for (int i=0;i<SZ;i++)t^=a[i];
			t=(t>>16)^(t&0xffff);
			t=(t>>8)^(t&0xff);
			t=(t>>4)^(t&0xf);
			t=(t>>2)^(t&0x3);
			return (t>>1)^(t&1);
		}
};

bs r[MAXN];
bs a[MAXN],p[MAXN];
int pv[MAXN];
bs tmp;
void queans(){
	tmp.clear();
	for (int j=0;j<m;j++){
		if(pv[j] && !tmp[j])tmp^=a[pv[j]];
		putchar(tmp[j]+'0');
	}
	putchar('\n');
}
bs aff;
void chg(const bs&pos,const bs&v,int tp=0){
	if(v.none())return;
	int id;for (int i=0;i<m;i++)if(v[i]){id=i;break;}
	if(tp){
		for (int i=1;i<=n;i++)aff.set(i,p[i][tp]);
	}else for (int i=1;i<=n;i++)aff.set(i,(p[i]&pos).count()&1);
	for (int i=id-1;i>=0;i--)if(pv[i] && aff[pv[i]])a[pv[i]]^=v;
	int j=pv[id];pv[id]=0;
	int mi=0,lo;
	for (int i=1;i<=n;i++)if(aff[i] && a[i].none()){
		pv[id]=mi=i,lo=m;
		break;
	}
	if(!mi){
		for (int i=m-1;i>id;i--)if(pv[i] && aff[pv[i]]){
			pv[id]=mi=pv[i];
			pv[i]=0;
			lo=i;
			break;
		}
	} else for (int i=mi+1;i<=n;i++)if(aff[i] && a[i].none())p[i]^=p[mi];
	if(mi){
		for (int i=lo-1;i>id;i--)if(pv[i] && aff[pv[i]]){
			a[pv[i]]^=a[mi];
			p[pv[i]]^=p[mi];
		}
		a[mi]^=v;
	}
	if(j){
		if(aff[j])a[j]^=v;
		for (int i=0;i<m;i++)if(a[j][i]){
			if(!pv[i]){
				pv[i]=j;
				break;
			}else{
				a[j]^=a[pv[i]];
				p[j]^=p[pv[i]];
			}
		}
	}
}
//
bs ca,va;
int fa[MAXN];
void cut(int x){
	if(fa[x]==x)return;
	int f=fa[x];
	chg(ca,r[f],x);
	for (int i=x;fa[i]==f;i++)fa[i]=x;
}
int main(){
	freopen("me.in","r",stdin);
	freopen("right.out","w",stdout);
	int q;
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n;i++)p[i].set(i,1);
	ca.clear();
	for (int i=1;i<=n;i++){
		for (int j=0;j<m;j++){
			char c;while((c=getchar())<'0'||c>'1');
			r[i].set(j,c-'0');
		}
		chg(ca,r[i],i);
	}
	for (int i=1;i<=n;i++)fa[i]=i;fa[n+1]=n+1;
	while(q--){
		int opt;scanf("%d",&opt);
		if(opt==3){
			queans();
		}else{
			int x,y;
			scanf("%d%d",&x,&y);
			for (int j=0;j<m;j++){
				char c;while((c=getchar())<'0'||c>'1');
				va.set(j,c-'0');
			}
			cut(x);cut(y+1);
			if(opt==1){
				for (int j=x;j<=y;j++){
					r[j]^=va;
					if(fa[j]==j)ca.set(j,1);
				}
				chg(ca,va);
				ca.clear();
			}else{
				for (int j=x;j<=y;j++){
					if(fa[j]==j)chg(ca,(j==x?(r[j]^va):r[j]),j);
					fa[j]=x;
					r[j]=va;
				}
			}
		}
	}
	return 0;
}



