#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=5005;
int Case,F=1,n,m,x,y,w,sum,a[N],b[N],p[N],v[N*16]; char opr[3]; string s; map<string,int> H;
bool read(int &x)
{
	#define CH getchar()
	char ch; x=0; for (ch=CH;!isalnum(ch);ch=CH) if (ch=='$') return 0;
	for (;isalnum(ch);x=x*16+(ch<'A'?ch-48:ch-55),ch=CH); return 1;
}
void prt(int x,bool flag)
{
	if (!x && flag) printf("????");
	else for (int i=12,y;i>=0;i-=4) y=x>>i&15,printf("%c",y<10?y+48:y+55);
}
int get(string s){if (H.find(s)==H.end()) H[s]=++n,a[n]=b[n]=0; return H[s];}
void chg(int &x){int y=x>>15&1; x=x<<1&65535,x+=y;}
int main()
{
	while (scanf("%s",opr),*opr!='$'){
		H.clear(),n=m=w=sum=0;
		while (*opr!='$'){
			if (*opr=='Z') m=0;
			else if (*opr=='C'){
				read(y);
				rep(i,y) if (read(x)) v[w++]=x; else read(x),v[w++]=-p[x],++i,++w;
			}else{
				cin>>s,x=get(s);
				if (*opr=='E') p[m++]=x;
				else read(y),a[x]?b[x]=1:a[x]=y+w+256;
			}
			scanf("%s",opr);
		}
		rep(i,w){
			chg(sum);
			if (v[i]<0) sum+=a[-v[i]]>>8,chg(sum),sum+=a[-v[i++]]&255;
			else sum+=v[i];
			}
		if (F) F=0; else puts(""); printf("Case %d: checksum = ",++Case); prt(sum&65535,0);
		puts(""),puts(" SYMBOL   ADDR"),puts("--------  ----");
		for (map<string,int> :: iterator i=H.begin();i!=H.end();++i){
			s=i->first,x=i->second;
			cout<<s; rep(i,10-s.size()) putchar(' '); prt(a[x],1);
			if (b[x]) printf(" M"); puts("");
		}
	}
	return 0;
}
