#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
struct bian{
	int next,point,f;
}b[50000];
int p[7000],len,dst[7100],pd[7100],x[7100];
int n,m,u[7000],v[7000],totpoint;
const int inf=1e9;
void ade(int k1,int k2,int k3)
{
    len++; b[len].point=k2; b[len].next=p[k1]; b[len].f=k3; p[k1]=len;
}
void add(int k1,int k2,int k3)
{
    ade(k1,k2,k3); ade(k2,k1,0);
}
bool bfs(int s,int t)
{
    int head=1,now=0,i,j;
    memset(dst,0xff,sizeof dst);
    memset(pd,0x00,sizeof pd);
    x[1]=s; pd[s]=1; dst[s]=0;
    while (head>now)
    {
        now++; i=p[x[now]]; 
        while (i!=-1)
        {
            j=b[i].point;
            if ((b[i].f)&&(!pd[j]))
            {
                pd[j]=1; dst[j]=dst[x[now]]+1;
                if (j==t)
                {
                    return 1;
                }
                head++; x[head]=j;
            }
            i=b[i].next;
        }
    }
    return pd[t];
}
int change(int k1,int aim,int k2)
{
    if ((k1==aim)||(k2==0)) return k2;
    int num=0,k,i,j;
    i=p[k1];
    while (i!=-1)
    {
        j=b[i].point;
        if ((b[i].f)&&(dst[k1]+1==dst[j]))
        {
            k=change(j,aim,min(k2,b[i].f));
            k2=k2-k; num+=k;
            b[i].f=b[i].f-k; b[i^1].f+=k;
            if (k2==0)
            {
                break;
            }
        }
        i=b[i].next;
    }
    if (!num)
    {
        dst[k1]=-1;
    }
    return num;
}
int dinic(int s,int t,int lim){
    int now=0; 
	while (bfs(s,t)&&lim){
		int k=change(s,t,lim); now+=k; lim-=k;
	}
	return now;
}
int main(){
//	freopen("forest61.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]);
	int tot=0; memset(p,0xff,sizeof p); totpoint=n+m+1; len=-1;
	for (int i=1;i<=n;i++) add(i,totpoint,2);
	for (int i=1;i<=m;i++){
		add(0,i+n,1); tot++; add(i+n,u[i],1); add(i+n,v[i],1);
	}
	int w=dinic(0,totpoint,inf);
	if (tot!=w){
		printf("No\n"); return 0;
	}
	for (int i=1;i<=n;i++){
		int kk=b[(i-1<<1)+1].f;
		w-=dinic(i,0,kk); b[i-1<<1].f=0; b[(i-1<<1)+1].f=0;
		w+=dinic(0,totpoint,2); if (tot!=w){printf("No\n"); return 0;}
		b[(i-1<<1)].f=2;
	}
	printf("Yes\n");
	return 0;
}
