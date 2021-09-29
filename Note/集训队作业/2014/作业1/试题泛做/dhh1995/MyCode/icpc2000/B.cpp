#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
string s,o[100005]; int n,L;
void dfs(int i,int x,int y,int z,string t)
{
	if (i==n){if (z+x*y==2000 && t.size()>n) o[L++]=t+"="; return;}
	int v=s[i]-48;
	if (i){
		dfs(i+1,v,x*y,z,t+"*"+s[i]);
		dfs(i+1,v,1,z+x*y,t+"+"+s[i]);
		dfs(i+1,v,-1,z+x*y,t+"-"+s[i]);
	}
	if (!i || x) dfs(i+1,x*10+v,y,z,t+s[i]);
}
int main()
{
	while (cin>>s){
		L=0,n=s.size()-1,dfs(0,0,1,0,"");
		sort(o,o+L); rep(i,L) cout<<o[i]<<endl;
		if (!L) puts("IMPOSSIBLE");
	}
	return 0;
}
