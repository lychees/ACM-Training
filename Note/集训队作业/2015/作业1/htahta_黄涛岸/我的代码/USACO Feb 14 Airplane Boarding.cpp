/*
ID:huangta3
PROG:boarding
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <ctime>
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long LL;
const int maxn=200100;
int ch[maxn][2],fa[maxn],root,tot=0,s[maxn],t[maxn],n;
LL val[maxn],maxv[maxn],pos[maxn],tag[maxn],ans=0;
inline int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f==1)return -v;else return v;
}

void mark(int x,int v)
{
	maxv[x]+=v,val[x]+=v,tag[x]+=v,pos[x]-=v;
}
void pushdown(int x)
{
	int l=ch[x][0],r=ch[x][1];
	if(tag[x])
	{
		if(l)mark(l,tag[x]);
		if(r)mark(r,tag[x]);
		tag[x]=0;
	}
}
void pushup(int x)
{
	maxv[x]=val[x];
	if(ch[x][0])maxv[x]=max(maxv[x],maxv[ch[x][0]]);
	if(ch[x][1])maxv[x]=max(maxv[x],maxv[ch[x][1]]);
}

void rotate(int x,int f)
{
	int y=fa[x];
	pushdown(y),pushdown(x);//?
	fa[ch[x][f]]=y,ch[y][!f]=ch[x][f];
	ch[x][f]=y,fa[x]=fa[y],fa[y]=x;
	if(fa[x])ch[fa[x]][ch[fa[x]][0]!=y]=x;
	pushup(y);
}

void splay(int x)
{
	while(fa[x])
		if(fa[fa[x]]==0)rotate(x,ch[fa[x]][0]==x);else
		{
			int y=fa[x],z=fa[y],f=(ch[z][0]==y);
			if(ch[y][!f]==x)rotate(y,f);else rotate(x,!f);
			rotate(x,f);
		}
	root=x;
}

LL ask(int p)
{
	int k=root,tv=n+2,tk;
	while(1)
	{
		pushdown(k);
		if(pos[k]>=p)
		{
			if(pos[k]<tv)tv=pos[k],tk=k;
			if(ch[k][0])k=ch[k][0];else break;
		}else
		{
			if(ch[k][1])k=ch[k][1];else break;
		}
	}
	k=tk;
	splay(k);
	pushdown(k);
	tv=maxv[ch[k][0]];
	mark(ch[k][0],1);
	return tv;
}

void add(int p,int v)
{
	ch[++tot][0]=ch[root][0];
	fa[tot]=root,fa[ch[root][0]]=tot;
	ch[root][0]=tot;
	pos[tot]=p,val[tot]=v;
	pushup(tot),pushup(root);
	splay(tot);
}

int main()
{
	freopen("boarding.in","r",stdin);
	freopen("boarding.out","w",stdout);
	n=get();
	tot=2;root=1;
	ch[1][1]=2,pos[1]=val[1]=0;
	pos[2]=n+1;fa[2]=1;
	for(int i=1;i<=n;i++)s[i]=get(),t[i]=get();
	for(int i=n;i;i--)
	{
		LL v=ask(s[i]);
		ans=max(ans,v+s[i]+t[i]);
		add(s[i]-1,v+t[i]+1);
	}
	cout<<ans<<endl;
	return 0;
}
