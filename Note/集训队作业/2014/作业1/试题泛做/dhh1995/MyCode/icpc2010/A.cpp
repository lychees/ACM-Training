#include<cstdio>
#include<string>
#include<queue>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (short i=0,_=n;i<_;++i)
int Case,n,m,tot; string s[105],t[105]; map<string,int> H;
int cal(int x,char opr,int y){return opr=='+'?x+y:opr=='-'?x-y:x*y;}
struct var{
	int x,y,z,d; deque<int> a; var(){x=y=z=d=1;}
	var(int X,int Y,int Z,int D):x(X),y(Y),z(Z),d(D){}
	inline int size() const{return x*y*z;}
	inline bool single() const{return d==1 && x==1;}
	var work(char opr,const var &A){
		var B(max(x,A.x),max(y,A.y),max(z,A.z),max(d,A.d)); bool s=single(),As=A.single();
		rep(i,B.size()) B.a.push_back(cal(s?a[0]:a[i],opr,As?A.a[0]:A.a[i])); return B;
	}
	var rho(const var &A){
		var B(a[0],x<2?1:a[1],x<3?1:a[2],x); int j=0;
		rep(i,B.size()){B.a.push_back(A.a[j]); if (++j==A.size()) j=0;} return B;
	}
	void drop(int n){x-=n; rep(i,n) a.pop_front();}
	var get(char opr){
		var A(x,y,z,max(1,d-1)); int val;
		if (d==3){
			A.z=1;
			rep(i,x) rep(j,y){
				val=a[(i*y+j)*z+z-1];
				for (int k=z-2;k>=0;--k) val=cal(a[(i*y+j)*z+k],opr,val);
				A.a.push_back(val);
			}
		}else if (d==2){
			A.y=1;
			rep(i,x){
				val=a[i*y+y-1];
				for (int j=y-2;j>=0;--j) val=cal(a[i*y+j],opr,val);
				A.a.push_back(val);
			}
		}else{
			A.x=1; val=a[x-1];
			for (int i=x-2;i>=0;--i) val=cal(a[i],opr,val);
			A.a.push_back(val);
		}
		return A;
	}
	void prt(){
		if (d==3)
			rep(i,x){
				rep(j,y) rep(k,z) printf("%d%s",a[(i*y+j)*z+k],k+1<z?" ":"\n");
				if (i+1<x) puts("");
			}
		if (d==2) rep(i,x) rep(j,y) printf("%d%s",a[i*y+j],j+1<y?" ":"\n");
		if (d==1) rep(i,x) printf("%d%s",a[i],i+1<x?" ":"\n");
	}
}v[20005],u[105];
var iota(int n,int v){var A(n,1,1,1); rep(i,n) A.a.push_back(i+v); return A;}
bool read(){char ch; do cin>>t[n++],ch=getchar(); while (ch==' '); return ch=='\n';}
int id(string s){if (H.count(s)) return H[s]; H[s]=++tot; return tot;}
int chg(string s){int x=0; rep(i,s.size()) x=x*10+s[i]-48; return x;}
bool isvar(string s){return s[0]>='a' && s[0]<='z' && s.size()<4 && s!="rho";}
void ins(var val)
{
	if (m && s[m]=="0") ++u[m].x,u[m].a.push_front(val.a[0]);
	else s[++m]="0",u[m]=val;
}
void deal(var A,string opr,var &B)
{
	if (opr=="drop") B.drop(A.a[0]);
	else if (opr=="rho") B=A.rho(B);
	else B=A.work(opr[0],B);
}
int main()
{
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	while (n=m=0,read() && *t!="#"){
		printf("Case %d:",++Case); rep(i,n) cout<<" "<<t[i]; cout<<endl;
		while (n--)
			if (t[n][0]>='0' && t[n][0]<='9') ins(iota(1,chg(t[n])));
			else{
				if (s[m]=="/") --m,u[m]=u[m].get(t[n][0]);
				else if (isvar(t[n])){
					int w=id(t[n]);
					if (s[m]=="=") --m,v[w]=u[m];
					else if (m>2 && s[m]=="0" && s[m-1]!=")") --m,deal(v[w],s[m+1],u[m]);
					else ins(v[w]);
				}else{
					if (m>2 && s[m]=="0" && s[m-1]!=")") deal(u[m],s[m-1],u[m-2]),m-=2;
					if (t[n]=="iota") u[m]=iota(u[m].a[0],1);
					else if (t[n]=="(") m-=2,ins(u[m+2]); else s[++m]=t[n];
				}
			}
		while (m>1) deal(u[m],s[m-1],u[m-2]),m-=2; u[m].prt();
	}
	return 0;
}
