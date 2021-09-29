#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int maxn=111;
const int maxpoints=11111;
const double eps=1e-9;
int n,i,j,points,id[maxpoints],cases;
double x[maxn],h[maxn],b[maxn],point[maxpoints],left,right,mid,top,side,k,height,len;

void addpoints(double z)
{
	point[points]=z;
	id[points]=points;
	points++;
}

void cross(double xa,double xb,double yb,double xc,double xd,double yd)
{
	double va,vc,t;
	va=(xb-xa)/yb;vc=(xd-xc)/yd;
	if(fabs(va-vc)<1e-9)
		return;
	t=(xc-xa)/(va-vc);
//	printf("%lf %lf\n",t,xa+va*t);
	if(t>0&&t<yb&&t<yd)
		addpoints(xa+va*t);
}

bool cmp(int i,int j)
{
	return point[i]<point[j];
}

int main()
{
	freopen("J.in","r",stdin);
	freopen("J_std.out","w",stdout);
	while(scanf("%d",&n)&&n)
	{
		points=0;
		for(i=0;i<n;i++)
		{
			scanf("%lf%lf%lf",&x[i],&h[i],&b[i]);
			b[i]/=2;
			addpoints(x[i]-b[i]);
			addpoints(x[i]);
			addpoints(x[i]+b[i]);
			for(j=0;j<i;j++)
			{
				cross(x[i]-b[i],x[i],h[i],x[j]-b[j],x[j],h[j]);
				cross(x[i]+b[i],x[i],h[i],x[j]-b[j],x[j],h[j]);
				cross(x[i]-b[i],x[i],h[i],x[j]+b[j],x[j],h[j]);
				cross(x[i]+b[i],x[i],h[i],x[j]+b[j],x[j],h[j]);
			}
		}
		sort(id,id+points,cmp);
		len=0;
		for(i=1;i<points;i++)
		{
			left=point[id[i-1]];
			right=point[id[i]];
//			printf("%lf %lf\n",left,right);
			mid=(left+right)/2;
			if(right-left>eps)
			{
				top=-2;
				for(j=0;j<n;j++)
				{
					side=x[j]-b[j];
					if(side<mid&&x[j]>mid)
					{
						height=h[j]*(mid-side)/b[j];
						if(height>top)
						{
							top=height;
							k=h[j]/b[j];
						}
					}
					side=x[j]+b[j];
					if(x[j]<mid&&side>mid)
					{
						height=h[j]*(side-mid)/b[j];
						if(height>top)
						{
							top=height;
							k=h[j]/b[j];
						}
					}
				}
				if(top>-1)
					len+=(right-left)*sqrt(1+k*k);
			}
		}
//		printf("%lf\n",len);
		printf("Case %d: %d\n\n",++cases,((int)((len+0.5)*10))/10);
	}
	return 0;
}
