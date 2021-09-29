
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int n;
double v,sv;
struct po
{
    int x, y, z;
    double r;
}p[10],b[2];
 
bool vis[10];
 
const double pi = acos(-1.0); //pi=3.141592653
const double inf=10000000000.0;
 
double min(double a,double b)
{
       if(a<b)
       return a;
       else
       return b;
}
 
double volume(po a,po b)//两点之间的距离 
{
     return sqrt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
 
double minst(int i)//找点i上的气球的最大半经 
{
       int j;
       double m=inf;
       double mi[6];
       mi[0]=abs(p[i].x-b[0].x);mi[1]=abs(p[i].y-b[0].y);mi[2]=abs(p[i].z-b[0].z);
       mi[3]=abs(p[i].x-b[1].x);mi[4]=abs(p[i].y-b[1].y);mi[5]=abs(p[i].z-b[1].z);
       for(j=0;j<6;j++ )
       if(mi[j]<m)
         m=mi[j];
      for(j=0;j<n;j++)
      {
           if(i!=j  && vis[j]==true)
           {
               m=min(m,volume(p[i],p[j])-p[j].r);
           }
      }
     // printf("%.2lf\n",m);
      return m;
}
 
void dfs(int step,double bv)
{
    if(step==n)
    {
        if(bv>v)
        v=bv;
        return ;       
    }
    else
    {
       for(int i=0;i<n;i++)
            if(!vis[i])
            {
                 vis[i]=true;
                 p[i].r=minst(i);
                 if(p[i].r>0)
                   dfs(step+1,bv+(4.0/3.0)*pi*p[i].r*p[i].r*p[i].r);
                 else
                   dfs(step+1,bv);
                 vis[i]=false;
            }
             
    }
     
}
 
int main(){
	freopen("box.in","r",stdin);
	freopen("bc.out","w",stdout);
    int i,j,cas=0;
    while(scanf("%d",&n)!=EOF)
    {
		cas++;
         scanf("%d%d%d%d%d%d",&b[0].x,&b[0].y,&b[0].z,&b[1].x,&b[1].y,&b[1].z);
         sv=fabs(b[0].x-b[1].x)*abs(b[0].y-b[1].y)*abs(b[0].z-b[1].z);//算出长方体的体积 
         for(i=0;i<n;i++)
         {
             scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
             p[i].r=0;
         }
         v=0;
         memset(vis,0,sizeof(vis));//用于标记是否遍历过 
         dfs(0,0.0);
         printf("%.lf\n",sv-v);
    }
    return 0;    
}
