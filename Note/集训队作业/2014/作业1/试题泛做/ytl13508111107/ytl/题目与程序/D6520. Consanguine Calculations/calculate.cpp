#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

char ch[6]={'#','A','B','O','+','-'};

set<string> my;
typedef set<string>::iterator it;

string a,b,c,son[20];
int tot;

string join1(char x,char y){
	if (x=='A'&&y=='A') return "A";
	if ((x=='A'&&y=='B')||(x=='B'&&y=='A')) return "AB";
	if ((x=='A'&&y=='O')||(x=='O'&&y=='A')) return "A";
	if (x=='B'&&y=='B') return "B";
	if ((x=='B'&&y=='O')||(x=='O'&&y=='B')) return "B";
	if (x=='O'&&y=='O') return "O";
	return "";
}
bool check(char x,char y,string &a){
	a=join1(x,y);
	if (a=="") return false;
	else return true;
}
string join2(char x,char y){
	if (x=='+'||y=='+') return "+";
	else return "-";
}
void get(char x,char y,string &a){
	a+=join2(x,y);
}
void newAns(string &a){
	if (my.find(a)==my.end()) my.insert(a);		
}
string deal(string a){
	if (a!="?") return a;
	if (my.empty()) return "IMPOSSIBLE";
	if (my.size()==1) return *my.begin();
	string b="{"+*my.begin();
	for (it i=(++my.begin());i!=my.end();i++) b+=", "+*i;
	b+="}";
	return b;
}
void makeson(char a1,char a2,char a3,char a4,char b1,char b2,char b3,char b4){
	tot=0;
	char tt[9]={'#',a1,a2,a3,a4,b1,b2,b3,b4};
	for (int x1=1;x1<=2;x1++)
	for (int x2=3;x2<=4;x2++)
	for (int x3=5;x3<=6;x3++)
	for (int x4=7;x4<=8;x4++){
		string e=join1(tt[x1],tt[x3]);
		if (e!="") son[++tot]=e+join2(tt[x2],tt[x4]);
	}
}
void work(int cas){
	my.clear();
	string u="",v="";
	for (int x1=1;x1<=3;x1++){char a1=ch[x1];
	for (int x2=1;x2<=3;x2++){char a2=ch[x2];
	for (int x3=4;x3<=5;x3++){char a3=ch[x3];
	for (int x4=4;x4<=5;x4++){char a4=ch[x4];
	for (int y1=1;y1<=3;y1++){char b1=ch[y1];
	for (int y2=1;y2<=3;y2++){char b2=ch[y2];
	for (int y3=4;y3<=5;y3++){char b3=ch[y3];
	for (int y4=4;y4<=5;y4++){char b4=ch[y4];
		if (!check(a1,a2,u)) continue;
		if (!check(b1,b2,v)) continue;
		get(a3,a4,u);
		get(b3,b4,v);
		if (c=="?"){
			if (a==u&&b==v){
				makeson(a1,a2,a3,a4,b1,b2,b3,b4);
				for (int i=1;i<=tot;i++) newAns(son[i]);
			}
		}else{
			makeson(a1,a2,a3,a4,b1,b2,b3,b4);
			for (int i=1;i<=tot;i++) if (son[i]==c){
				if (a==u) newAns(v);
				if (b==v) newAns(u);
			}
		}
	}}}}}}}}
	cout<<"Case "<<cas<<": "<<deal(a)<<" "<<deal(b)<<" "<<deal(c)<<endl; 
}
int main(){
	freopen("calculate.in","r",stdin);
	freopen("calculate.out","w",stdout);
	int cas=0;
	while (cin>>a>>b>>c&&!(a=="E"&&b=="N"&&c=="D")) work(++cas);          
	return 0;
}
