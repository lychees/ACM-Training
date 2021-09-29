#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define CH getchar()
char ch,last; int a[105],n,sign,flag,x,y,D,Case;
bool check(int y){long long res=0,x=1; rep(i,n) res=(res+x*a[i])%D,x=x*y%D; return res==0;}
bool work(){rep(i,n+1) if (!check(i)) return 0; return 1;}
int main()
{
	while ((ch=CH)!='.'){
		rep(i,101) a[i]=0; n=x=y=flag=0,sign=1;
		do{
			last=ch,ch=CH;
			if (last!='(' && ch=='-' || ch=='+' || ch==')'){
				if (last=='n') ++y; if (!flag) x=y+!y,y=0;
				n=max(n,y+1),a[y]=x*sign,x=y=flag=0,sign=1;
				}
			if (ch=='-') sign=-1; else if (ch=='+') sign=1;
			else if (ch>='0' && ch<='9') y=y*10+ch-48; else if (ch=='n') flag=1,x=y+!y,y=0;
		}while (ch!=')');
		CH; scanf("%d",&D); while ((ch=CH)!='\n');
		printf("Case %d: ",++Case);
		puts(work()?"Always an integer":"Not always an integer");
		}
	return 0;
}
