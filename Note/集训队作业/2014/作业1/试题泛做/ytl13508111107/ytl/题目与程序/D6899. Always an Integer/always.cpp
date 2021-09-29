//By ytl 2013-11-21
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;


string str,st;int len;
int now;
LL C,E,D;
LL xi[200],zhi[200];

inline LL Mod(LL a){return a<D?a:a%D;}
int randM(){
	return rand()|(rand()<<15)|((rand()&1)<<30);
}

bool check(LL n){
	if (n==-1) n=randM();
	zhi[0]=1;
	for (int i=1;i<=100;i++) zhi[i]=Mod(zhi[i-1]*n);
	
	LL ans=0;
	for (int i=0;i<=100;i++) if (xi[i])
		ans=Mod(ans+xi[i]*zhi[i]);
	return ans==0;
}

void readA(LL &a){
	a=0;char c=str[now++];
	if (c=='n'){
		a=1;
		return;
	}
	while (c!='n'&&c!=')'){
		a=a*10+c-'0';
		c=str[now++];
	}
}
void readB(LL &a){
	a=0;char c=str[now++];
	if (c!='^'){
		now--;
		a=1;
		return;
	}
	c=str[now++];
	while (c>='0'&&c<='9'){
		a=a*10+c-'0';
		c=str[now++];
	}
	now--;
}
void deal(){
	for (int i=0;i<=100;i++) xi[i]=0;
	if (str[1]!='-'&&str[1]!='+'){
		str[0]='+';
		now=0;
	}else now=1;
	while (str[now]!=')'){
		int t=(str[now++]=='+');
		readA(C);
		if (str[now-1]==')'){
			now--;
			xi[0]=t?C:-C;
			break;
		}
		readB(E);
		xi[E]=t?C:-C;
	}
	now+=2;
	D=0;
	for (int i=now;i<len;i++) if (str[i]!=')'&&str[i]!='('){
		D=D*10+str[i]-'0';
	} 
}
int main(){
	freopen("always.in","r",stdin);
	freopen("always.out","w",stdout);
	int cas=0;
	while (cin>>str&&str!="."){
		len=str.size();
		deal();
		int flag=0;
		for (int i=0;i<=10000;i++) if (!check(i)){
			flag=1;
			break;
		}
		for (int i=1;i<=1000;i++) if (!check(-1)){
			flag=1;
			break;
		}
		//printf("!%I64d\n",D);
		if (flag) printf("Case %d: Not always an integer\n",++cas);
		else printf("Case %d: Always an integer\n",++cas);	
	}
	return 0;
}
