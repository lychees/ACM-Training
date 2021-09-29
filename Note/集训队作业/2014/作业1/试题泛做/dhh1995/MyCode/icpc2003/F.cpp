#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=1005;
int Case,F=1,a[N],b[N],c[N],d[N]; char A[N],B[N];
int c4(int x){return x<10?x+48:x+55;}
void c3(int *a,int *A)
{
	*A=0; int x=1,y=*a/4*4+4-*a; if (y==4) A[++*A]=c4(x),x=0,y=0;
	rep(i,*a){x=x*2+a[i]; if (++y==4) A[++*A]=c4(x),x=0,y=0;}
}
int c2(int x){return x<65?x-48:x-55;}
void c1(char *A,int *a)
{
	bool flag=0; *a=0;
	rep(i,*A){
		int x=c2(A[i]);
		for (int j=3;j>=0;--j) if (flag) a[++*a]=x>>j&1; else if (x>>j&1) flag=1;
	}
}
void dfs(int *a,int &i,bool o)
{
	if (o) c[++*c]=a[i];
	if (a[i]){if (o) c[++*c]=a[i+1]; i+=2;}
	else{++i; rep(k,4) dfs(a,i,o);}
}
void work(int &i,int &j)
{
	if (i>*a || j>*b) return; 
	if (a[i]){dfs(b,j,a[i+1]); if (!a[i+1]) c[++*c]=1,c[++*c]=0; i+=2;}
	else if (b[j]){dfs(a,i,b[j+1]); if (!b[j+1]) c[++*c]=1,c[++*c]=0; j+=2;}
	else{
		c[++*c]=0; ++i,++j; int x=5,last=*c;
		rep(k,4) work(i,j),x=x>3?c[*c]:x!=c[*c]?3:x;
		if (*c-last==8 && x<2) c[*c=last]=1,c[++*c]=x;
	}
}
int main()
{
	while (scanf("%s%s",A+1,B+1),A[1]!='0' || B[1]!='0'){
		*A=strlen(A+1),c1(A,a),*B=strlen(B+1),c1(B,b),*c=0; int i=1,j=1; work(i,j);
		if (F) F=0; else puts(""); printf("Image %d:\n",++Case);
		c3(c,d); rep(k,*d) printf("%c",d[k]); puts("");
	}
	return 0;
}
