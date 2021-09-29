#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int MAXN=1100007;
const int MAXR=20;
const int MAXC=10;
typedef unsigned char _char;
struct Tstack
{
	static const int MAXS=MAXN;
	int len;
	int data[MAXS];
	void clear(void){len=0;}
	void push(int k){data[++len]=k;}
	int pop(void){return data[len--];}
	inline bool empty(){return len==0;}
};

const int exp4[]={0x000003,0x00000C,0x000003,0x000030,0x0000C0,0x000300,0x000C00,
				  0x003000,0x00C000,0x030000,0x0C0000,0x30000,0xC00000};
const int div4[]={0,2,4,6,8,10,12,14,16,18,20,22};
int r,c;
_char f[MAXR][MAXC][MAXN];
int l[MAXR][MAXC][MAXN];
Tstack s[2];
bool a[MAXR][MAXC];
int ans[MAXR][MAXC];
bool path[MAXR][MAXC];
int maxlen=0;

void init()
{
	int i,j;
	char str[20];
	for(i=0;i<r;++i)
	{
		scanf("%s",str);
		for(j=0;j<c;++j)
			if(str[j]=='#')
				a[i][j]=0;
			else
				a[i][j]=1;
	}
}

inline _char max(_char a,_char b)
{
	return a>b?a:b;
}

inline int getbit(int k,int n)
{
	return ((k&exp4[n])>>div4[n]);
}

inline int changebit(int k,int n,int m)
{
	return k-(k&exp4[n])+(m<<div4[n]);
}

inline int changeL(int k,int j)
{
	k=changebit(changebit(k,j,3),j+1,3);
	int t=j+1,s=1,i;
	while(s>0)
	{
		++t;
		i=getbit(k,t);
		if(i==1)
			++s;
		else if(i==2)
			--s;
	}
	k=changebit(k,t,1);
	return k;
}

inline int changeR(int k,int j)
{
	k=changebit(changebit(k,j,3),j+1,3);
	int t=j,s=1,i;
	while(s>0)
	{
		--t;
		i=getbit(k,t);
		if(i==2)
			++s;
		else if(i==1)
			--s;
	}
	k=changebit(k,t,2);
	return k;
}

inline void updata(_char hash[],int path[],Tstack &s,int k,_char v,int last)
{
	if(hash[k]==0xff)
	{
		hash[k]=v;
		path[k]=last;
		s.push(k);
	}
	else if(v>hash[k])
	{
		hash[k]=v;
		path[k]=last;
	}
}

inline bool ok(int k)
{
	int i,j;
	for(i=0;i<c;++i)
	{
		j=getbit(k,i);
		if((j==1)||(j==2))
			return false;
	}
	return getbit(k,c)==1;
}

void solve()
{
	int now=0;
	int last=1;
	int i,j,k,t,left,up,d;
	memset(f,0xff,sizeof(f));
	updata(f[0][0],l[0][0],s[now],1,0,-1);
	for(i=0;i<r;++i)
	{
		for(j=0;j<c;++j)
		{
			now^=1;
			last^=1;
			s[now].clear();
			if(s[last].len>maxlen)
				maxlen=s[last].len;
			while(!s[last].empty())
			{
				k=s[last].pop();
				d=f[i][j][k];
				left=getbit(k,j);
				up=getbit(k,j+1);
				if(a[i][j])
				{
					if((left==2)&&(up==1))
					{
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,3),j+1,3),d+1,k);
					}
					else if((left==0)&&(up==0))
					{
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,1),j+1,2),d+1,k);
					}
					else if((left==1)&&(up==1))
					{
						updata(f[i][j+1],l[i][j+1],s[now],changeL(k,j),d+1,k);
					}
					else if((left==2)&&(up==2))
					{
						updata(f[i][j+1],l[i][j+1],s[now],changeR(k,j),d+1,k);
					}
					else if((left==0)&&(up<3))
					{
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,up),j+1,3),d+1,k);
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,3),j+1,up),d+1,k);
					}
					else if((left<3)&&(up==0))
					{
						if((j+2>c)||(getbit(k,j+2)!=3))
							updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,left),j+1,3),d+1,k);
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,3),j+1,left),d+1,k);
					}
				}
				if(((left==0)||(left==3))&&((up==0)||(up==3)))
				{
					if((up==3)&&((j+2>c)||(getbit(k,j+2)==0)))
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,0),j+1,3),d,k);
					else
						updata(f[i][j+1],l[i][j+1],s[now],changebit(changebit(k,j,0),j+1,0),d,k);
				}
			}
		}
		if(i==(r-1))
			break;
		now^=1;
		last^=1;
		s[now].clear();
		while(!s[last].empty())
		{
			k=s[last].pop();
			d=f[i][c][k];
			left=getbit(k,c);
			if((left==0)||(left==3))
				updata(f[i+1][0],l[i+1][0],s[now],changebit(k,c,0)<<2,d,k);
		}
	}
	int anslen=-1;
	k=-1;
	while(!s[now].empty())
	{
		k=s[now].pop();
		if(ok(k)&&(f[i][c][k]>anslen))
		{
			anslen=f[i][c][k];
			t=k;
		}
	}
	for(i=r-1;i>=0;--i)
		for(j=c;j>=0;--j)
		{
			k=t;
			ans[i][j]=k;
			t=l[i][j][k];
		}
	d=0;
	memset(path,0,sizeof(path));
	for(i=0;i<r;++i)
		for(j=0;j<=c;++j)
		{
			k=f[i][j][ans[i][j]];
			if(k>d)
				path[i][j]=true;
			d=k;
		}
	for(i=0;i<r;++i)
	{
		for(j=0;j<c;++j)
		{
			if(path[i][j+1])
				printf("C");
			else if(!a[i][j])
				printf("#");
			else
				printf(".");
		}
		printf("\n");
	}
}

int main()
{
	int CASE=0;
	maxlen=0;
	while(scanf("%d%d",&r,&c)&&(r||c))
	{
		printf("CASE %d:\n",++CASE);
		init();
		solve();
		printf("\n");
	}
}
