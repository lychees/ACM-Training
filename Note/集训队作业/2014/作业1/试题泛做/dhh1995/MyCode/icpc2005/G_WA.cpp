#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
int Case,n,sum,tmp,La,Lb,c[105],d[105],a[55],b[55],x[55],y[55],c0[4],c1[4]; char dir;
int chg(char dir){return dir=='N'?0:dir=='S'?1:dir=='E'?2:3;}
bool match(int i,int j,int L)
{
	while (L>0){
		if (x[i]!=y[j]) return 0;
		if (L<=a[i] || L<=b[j]) return L<=a[i] && L<=b[j];
		if (a[i]!=b[j]) return 0;
		L-=a[i],--i,--j;
	}
	return 1;
}
bool check(int i,int j,int L)
{
	int k=1; while (L>=b[k]) L-=b[k],++k;
	if (x[i]!=y[k] || (i<j?b[k]-L!=a[i]:b[k]-L<a[i])) return 0; ++i,++k;
//	printf("? %d %d\n",i,k);
	while (i<=j){
		if (x[i]!=y[k]) return 0;
		if (i==j) return a[i]<=b[k];
		if (a[i]!=b[i]) return 0;
		++i,++k;
	}
	return 0;
}
int get(int *a,int *x,int *b,int *y,int i,int &L,int flag)
{
	L=0;
	rep(k,1,*b){
		L+=a[i]; int j=flag>0?k:*b+1-k;
		if (x[i]!=y[j]) return 0;
		if (i==(flag>0?*a:1)) return b[j]>a[i]?2:b[j]==a[i];
		if (a[i]!=b[j]) return 0;
		i+=flag;
	}
	return 0;
}
bool work()
{
	if (sum&1) return 0; sum/=2; rep(i,1,n) c[i+n]=c[i],d[i+n]=d[i];
	rep(k,1,n){
		int s=0,flag=0; *a=*b=0; rep(i,0,3) c0[i]=c1[i]=0;
		rep(i,k,k+n-1)
			if (s<sum)
				if (s+c[i]<=sum) c0[d[i]]+=a[++*a]=c[i],x[*a]=d[i],s+=c[i];
				else c0[d[i]]+=a[++*a]=sum-s,x[*a]=d[i],
					c1[d[i]^1]+=b[++*b]=s+c[i]-sum,y[*b]=d[i]^1,s=sum;
			else c1[d[i]^1]+=b[++*b]=c[i],y[*b]=d[i]^1;
		rep(i,0,3) if (c0[i]!=c1[i]) flag=1; if (flag) continue;
//		rep(i,0,3) printf("%d ",c0[i]); puts("c0");
//		rep(i,0,3) printf("%d ",c1[i]); puts("c1");
		reverse(b+1,b+*b+1),reverse(y+1,y+*b+1);
		rep(i,1,*a) printf("%d ",a[i]); puts("a");
		rep(i,1,*a) printf("%d ",x[i]); puts("x");
		rep(i,1,*b) printf("%d ",b[i]); puts("b");
		rep(i,1,*b) printf("%d ",y[i]); puts("y");
		rep(i,1,*a) if (tmp=get(a,x,b,y,i,La,1)){
			printf("i=%d La=%d\n",i,La);
			rep(j,1,*b) if (get(b,y,a,x,j,Lb,1)){
				printf("j=%d Lb=%d\n",j,Lb);
				if (match(i-1,j-1,sum-La-Lb)) return 1;
			}
			rep(j,1,*a) if (get(a,x,b,y,j,Lb,-1)){
//				printf("j=%d Lb=%d !\n",j,Lb);
				if (check(j+1,i-1,La)) return 1;
			}
		}
	}
	return 0;
}
int main()
{
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	while (scanf("%d",&n),n){
		sum=0,d[0]=-1;
		rep(i,1,n){
			scanf("%*c%c%d",&dir,c+i),sum+=c[i],d[i]=chg(dir);
			if (d[i]==d[i-1]) c[i-1]+=c[i],--i,--n;
		}
		if (n>1 && d[1]==d[n]) c[1]+=c[n--]; bool flag=work();
		printf("Polygon %d: %s\n",++Case,flag?"Possible":"Impossible");
	}
	return 0;
}
