#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int N=99990;
char TS[20];
int n,m,lc[N],rc[N],id[N];
unsigned A[1024],B[1024],C[1024],seed[1024];
string ans;

vector<unsigned> V[N];

unsigned ra()
{return rand()^rand()<<15^rand()<<30;}

string tobit(unsigned x)
{
	string r="";
	for(int i=9;~i;i--)
		if(x>>i&1)r+='1';
		else r+='0';
	return r;
}

void treecode(int x)
{
	if(lc[x]||rc[x])
	{
		ans+='1';
		treecode(lc[x]);
		treecode(rc[x]);
	}
	else ans+='0';
}

unsigned cnt(unsigned x){return x?1+cnt(x&x-1):0;}

bool clr(unsigned x,unsigned r)
{
	srand(x+r);rand();
	return cnt(ra())&1;
}

void build(int x,int d)
{
	if(V[x].empty())return;
	lc[x]=++n,rc[x]=++n;
	int r=seed[d];
	if(V[x].size()>1)
	{
		for(int i=0;i<V[x].size();i++)
			if(clr(V[x][i],r))V[rc[x]].push_back(V[x][i]);
			else V[lc[x]].push_back(V[x][i]);
	}
	else
	{
		for(int i=0;i<1024;i++)
			if(V[x][0]==A[i])C[m++]=B[i];
	}
	build(lc[x],d+1);
	build(rc[x],d+1);
}

void encode()
{
	for(int i=0;i<1024;i++)
	{
		scanf("%u%u",A+i,B+i);
		V[0].push_back(A[i]);
	}
	build(0,0);
	for(int i=0;i<1024;i++)
		ans+=tobit(C[i]);
	treecode(0);
	cout<<ans<<endl;
}

void codetree(int x,int &pos)
{
	if(ans[pos++]=='0'){lc[x]=rc[x]=-1;return;}
	lc[x]=++n,rc[x]=++n;
	codetree(lc[x],pos);
	codetree(rc[x],pos);
	if(lc[lc[x]]==-1&&rc[rc[x]]==-1)lc[x]=rc[x]=0,id[x]=m++;
}

int getid(int x,int d,unsigned t)
{
	if(id[x]!=-1)return id[x];
	int r=seed[d];
	return clr(t,r)?getid(rc[x],d+1,t):getid(lc[x],d+1,t);
}

void decode()
{
	memset(id,-1,sizeof(id));
	cin>>ans;
	for(int i=0;i<1024;i++)
		for(int j=0;j<10;j++)
			C[i]=C[i]<<1|(ans[i*10+j]-'0');
	int pos=1024*10;
	codetree(0,pos);
	unsigned Q,a,p;
	scanf("%u",&Q);
	while(Q--)
	{
		scanf("%u",&a);
		p=getid(0,0,a);
		printf("%u\n",C[p]);
	}
}

int main()
{
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
	srand(768073863);
	for(int i=0;i<1024;i++)seed[i]=ra();
	scanf("%s",TS);
	if(strcmp(TS,"encode")==0)
		encode();
	else
		decode();
	return 0;
}

