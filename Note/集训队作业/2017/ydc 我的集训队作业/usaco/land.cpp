#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 500010
using namespace std;
typedef long long LL;
struct pp
{
	int h,l;
}square[MAXN];
struct node
{
	LL S,G;
	int num;
}queue[MAXN];
int n;
LL F[MAXN];
bool mark[MAXN];
bool cmp(const pp &a,const pp &b)
{
	return a.h<b.h;
}
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&square[i].h,&square[i].l);
	sort(square+1,square+n+1,cmp);
	int maxl=0,tot=n;
	n=0;
	for(int i=tot;i>=1;i--)
		square[i].l<=maxl?mark[i]=true:maxl=square[i].l;
	for(int i=1;i<=tot;i++)
		if(mark[i]==false)
			square[++n]=square[i];
}
void Dp()
{
	int front=1,rear=0;
	queue[++rear]=(node){0,square[1].l,0};
	for(int i=1;i<=n;i++)
	{
		while(front<rear&&queue[front+1].S-queue[front].S<=-square[i].h*(queue[front+1].G-queue[front].G))
			front++;
		F[i]=queue[front].S+square[i].h*queue[front].G;
		node now=(node){F[i],square[i+1].l,i};
		while(front<rear&&(now.S-queue[rear].S)*(queue[rear].G-queue[rear-1].G)>=(queue[rear].S-queue[rear-1].S)*(now.G-queue[rear].G))
			rear--;
		queue[++rear]=now;
	}
}
int main()
{
 	read();
 	Dp();
 	printf("%I64d\n",F[n]);
 	return 0;
}

