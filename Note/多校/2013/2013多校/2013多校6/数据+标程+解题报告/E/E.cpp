#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
#define fi first
#define se second
struct M
{
	map<int,int> A;int B;
	M():B(0){}
	~M(){A.clear();}
	int get(int x)
	{
		int c=A[x];
		if(c>0)return 1;else
		if(c>=B)return 0;else return -1;
	}
	void set(int x,int y)
	{
		if(y==-1)A[x]=B-1;else A[x]=y;
	}
};
char s[10];
#define N 1000010
M* Ap[N];bool IF[N];int sp[N];
M* ff()
{
	int st=1;sp[1]=0;Ap[1]=new M();IF[1]=0;
	while(st)
	{
		if(sp[st]==1)
		{
			M*A=Ap[st],*B=Ap[st+1];
			if(A->A.size()<B->A.size())
			{
				swap(A,B);
				for(map<int,int>::iterator i=B->A.begin();i!=B->A.end();i++)
					if(i->se>0)A->set(i->fi,1);else
					if(i->se<B->B)A->set(i->fi,-1);
				delete Ap[st];
			}else
			{
				for(map<int,int>::iterator i=B->A.begin();i!=B->A.end();i++)
					if(A->get(i->fi)==0)
						if(i->se>0)A->set(i->fi,1);else
						if(i->se>=B->B)A->set(i->fi,0);else A->set(i->fi,-1);
				delete Ap[st+1];
			}
			Ap[st]=A;Ap[st+1]=NULL;sp[st]=0;
			continue;
		}else
		if(sp[st]==2)
		{
			M*A=Ap[st],*B=Ap[st+1];bool F=0;
			if(A->A.size()<B->A.size())swap(A,B),F=1;
			for(map<int,int>::iterator i=B->A.begin();i!=B->A.end();i++)
				if(i->se>0)A->set(i->fi,1);else
				if(i->se>=B->B){if(A->get(i->fi)==-1)A->set(i->fi,0);}else
				if(A->get(i->fi)==-1)A->A[i->fi]=A->B-2;
			A->B--;
			if(!F)delete Ap[st+1];else delete Ap[st];
			Ap[st]=A;Ap[st+1]=NULL;st--;
			continue;
		}
		scanf("%s",s);M*A=Ap[st];
		if(s[0]=='e'&&s[1]=='n')
		{
			if(IF[st])A->B--;st--;
		}else
		if(s[0]=='a')
		{
			int x;scanf("%d",&x);
			if(A->get(x)==0)A->set(x,-1);
		}else
		if(s[0]=='u')
		{
			int x;scanf("%d",&x);
			if(A->get(x)==0)A->set(x,1);
		}else
		if(s[0]=='i')
		{
			Ap[st+1]=new M();IF[st+1]=1;sp[st+1]=0;sp[st]=1;st++;
		}else
		if(s[0]=='e'&&s[1]=='l')
		{
			Ap[st+1]=new M();IF[st+1]=0;sp[st+1]=0;sp[st]=2;st++;
		}
	}
	return Ap[1];
}
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		int n;scanf("%d",&n);
		M*A=ff();
		for(int i=1;i<=n;i++)
			printf("%d%c",A->get(i),i==n?'\n':' ');
	}
	return 0;
}