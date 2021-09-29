#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#define N 100000
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
int i,j,k,n,m;
int a[100],p10[20],p1[20],b[N];
inline int cal(int x) {
	return b[x/N]+b[x%N];
}
inline int xia(int x) {
	int A=x%10;
	if (A<3||A==5||A==8) return x+1;
	if (A==3||A==6) return x+2;
	if (A==4) return x+3;
	int s=0;
	for (;x%10==7;x/=10) s++;
	if (x%10==4) return (x+3)*p10[s]+p1[s]*4;
	int s1=cal(x);
	int y=x+1;
	if (s1==cal(y)) return y*p10[s]+p1[s]*4;
	if (s1==cal(y)+1) return y*p10[s]+p1[s+1]*4;
	if (s1==cal(y)-1) {
		if (s) return y*p10[s]+p1[s-1]*4;
		else {
			for (;y%10==0;) y/=10,s++;
			return (y+1)*p10[s];
		}
	}
}
int dfs(int x,int y) {
	if (y==1) return xia(x);
	int an=dfs(x/10,(x+y-1)/10-x/10+1)*10+x%10;
	if (y>=10) return an;
	else {
		int i,k;
		For(i,1,y) a[i]=cal(x+i-1);
		for (k=xia(x);k<an;k=xia(k)) {
			int F=0;
			For(i,1,y) if (a[i]!=cal(k+i-1)) {
				F=1; break;
			}
			if (!F) return k;
		}
		return an;
	}
}
int main() {
	For(i,0,N-1) {
		int A=i%10;
		b[i]=b[i/10]+(A==4||A==7);
	}
	p10[0]=1; For(i,1,19) p10[i]=p10[i-1]*10;
	For(i,1,19) p1[i]=p1[i-1]*10+1;
	scanf("%d%d",&n,&m);
	printf("%d\n",dfs(n,m));
	return 0;
}
