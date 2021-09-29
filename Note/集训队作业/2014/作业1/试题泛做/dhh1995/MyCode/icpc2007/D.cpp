#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<n;++i)
ll Case,n,t,a,b,e,g,x[1005],y[1005]; bool u[1005]; unsigned ll m;
int main()
{
	while (cin>>n>>m,n||m){
		rep(i,n) cin>>x[i]>>y[i],u[i]=1; a=b=g=0;
		rep(i,n){
			int l=(i+n-1)%n,r=(i+1)%n;
			if ((x[r]-x[i])*(y[i]-y[l])==(y[r]-y[i])*(x[i]-x[l])) u[i]=0;
		}
		t=n,n=0; rep(i,t) if (u[i]) x[n]=x[i],y[n++]=y[i]; x[n]=*x,y[n]=*y;
		rep(i,n) a+=x[i+1]*y[i]-x[i]*y[i+1],b+=e=abs(__gcd(x[i+1]-x[i],y[i+1]-y[i])),g=__gcd(g,e);
		a=abs(a/g/g),b=b/g;
		cout<<"Case "<<++Case<<": "<<(m+m+(2*m+1)*(m+1)*m/6*a-(m+1)*m/2*b)/2<<endl;
	}
	return 0;
}
