#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const string bl[]={"A","B","O","AB"};
string a,b,c; int Case; bool u[5];
void chg(string &a,string &x,char &y){int L=a.size(); y=a[L-1]; x=a[0]; x+=L<3?'O':a[1];}
string trans(string x,string y){return x=="O"?y:y=="O"?x:x==y?x:"AB";}
void get(string &a,string &b,string &s,bool flag)
{
	string x1,x2,t; char y1,y2; int c=0,id; s=""; chg(a,x1,y1),chg(b,x2,y2); rep(i,4) u[i]=0;
	if (flag){
		rep(i,2) rep(j,2){
			t=trans(x1.substr(i,1),x2.substr(j,1));
			rep(k,4) if (bl[k]==t) id=k;
			if (!u[id]){
				u[id]=1; if (c++) s+=", "; s+=t+"-";
				if (y1=='+' || y2=='+') ++c,s+=", "+t+"+";
			}
		}
	}else{
		rep(i,2) rep(j,3){
			t=trans(x1.substr(i,1),bl[j]);
			if (t+y2==b) rep(j1,3){
				t=trans(bl[j],bl[j1]);
				rep(k,4) if (bl[k]==t) id=k;
				if (!u[id]){
					u[id]=1; if (c++) s+=", "; s+=t+"+";
					if (y1=='+' || y2=='-') ++c,s+=", "+t+"-";
				}
			}
		}
	}
	if (!c) s="IMPOSSIBLE"; else if (c>1) s='{'+s+'}';
}
int main()
{
	while (cin>>a>>b>>c,a!="E"){
		if (a[0]=='?') get(b,c,a,0);
		if (b[0]=='?') get(a,c,b,0);
		if (c[0]=='?') get(a,b,c,1);
		cout<<"Case "<<++Case<<": "<<a<<" "<<b<<" "<<c<<endl;
	}
	return 0;
}
