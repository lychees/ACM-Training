#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=110;
const int MAXM=20010;
struct wl
{int from,to;double v;};
wl edge[MAXM];
int n,cnt;
struct point
{double x,y;};
point data[MAXN];
int bc[MAXN];
int w[MAXN];
struct ww
{int p;double v;};
ww ed[MAXM];
int next[MAXM],head[MAXN],s_cnt;
double calc(int a,int b)
{
 double l1=(data[a].x-data[b].x)*(data[a].x-data[b].x);
 double l2=(data[a].y-data[b].y)*(data[a].y-data[b].y);
 return sqrt(l1+l2);
}

void build(int a,int b,double c)
{
 edge[++cnt].from=a;
 edge[cnt].to=b;
 edge[cnt].v=c;
 return ;
}
bool cmp(wl a,wl b)
{return a.v<b.v;}
int find(int u)
{
 while(u!=bc[u])
  u=bc[u];
 return u;
}
void s_build(int a,int b,double c)
{
 ed[++s_cnt].p=b;
 ed[s_cnt].v=c;
 next[s_cnt]=head[a];
 head[a]=s_cnt;
 return ;
}
void MST()
{
 for(int i=1;i<=n;i++)
  bc[i]=i;
 sort(edge+1,edge+1+cnt,cmp);
 int k1,k2;
 for(int i=1;i<=cnt;i++)
 {
  k1=find(edge[i].from);
  k2=find(edge[i].to);
  if(k1!=k2)
  {
   s_build(edge[i].from,edge[i].to,edge[i].v);
   s_build(edge[i].to,edge[i].from,edge[i].v);
   bc[k1]=k2;
  }
 }
}
double ans;
void dfs(int u,int fa,double sumv)
{
 ans+=(sumv*w[u]);
 int v,pos;
 pos=head[u];
 while(pos!=0)
 {
  v=ed[pos].p;
  if(v!=fa)
   dfs(v,u,max(sumv,ed[pos].v));
  pos=next[pos];
 }
}
void solve()
{
 ans=0;
 dfs(1,0,0);
 int man=0;
 for(int i=1;i<=n;i++) 
  man+=w[i];
 ans/=man;
 printf("%.2lf\n\n",ans);
}
void init()
{
 cnt=0;
 s_cnt=0;
 memset(head,0,sizeof head);
}
int main()
{
	freopen("island.in","r",stdin);
	freopen("bc.out","w",stdout);

 int cas=1;
 while(1)
 {
  scanf("%d",&n);
  if(n==0)
   break;
  printf("Island Group: %d Average ",cas++);
  init();
  for(int i=1;i<=n;i++)
   scanf("%lf%lf%d",&data[i].x,&data[i].y,&w[i]);
  for(int i=1;i<n;i++)
   for(int j=i+1;j<=n;j++)
    build(i,j,calc(i,j));
  MST();
  solve();
 }
 return 0;
}
 
