#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<bitset>
#include<cassert>
#define cl(a) memset(a,0,sizeof(a))
using namespace std;
typedef long long ll;
typedef double db;
const db pi=3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862;
void gn(int &x){
    int sg=1;char c;while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')sg=-1,x=0;else x=c-'0';
    while((c=getchar())>='0'&&c<='9')x=x*10+c-'0';
    x*=sg;
}
void gn(ll &x){
    int sg=1;char c;while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')sg=-1,x=0;else x=c-'0';
    while((c=getchar())>='0'&&c<='9')x=x*10+c-'0';
    x*=sg;
}
int mo=258280327;
int inf=1000000000;
db eps=1e-6;
//ll inf=1000000000000000000ll;
int qp(int a,ll b){int ans=1;do{if(b&1)ans=1ll*ans*a%mo;a=1ll*a*a%mo;}while(b>>=1);return ans;}
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
#define x1 x192837465
#define x2 x123456789
#define y1 y192837465
#define y2 y123456789
int n;
int te=0;
int sz[133333],pos[133333];
int cur3;
int cur12=0,ho=0;


int lab[133333];
inline void A(int x){
	cout<<"A "<<x<<endl;
	//assert(lab[x]==0);
	lab[x]=te;
	pos[te]=x;
}
inline void M(int x,int y){
	cout<<"M "<<x<<" "<<y<<endl;
	/*assert(lab[x]);
	assert(lab[y]==0);*/
	lab[y]=lab[x];lab[x]=0;
	pos[lab[y]]=y;
}
inline void D(){
	cout<<"D"<<endl;
}
void add(int id,int s){
	sz[id]=s;
	if(s==3){
		cur3-=3;
		A(cur3);
	}else{
		if(!ho){
			A(cur12+1);
			if(s==2)cur12+=2;
			else{
				cur12+=2;
				ho=cur12;
			}
		}else{
			if(s==1){
				A(ho);
				ho=0;
			}else{
				A(cur12+1);
				cur12+=2;
			}
		}
	}
}
int adj(int x){
	return ((x-1)^1)+1;
}
void fre(int id){
	int p=pos[id];pos[id]=0;
	if(sz[id]==3){
		if(cur3!=p){
			M(cur3,p);
		}
		cur3+=3;
	}else{
		int s=sz[id];
		if(!ho){
			if(s==2){
				if(p!=adj(cur12)){
					if(lab[adj(cur12)])M(adj(cur12),p);
					if(lab[cur12])M(cur12,adj(p));
				}
				cur12-=2;
			}else{
				ho=p;
			}
		}else{
			if(s==2){
				if(p!=adj(cur12)){
					if(lab[adj(cur12)])M(adj(cur12),p);
					if(lab[cur12])M(cur12,adj(p));
					if(ho==adj(cur12))ho=p;
					else if(ho==cur12)ho=adj(p);
				}
				cur12-=2;
			}else{
				if(p==adj(ho)){
					p=min(p,ho);
					if(p!=adj(cur12)){
						if(lab[adj(cur12)])M(adj(cur12),p);
						if(lab[cur12])M(cur12,adj(p));
					}
				}else{
					if(ho==cur12 || ho==adj(cur12)){
						if(lab[cur12]){
							//assert(p!=cur12);
							M(cur12,p);
						}
						else {
							//assert(p!=adj(cur12));
							M(adj(cur12),p);
						}
					}else if(lab[cur12] || p==cur12){
						if(p==cur12 || p==adj(cur12)){
							p=adj(p);
							//assert(p!=ho);
							M(p,ho);
						}else{
							//assert(cur12!=ho);
							M(cur12,ho);
							//assert(adj(cur12)!=p);
							M(adj(cur12),p);
						}
					}else{
						//assert(lab[adj(cur12)]);
						/*if(sz[lab[adj(cur12)]]==1){
							assert(ho==cur12);
						}else;// assert(sz[lab[adj(cur12)]]==2);
						*/
						//assert(lab[ho]==0);
						M(adj(p),ho);
						
						//assert(adj(cur12)!=min(p,adj(p)));
						M(adj(cur12),min(p,adj(p)));
					}
				}
				ho=0;
				cur12-=2;
			}
		}
	}
}
int main()
{
	cin>>n;
	int opt;
	cur3=n+1;
	int su=0;
	while(cin>>opt){
		/*if(su%2==1){
			assert(ho);
			assert(cur12==su+1);
		}else{
			assert(ho==0);
			assert(cur12==su);
			if(su){
				assert(sz[lab[cur12]]==1 && sz[lab[cur12-1]]==1 || sz[lab[cur12-1]]==2 && !lab[cur12]);
			}
		}*/

		
		/*if(ho){
			assert(lab[ho]==0);
			assert(lab[adj(ho)]);
		}*/
		++te;
		if(opt==0)break;
		if(opt>0){
			add(te,opt);
			if(opt<=2)su+=opt;
		}else{
			opt*=-1;
			lab[pos[opt]]=0;
			if(sz[opt]<=2)su-=sz[opt];
			fre(opt);
			D();
		}
	}
	return 0;
}
