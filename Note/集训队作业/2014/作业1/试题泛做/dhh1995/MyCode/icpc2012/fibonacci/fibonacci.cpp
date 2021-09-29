#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=105;
string l[N],r[N],s,t; int next[100005],Case,n=100,m=100000; long long f[N];
int get(string L,string R)
{
	if (L.size()>=m) L.erase(0,L.size()-m+1);
	if (R.size()>=m) R.erase(m-1);
	t=L+R; int n=t.size(),res=0,j=0; if (n<m) return 0;
	rep(i,n){
		while (j>=0 && t[i]!=s[j]) j=next[j];
		if (++j==m) ++res,j=next[j];
	}
	return res;
}
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	l[0]=r[0]="0",l[1]=r[1]="1";
	for (int i=2;i<=n;++i){
		if (l[i-1].size()<m) l[i]=l[i-1]+l[i-2]; else l[i]=l[i-1];
		if (l[i].size()>m) l[i].erase(m);
		if (r[i-2].size()<m) r[i]=r[i-1]+r[i-2]; else r[i]=r[i-2];
		if (r[i].size()>m) r[i].erase(0,r[i].size()-m);
	}
	while (scanf("%d",&n)!=EOF){
		cin>>s,m=s.size(),next[0]=-1; int j=-1;
		rep(i,m){
			while (j>=0 && s[i]!=s[j]) j=next[j];
			next[i+1]=++j;
		}
		rep(i,n+1) f[i]=0; f[0]=s=="0",f[1]=s=="1";
		for (int i=2;i<=n;++i) f[i]=f[i-1]+f[i-2]+get(r[i-1],l[i-2]);
		cout<<"Case "<<++Case<<": "<<f[n]<<endl;
	}
	return 0;
}
