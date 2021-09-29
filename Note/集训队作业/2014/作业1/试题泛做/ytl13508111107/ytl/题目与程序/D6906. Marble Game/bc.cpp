#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<iostream>
#include<map>
#include<queue>
using namespace std;

int a[4][4],b[4][4];
int tmp[4][4];
int N,M,c[9],ind[4][4];
long long jia()
{
    memset(c,0,sizeof(c));
    int i,j;
    for(i=0;i<N;i++)
	for(j=0;j<N;j++)if(b[i][j]>0)
	    c[b[i][j]]=ind[i][j];
    long long ans=0;
    for(i=1;i<=M;i++)
	ans=(ans<<5)+c[i];
    return ans;
}
int ix[20],iy[20],X[20],Y[20];
void jie(long long sta)
{
    memset(tmp,0,sizeof(tmp));
    int i,j;

    for(i=M;i>=1;i--)
    {
	j=(sta&31);
	sta>>=5;
	if(j)
	{
	    tmp[X[j]][Y[j]]=i;
	    tmp[ix[i]][iy[i]]=-i;
	}
    }
}
int heng[4][4][4],shu[4][4][4];
int rot1()
{
    int i,j,ii,jj;
    memset(b,0,sizeof(b));
    for(i=N-1;i>=0;i--)
	for(j=0;j<N;j++)if(a[i][j]>0)
	{
	    ii=i,jj=j;
	    while(ii+1<N&&!heng[jj][ii][ii+1]&&!b[ii+1][jj])
		ii++;
	    if(ii==N-1||heng[jj][ii][ii+1]||b[ii+1][jj]>0)
		b[ii][jj]=a[i][j];//,b[ix[a[i][j]]][iy[a[i][j]]]=-a[i][j];
	    else if(a[i][j]==-b[ii+1][jj])
		b[ii+1][jj]=0;
	    else
		return 0;
	}
    else if(a[i][j]<0)
	b[i][j]=a[i][j];
    return 1;
}
int rot2()
{
    int i,j,ii,jj;
    memset(b,0,sizeof(b));
    for(i=0;i<N;i++)
	for(j=0;j<N;j++)if(a[i][j]>0)
	{
	    ii=i,jj=j;
	    while(ii&&!heng[jj][ii][ii-1]&&!b[ii-1][jj])
		ii--;
	    if(ii==0||heng[jj][ii][ii-1]||b[ii-1][jj]>0)
		b[ii][jj]=a[i][j];//,b[ix[a[i][j]]][iy[a[i][j]]]=-a[i][j];
	    else if(a[i][j]==-b[ii-1][jj])
		b[ii-1][jj]=0;
	    else
		return 0;
	}
    else if(a[i][j]<0)
	b[i][j]=a[i][j];
    return 1;
}
int rot3()
{
    int i,j,ii,jj;
    memset(b,0,sizeof(b));
    for(j=N-1;j>=0;j--)
	for(i=0;i<N;i++)if(a[i][j]>0)
	{
	    ii=i,jj=j;
	    while(jj+1<N&&!shu[ii][jj][jj+1]&&!b[ii][jj+1])
		jj++;
	    if(jj==N-1||shu[ii][jj][jj+1]||b[ii][jj+1]>0)
		b[ii][jj]=a[i][j];//,b[ix[a[i][j]]][iy[a[i][j]]]=-a[i][j];
	    else if(a[i][j]==-b[ii][jj+1])
		b[ii][jj+1]=0;
	    else
		return 0;
	}else if(a[i][j]<0)
	    b[i][j]=a[i][j];
    return 1;
}
int rot4()
{
    int i,j,ii,jj;
    memset(b,0,sizeof(b));
    for(j=0;j<N;j++)
	for(i=0;i<N;i++)if(a[i][j]>0)
	{
	    ii=i,jj=j;
	    while(jj&&!shu[ii][jj][jj-1]&&!b[ii][jj-1])
		jj--;
	    if(jj==0||shu[ii][jj][jj-1]||b[ii][jj-1]>0)
		b[ii][jj]=a[i][j];//,b[ix[a[i][j]]][iy[a[i][j]]]=-a[i][j];
	    else if(a[i][j]==-b[ii][jj-1])
		b[ii][jj-1]=0;
	    else
		return 0;
	}else if(a[i][j]<0)
	    b[i][j]=a[i][j];
    return 1;
}

map<long long,int>dis;

queue<long long>q;

void upd(long long s,int d)
{
    if(dis.count(s))
	return;
    dis[s]=d;
    q.push(s);
}
int gao()
{
    long long u,v;
    int i;

    dis.clear();
    while(!q.empty())
	q.pop();

    upd(jia(),0);
    while(!q.empty())
    {
	u=q.front();q.pop();
	i=dis[u];

	jie(u);
	memcpy(a,tmp,sizeof(tmp));

	if(rot1())
	upd(jia(),i+1);

	if(rot2())
	upd(jia(),i+1);
	
	if(rot3())
	upd(jia(),i+1);

	if(rot4())
	upd(jia(),i+1);

	if(dis.count(0))
	    return dis[0];
    }
    return -1;
}
int W;
int yin[110];
int init()
{
    int ret=1;
    memset(heng,0,sizeof(heng));
    memset(shu,0,sizeof(shu));
    memset(b,0,sizeof(b));
    memset(ind,0,sizeof(ind));
    memset(c,0,sizeof(c));
    memset(a,0,sizeof(a));
    int i,j,k;

    int x,y;
    for(i=1;i<=M;i++)
    {
	scanf("%d%d",&x,&y);
	if(b[x][y])
	    ret=0;
	b[x][y]=i;
    }
    for(i=1;i<=M;i++)
    {
	scanf("%d%d",&x,&y);

	if(b[x][y]>0)
	{
	    if(b[x][y]==i)
		b[x][y]=0;
	    else
		ret=0;
	}
	else if(b[x][y]<0)
	    ret=0;
	else
	    b[x][y]=-i;
	ix[i]=x,iy[i]=y;
    }
    int xx,yy;

    for(i=1;i<=W;i++)
    {
	scanf("%d%d%d%d",&x,&y,&xx,&yy);
	if(xx==x)
	    shu[x][y][yy]=shu[x][yy][y]=1;
	if(yy==y)
	    heng[y][x][xx]=heng[y][xx][x]=1;
    }
    if(ret==0)
	return 0;
    k=0;
    for(i=0;i<N;i++)
	for(j=0;j<N;j++)
	    ind[i][j]=++k,X[k]=i,Y[k]=j;
    return 1;
}
int main()
{
    	freopen("game.in","r",stdin);
	freopen("bc.out","w",stdout);
	int k,ii=0,i,w,j,jj=0;
    while(scanf("%d%d%d",&N,&M,&W),N)
    {
	k=init();
	if(k)
	    j=gao();
	jj++;
    	if(!k||j<0)
	{
	    printf("Case %d: ",++ii);
	    puts("impossible\n");
	}
	else
	{printf("Case %d: ",++ii);

	    printf("%d moves\n\n",j);
	    	}
    }
}
