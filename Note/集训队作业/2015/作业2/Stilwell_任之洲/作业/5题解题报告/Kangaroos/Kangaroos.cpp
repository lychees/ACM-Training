#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n,m,i,j,k,l,r;
int a[50005],b[50005],ans[200005];

struct node
{
	node *l,*r;
	int x,y,Minx,Maxx,Miny,Maxy,id;
	int ans,sum,pre,now,Max;
	bool mark,clean;
	void down()
	{
		if(!clean)pre=now;
		if(now>Max)Max=now;
		if(l)
		{
			if(clean)
			{
				if(!l->clean)l->clean=true,l->pre=l->now+pre;
				if(l->now+pre>l->Max)l->Max=l->now+pre;
				if(l->sum+pre>l->ans)l->ans=l->sum+pre;
				l->sum=l->now=now;
			}else l->now+=pre,l->sum+=pre;
			l->mark=true;
		}
		if(r)
		{
			if(clean)
			{
				if(!r->clean)r->clean=true,r->pre=r->now+pre;
				if(r->now+pre>r->Max)r->Max=r->now+pre;
				if(r->sum+pre>r->ans)r->ans=r->sum+pre;
				r->sum=r->now=now;
			}else r->now+=pre,r->sum+=pre;
			r->mark=true;
		}
		clean=mark=false;
		now=pre=0;
	}
}t[200005],*root;
inline bool cmpx(const node &a,const node &b){return a.x<b.x;}
inline bool cmpy(const node &a,const node &b){return a.y<b.y;}

double avex,avey,sumx,sumy;
double sqr(double x){return x*x;}
node *build(int l,int r)
{
	int mid=(l+r)>>1;
	avex=avey=sumx=sumy=0;
	for(int i=l;i<=r;++i)avex+=t[i].x,avey+=t[i].y;
	avex/=(r-l+1);avey/=(r-l+1);
	for(int i=l;i<=r;++i)sumx+=sqr(t[i].x-avex),sumy+=sqr(t[i].y-avey);
	if(sumx>sumy)nth_element(t+l,t+mid,t+r+1,cmpx);
	else nth_element(t+l,t+mid,t+r+1,cmpy);
	swap(t[l],t[mid]);
	t[l].Minx=t[l].Maxx=t[l].x;
	t[l].Miny=t[l].Maxy=t[l].y;
	if(l!=mid)
	{
		node *y=t[l].l=build(l+1,mid);
		if(y->Minx<t[l].Minx)t[l].Minx=y->Minx;
		if(y->Maxx>t[l].Maxx)t[l].Maxx=y->Maxx;
		if(y->Miny<t[l].Miny)t[l].Miny=y->Miny;
		if(y->Maxy>t[l].Maxy)t[l].Maxy=y->Maxy;
	}
	if(r!=mid)
	{
		node *y=t[l].r=build(mid+1,r);
		if(y->Minx<t[l].Minx)t[l].Minx=y->Minx;
		if(y->Maxx>t[l].Maxx)t[l].Maxx=y->Maxx;
		if(y->Miny<t[l].Miny)t[l].Miny=y->Miny;
		if(y->Maxy>t[l].Maxy)t[l].Maxy=y->Maxy;
	}
	return t+l;
}

void calc(node *x)
{
	if(x->Minx>r||x->Maxy<l)
	{
		if(!x->clean)x->pre=x->now;
		if(x->now>x->Max)x->Max=x->now;
		if(x->sum>x->ans)x->ans=x->sum;
		x->now=x->sum=0;
		x->mark=x->clean=true;
		return;
	}
	if(x->Maxx<=r&&x->Miny>=l)
	{
		++x->sum;
		++x->now;
		x->mark=true;
		return;
	}
	if(x->mark)x->down();
	if(x->x<=r&&x->y>=l)++x->sum;
	else
	{
		if(x->sum>x->ans)x->ans=x->sum;
		x->sum=0;
	}
	if(x->l)calc(x->l);
	if(x->r)calc(x->r);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d%d",&a[i],&b[i]);
	for(i=1;i<=m;++i)scanf("%d%d",&t[i].x,&t[i].y),t[i].id=i;
	root=build(1,m);
	for(i=1;i<=n;++i)
	{
		l=a[i];r=b[i];
		calc(root);
	}
	for(i=1;i<=m;++i)
	{
		if(t[i].mark)t[i].down();
		if(t[i].l&&t[i].Max>t[t[i].l-t].Max)t[t[i].l-t].Max=t[i].Max;
		if(t[i].r&&t[i].Max>t[t[i].r-t].Max)t[t[i].r-t].Max=t[i].Max;
		if(t[i].ans>ans[t[i].id])ans[t[i].id]=t[i].ans;
		if(t[i].sum>ans[t[i].id])ans[t[i].id]=t[i].sum;
		if(t[i].Max>ans[t[i].id])ans[t[i].id]=t[i].Max;
	}
	for(i=1;i<=m;++i)printf("%d\n",ans[i]);
}
