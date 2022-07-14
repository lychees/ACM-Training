#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 410
using namespace std;
struct Point
{
	int x,y;
	void Read()
	{
		scanf("%d %d",&x,&y);
		x+=500,y+=500;
	}
	Point() {}
	Point(int x,int y): x(x),y(y) {}
	friend bool operator == (const Point &a,const Point &b)
	{
		return a.x==b.x&&a.y==b.y;
	}
}S,T,tree[maxn];
int nTree,map[1000][1000],father[700][700];
int ans[1000010],tot;
char out[]={"RUDL"};
int movex[]={1,0,0,-1};
int movey[]={0,1,-1,0};
void read()
{
	S.Read(),T.Read();
	scanf("%d",&nTree);
	if(nTree==0)
	{
		printf("-1\n");
		exit(0);
	}
	for(int i=1;i<=nTree;i++)
	{
		tree[i].Read();
		map[tree[i].x][tree[i].y]=1;
	}
}
void BFS(const Point &S,const Point &T)
{
	queue<Point> q;
	Point head;
	q.push(S);
	memset(father,-1,sizeof(father));
	father[S.x][S.y]=0;
	while(!q.empty())
	{
		head=q.front(),q.pop();
		int x,y;
		for(int i=0;i<4;i++)
		{
			x=head.x+movex[i],y=head.y+movey[i];
			if(x>=350&&x<=650&&y>=350&&y<=650&&map[x][y]==0&&father[x][y]==-1)
			{
				father[x][y]=i;
				q.push(Point(x,y));
				if(x==T.x&&y==T.y)
					break;
			}
		}
		if(x==T.x&&y==T.y)
			break;
	}
	if(father[T.x][T.y]==-1)
	{
		printf("-1\n");
		exit(0);
	}
	for(int i=T.x,j=T.y,p;i!=S.x||j!=S.y;i-=movex[p],j-=movey[p])
	{
		p=father[i][j];
		ans[++tot]=p;
	}
	reverse(ans+1,ans+tot+1);
}
void print(int n)
{
	for(int i=1;i<=n;i++)
		printf("%c",out[ans[i]]);
	printf("\n");
	exit(0);
}
bool check(int x,int y)
{
	if(x<200||x>800||y<200||y>800)
		return true;
	return map[x][y]==0;
}
void work()
{
	for(int i=1;i<=tot;i++)
	{
		int p=ans[i];
		S.x+=movex[p],S.y+=movey[p];
		int px=T.x+movex[p],py=T.y+movey[p];
		if(S.x>=200&&S.x<=800&&S.y>=200&&S.y<=800&&check(px,py))
			T.x=px,T.y=py,ans[++tot]=p;
		else if((px<200||px>800||py<200||py>800))
			T.x=px,T.y=py;
		if(S==T)
			print(tot);
	}
	if(S.x>=400&&S.x<=600)
		for(int i=1;i<=500;i++)
		{
			S.x++,T.x++;
			ans[++tot]=0;
		}
	if(S.y>=400&&S.y<=600)
		for(int i=1;i<=600;i++)
		{
			S.y++,T.y++;
			ans[++tot]=1;
		}
	//把这俩家伙的x对齐
	if(S.x<T.x&&S.y<=T.y)
	{
		//找到最下的最左的树，让他们不断往下走，往左走，往上走，往右走，卡住，哈哈哈哈
		Point p=tree[1];
		for(int i=2;i<=nTree;i++)
			if(p.y>tree[i].y||(p.y==tree[i].y&&p.x>tree[i].x))
				p=tree[i];
		while(T.y>0)
		{
			S.y--,T.y--;
			ans[++tot]=2;
		}
		while(T.x>0)
		{
			S.x--,T.x--;
			ans[++tot]=3;
		}
		while(T.y!=p.y)
		{
			S.y++,T.y++;
			ans[++tot]=1;
		}
		while(T.x<p.x-1)
		{
			S.x++,T.x++;
			ans[++tot]=0;
		}
		while(S.x<T.x)
		{
			S.x++;
			ans[++tot]=0;
		}
		if(S.y==T.y)
			print(tot);
	}
	if(S.x>T.x&&S.y<=T.y)
	{
		//找到最右下的树，让他不断往下走，右走，上走，左走，卡住
		Point p=tree[1];
		for(int i=2;i<=nTree;i++)
			if(p.y>tree[i].y||(p.y==tree[i].y&&p.x<tree[i].x))
				p=tree[i];
		while(T.y>0)
		{
			S.y--,T.y--;
			ans[++tot]=2;
		}
		while(T.x<1000)
		{
			S.x++,T.x++;
			ans[++tot]=0;
		}
		while(T.y!=p.y)
		{
			S.y++,T.y++;
			ans[++tot]=1;
		}
		while(T.x!=p.x+1)
		{
			S.x--,T.x--;
			ans[++tot]=3;
		}
		while(S.x!=T.x)
		{
			S.x--;
			ans[++tot]=3;
		}
		if(S.y==T.y)
			print(tot);
	}
	if(S.x<T.x&&S.y>T.y)
	{
		//找到最左上的树，向上走，左走，下走，右走
		Point p=tree[1];
		for(int i=2;i<=nTree;i++)
			if(p.y<tree[i].y||(p.y==tree[i].y&&p.x>tree[i].x))
				p=tree[i];
		while(T.y<1000)
		{
			S.y++,T.y++;
			ans[++tot]=1;
		}
		while(T.x>0)
		{
			S.x--,T.x--;
			ans[++tot]=3;
		}
		while(T.y!=p.y)
		{
			S.y--,T.y--;
			ans[++tot]=2;
		}
		while(T.x!=p.x-1)
		{
			S.x++,T.x++;
			ans[++tot]=0;
		}
		while(S.x!=T.x)
		{
			S.x++;
			ans[++tot]=0;
		}
		if(S.y==T.y)
			print(tot);
	}
	if(S.x>T.x&&S.y>T.y)
	{
		//找到最右上的树，向上走，右走，下走，左走
		Point p=tree[1];
		for(int i=2;i<=nTree;i++)
			if(p.y<tree[i].y||(p.y==tree[i].y&&p.x<tree[i].x))
				p=tree[i];
		while(T.y<1000)
		{
			S.y++,T.y++;
			ans[++tot]=1;
		}
		while(T.x<1000)
		{
			S.x++,T.x++;
			ans[++tot]=0;
		}
		while(T.y!=p.y)
		{
			S.y--,T.y--;
			ans[++tot]=2;
		}
		while(T.x!=p.x+1)
		{
			S.x--,T.x--;
			ans[++tot]=3;
		}
		while(S.x!=T.x)
		{
			S.x--;
			ans[++tot]=3;
		}
		if(S.y==T.y)
			print(tot);
	}
	//哈哈哈哈，他们x已经对齐了
	if(S.y>T.y)
	{
		int k=map[T.x+1][T.y]?0:3;
		ans[++tot]=1,S.y++,T.y++;
		ans[++tot]=k,S.x+=movex[k],T.x+=movex[k];
		while(S.y>T.y)
			ans[++tot]=2,S.y--;
		print(tot);
	}
	else
	{
		int k=map[T.x+1][T.y]?0:3;
		ans[++tot]=2,S.y--,T.y--;
		ans[++tot]=k,S.x+=movex[k],T.x+=movex[k];
		while(S.y<T.y)
			ans[++tot]=1,S.y++;
		print(tot);
	}
}
int main()
{
	read();
	BFS(S,T);
	work();
	return 0;
}
