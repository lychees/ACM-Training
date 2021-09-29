#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn=60;
const double eps=1e-5;

int n,m;

double uy,dy,lx,rx;

double ratio;

double px1,py1,px2,py2,ax1,ay1,ax2,ay2;

double px[maxn*maxn],py[maxn*maxn];

int sgn(double x)
{
	if (fabs(x)<=eps) return 0;
	if (x>0) return 1;
	else return -1;
}

struct segment
{
	double x1,y1,x2,y2;
	int dir;
	void init()
	{
		scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		if (sgn(y1-y2)==0) 
		{
			dir=0;
			if (sgn(x1-x2)>0) swap(x1,x2);
		}
		else 
		{
			dir=1;
			if (sgn(y1-y2)>0) swap(y1,y2);
		}
	}
	bool operator==(const segment &a)const
	{
		return dir==a.dir && sgn(x1-a.x1)==0 && sgn(x2-a.x2)==0  && sgn(y1-a.y1)==0 && sgn(y2-a.y2)==0;
	}
}seg1[maxn],seg2[maxn],seg3[maxn],seg4[maxn];

double cross(double x1,double y1,double x2,double y2,double x3,double y3)
{
	return (x1-x2)*(y2-y3)-(y1-y2)*(x2-x3);
}

double move(double pre,double o,double delta,double ratio)
{
	return o+(pre-o)*ratio+delta;
}

bool cro(segment a,segment b)
{
	if (a.dir) swap(a,b);
	if (sgn(b.y1-a.y1)>=0 || sgn(a.y1-b.y2)>=0) return false;
	if (sgn(a.x1-b.x1)>=0 || sgn(b.x1-a.x2)>=0) return false;
	return true;
}

bool cmp(const segment &a,const segment &b)
{
	if (a.dir!=b.dir) return a.dir<b.dir;
	if (sgn(a.x1-b.x1)!=0) return a.x1<b.x1;
	if (sgn(a.x2-b.x2)!=0) return a.x2<b.x2;
	if (sgn(a.y1-b.y1)!=0) return a.y1<b.y1;
	if (sgn(a.y2-b.y2)!=0) return a.y2<b.y2;
	return false;
}

bool check()
{
	if (sgn(ratio-1)>0) return false;
	double l,r,u,d;
	double dex=ax1-px1,dey=ay1-py1;
	l=move(lx,px1,dex,ratio);
	r=move(rx,px1,dex,ratio);
	u=move(uy,py1,dey,ratio);
	d=move(dy,py1,dey,ratio);
	int cnt=0;
	for (int a=1;a<=m;a++)
		if (seg2[a].dir==0)
		{
			if (sgn(seg2[a].y1-d)>=0 && sgn(u-seg2[a].y1)>=0)
			{
				if (sgn(l-seg2[a].x2)>=0 || sgn(seg2[a].x1-r)>=0) ;
				else
				{
					cnt++;
					seg4[cnt].dir=0;
					seg4[cnt].y1=seg4[cnt].y2=seg2[a].y1;
					seg4[cnt].x1=max(l,seg2[a].x1);
					seg4[cnt].x2=min(r,seg2[a].x2);
				}
			}	
		}
		else
		{
			if (sgn(seg2[a].x1-l)>=0 && sgn(r-seg2[a].x2)>=0)
			{
				if (sgn(d-seg2[a].y2)>=0 || sgn(seg2[a].y1-u)>=0) ;
				else
				{
					cnt++;
					seg4[cnt].dir=1;
					seg4[cnt].x1=seg4[cnt].x2=seg2[a].x1;
					seg4[cnt].y1=max(d,seg2[a].y1);
					seg4[cnt].y2=min(u,seg2[a].y2);
				}
			}
		}
	if (cnt!=n) return false;
	for (int a=1;a<=n;a++)
	{
		seg3[a].x1=move(seg1[a].x1,px1,dex,ratio);
		seg3[a].x2=move(seg1[a].x2,px1,dex,ratio);
		seg3[a].y1=move(seg1[a].y1,py1,dey,ratio);
		seg3[a].y2=move(seg1[a].y2,py1,dey,ratio);
		seg3[a].dir=seg1[a].dir;
	}
	sort(seg3+1,seg3+n+1,cmp);
	sort(seg4+1,seg4+n+1,cmp);
	for (int a=1;a<=n;a++)
		if (seg3[a]==seg4[a]) ;
		else return false;
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	rx=uy=-1e+6;lx=dy=1e+6;
	for (int a=1;a<=n;a++)
	{
		seg1[a].init();
		uy=max(uy,max(seg1[a].y1,seg1[a].y2));
		dy=min(dy,min(seg1[a].y1,seg1[a].y2));
		rx=max(rx,max(seg1[a].x1,seg1[a].x2));
		lx=min(lx,min(seg1[a].x1,seg1[a].x2));
	}
	for (int a=1;a<=m;a++)
		seg2[a].init();
	bool check_point=false;
	for (int a=1;a<=n;a++)
	{
		if (check_point) break;
		for (int b=a+1;b<=n;b++)
			if (seg1[a].dir!=seg1[b].dir && cro(seg1[a],seg1[b]))
			{
				check_point=true;
				if (seg1[a].dir) px1=seg1[a].x1,py1=seg1[b].y1;
				else px1=seg1[b].x1,py1=seg1[a].y1;
				break;
			}
	}
	int cnt=0;
	for (int a=1;a<=m;a++)
		for (int b=a+1;b<=m;b++)
			if (seg2[a].dir!=seg2[b].dir && cro(seg2[a],seg2[b]))
			{
				cnt++;
				if (seg2[a].dir) px[cnt]=seg2[a].x1,py[cnt]=seg2[b].y1;
				else px[cnt]=seg2[b].x1,py[cnt]=seg2[a].y1;
			}
	bool find=false;
	if (check_point)
	{
		for (int a=1;a<=n && !find;a++)
			for (int b=1;b<=m && !find;b++)
				if (seg1[a].dir==seg2[b].dir)
				{
					px2=seg1[a].x1;py2=seg1[a].y1;
					ax2=seg2[b].x1;ay2=seg2[b].y1;
					double dx=px2-px1,dy=py2-py1;
					for (int c=1;c<=cnt && !find;c++)
					{
						double dx1=ax2-px[c],dy1=ay2-py[c];
						if (sgn(dx*dy1-dx1*dy)==0)
						{
							ax1=px[c];ay1=py[c];
							if (sgn(dx)!=0) ratio=dx1/dx;
							else ratio=dy1/dy;
							if (check()) find=true;
						}
					}
					px2=seg1[a].x2;py2=seg1[a].y2;
					ax2=seg2[b].x2;ay2=seg2[b].y2;
					dx=px2-px1,dy=py2-py1;
					for (int c=1;c<=cnt && !find;c++)
					{
						double dx1=ax2-px[c],dy1=ay2-py[c];
						if (sgn(dx*dy1-dx1*dy)==0)
						{
							ax1=px[c];ay1=py[c];
							if (sgn(dx)!=0) ratio=dx1/dx;
							else ratio=dy1/dy;
							if (check()) find=true;
						}
					}
				}
	}
	if (find) printf("valid puzzle\n");
	else printf("impossible\n");

	return 0;
}
