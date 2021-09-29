#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char input[2000];
bool ok;
int i,j,position,N,cases;
long long D,calc,T;
long long A[110];

long long get_num()
{
	long long tmp;
	tmp=0;
	while('0'<=input[position] && input[position]<='9')
	{
		tmp=tmp*10+input[position]-'0';
		position++;
	}
	return tmp;
}

bool init()
{
	int sign;
	long long C,E;
	gets(input);
	if(input[0]=='.')
		return false;
	memset(A,0,sizeof(A));
	position=1;
	while(input[position]!=')')
	{
		if(input[position]=='-')
		{
			sign=-1;
			position++;
		}
		else if(input[position]=='+')
		{
			sign=1;
			position++;
		}
		else
			sign=1;
		if(input[position]!='n')
			C=get_num();
		else
			C=1;
		C*=sign;
		if(input[position]!='n')
			E=0;
		else
		{
			position++;
			if(input[position]!='^')
				E=1;
			else
			{
				position++;
				E=get_num();
			}
		}
		A[E]=C;
	}
	position+=2;
	D=get_num();
	return true;
}

void work()
{
	for(N=100;A[N]==0;N--);
		ok=true;
	for(i=1;i<=N+1;i++)
	{
		calc=0;
		T=1;
		for(j=0;j<=N;j++)
		{
			calc=(calc + (T*A[j])%D)%D;
			T=(T*i)%D;
		}
		if(calc!=0)
			ok=false;
	}
	if(ok)
		printf("Case %d: Always an integer\n",++cases);
	else
		printf("Case %d: Not always an integer\n",++cases);
}

int main()
{
	freopen("always.in","r",stdin);
	freopen("bc.out","w",stdout);
	cases=0;
	while(init())
		work();
	return 0;
}
