#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
#include<map>
using namespace std;
const int N=1024;
const int small=8;
const int valL=10;
const unsigned SEED=3319190931u;

unsigned hash(unsigned seed, unsigned x)
{
	x*=2091135069u;
	x^=seed;
	x^=x<<16;
	x^=(x*1050815003u+1700709617u)%1000000007;
	x^=x>>16;
	x^=seed;
	return x;
}

unsigned next_seed(unsigned seed)
{
	return seed*3766308915u+1421124347u;
}

void putsnum(unsigned x, int l = valL)
{
	for(int i=l;i;i--)
		putchar('0'+(x>>i-1&1));
}

unsigned getsnum(int l = valL)
{
	unsigned x = 0;
	for(int i=l;i;i--)
		x=x<<1|getchar()-'0';
	return x;
}

void putnum(unsigned x, double e)
{
	int d=floor(-e),l=d;
	while(x>>l)
		l+=2,putchar('1');
	putchar('0');
	putsnum(x,l);
}

unsigned getnum(double e)
{
	int d=floor(-e),l=d;
	while(getchar()=='1')
		l+=2;
	return getsnum(l);
}

struct node
{
	int n;
	unsigned val[small];
	unsigned seed;
	node *ch[2];

	inline int get(unsigned key)
	{
		if(n==small)
			return val[hash(seed,key)%small];
		return ch[hash(seed,key)&1]->get(key);
	}
};

// C(n, n / 2) / 2^n
inline double getexp1(int n)
{
	double res=0;
	int h=n/2;
	for(int k=0;k<h;k++)
		res+=log(n-k)-log(h-k);
	return res/log(2)-n;
}
// n! / n^n
inline double getexp2(int n)
{
	double res=0;
	for(int k=0;k<n;k++)
		res+=log(n-k)-log(n);
	return res/log(2);
}

void encode(vector<pair<unsigned, unsigned> > code, unsigned &seed)
{
	if (code.size()==small)
	{
		bool vis[small];
		unsigned b[small];
		int tim=0;
		while(1)
		{
			bool flag=1;
			memset(vis,0,sizeof(vis));
			for(int i=0;i<code.size();i++)
			{
				int w=hash(seed,code[i].first)%small;
				if(vis[w]){flag=0;break;}
				vis[w]=1,b[w]=code[i].second;
			}
			if(flag)break;
			tim++;
			seed=next_seed(seed);
		}
		putnum(tim,getexp2(small));
		for(int i=0;i<small;i++)
			putsnum(b[i]);
		return;
	}
	vector<pair<unsigned, unsigned> > part[2];
	int tim=0;
	while(1)
	{
		part[0].clear(),part[1].clear();
		for(int i=0;i<code.size();i++)
			part[hash(seed,code[i].first)&1].push_back(code[i]);
		if(part[0].size()==code.size()/2)break;
		tim++;
		seed=next_seed(seed);
	}
	putnum(tim,getexp1((int)code.size()));
	encode(part[0],seed=next_seed(seed));
	encode(part[1],seed=next_seed(seed));
}

node *decode(int n, unsigned &seed)
{
	node *code=new node;
	code->n=n;
	if(n==small)
	{
		int tim=getnum(getexp2(n));
		while(tim--)
			seed=next_seed(seed);
		code->seed=seed;
		for (int i=0;i<small;i++)
			code->val[i]=getsnum(valL);
		return code;
	}
	int tim=getnum(getexp1(n));
	while(tim--)
		seed=next_seed(seed);
	code->seed=seed;
	code->ch[0]=decode(n/2,seed=next_seed(seed));
	code->ch[1]=decode(n/2,seed=next_seed(seed));
	return code;
}

int main()
{
	//freopen("message.in","r",stdin);
	//freopen("message.out","w",stdout); 
	string type;
	cin>>type;
	if (type=="encode")
	{
		vector<pair<unsigned, unsigned> > code;
		for(int i=0;i<N;i++)
		{
			unsigned key,val;
			scanf("%u%u",&key,&val);
			code.push_back(make_pair(key,val));
		}
		unsigned seed=SEED;
		encode(code,seed);
		cout<<endl;
	}
	else if(type=="decode")
	{
		getchar();
		unsigned seed=SEED;
		node *code=decode(N,seed);
		int Q;
		cin>>Q;
		for(int k=0;k<Q;k++)
		{
			unsigned key;
			scanf("%u",&key);
			printf("%u\n",code->get(key));
		}
	}
	return 0;
}

