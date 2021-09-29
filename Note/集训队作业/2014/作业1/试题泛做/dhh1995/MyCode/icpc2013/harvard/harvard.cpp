#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
typedef long long ll;
const int N=1005;
int n,m,k,l,a[N],b[15],stack[N],h[N],t[N]; ll ans,c[15][15]; char ch;
void dfs(int x,int y,int z,int s,ll res)
{
	if (res>=ans) return; if (s>k){ans=res; return;} if (x>n) return;
	if (y==1){
		int i=k; while (b[i]) --i;
		rep(j,k) if (b[j]>1 && b[j]<x) res+=c[i][j]+c[j][i];
		b[i]=x,dfs(x,y+1,i-1,s+1,res),b[i]=0;
	}else{
		if (y<=m) rep(i,z) if (!b[i]){
			ll tmp=res; rep(j,k) if (b[j]>1 && b[j]<x) tmp+=c[i][j]+c[j][i];
			b[i]=x,dfs(x,y+1,i-1,s+1,tmp),b[i]=0;
		}
		dfs(x+1,1,k,s,res);
	}
}
void work(int x,int z)
{
	if (x>m || x>k){
		rep(i,k) rep(j,k) c[i][j]=0; int top=1,flag=0; ll res=0,Times=1; t[1]=0;
		rep(i,l){
			if (a[i]<0) Times*=stack[++top]=-a[i],h[top]=t[top]=0;
			else if (!a[i]){
				c[t[top]][h[top]]+=Times;
				Times/=stack[top];
				c[t[top]][h[top]]-=Times;
				c[t[top-1]][h[top]]+=Times;
				if (!h[--top]) h[top]=h[top+1];
				if (t[top+1]) t[top]=t[top+1];
			}else{
				res+=Times;
				if (!b[a[i]]){
					if (!h[top]) h[top]=a[i];
					c[t[top]][a[i]]+=Times;
					t[top]=a[i],flag=1;
				}
			}
		}
		dfs(2,1,k,x,res+flag); return;
	}
	rep(i,z) if (!b[i]) b[i]=1,work(x+1,i-1),b[i]=0;
}
int main()
{
	freopen("harvard.in","r",stdin);
	freopen("harvard.out","w",stdout);
	while (l=k=0,ans=1LL<<60,scanf("%d%d ",&n,&m)!=EOF){
		while ((ch=getchar())!='\n' && ch!=EOF){
			if (ch=='R') ++l,scanf("%d",a+l),a[l]*=-1;
			if (ch=='V') ++l,scanf("%d",a+l),k=max(k,a[l]);
			if (ch=='E') a[++l]=0;
			}
		work(1,k),cout<<ans<<endl;
		}
	return 0;
}
