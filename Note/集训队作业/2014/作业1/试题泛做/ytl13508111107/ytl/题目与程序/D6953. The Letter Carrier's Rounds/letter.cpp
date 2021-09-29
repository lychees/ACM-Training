//By ytl 2013-11-13
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#define N 200005
using namespace std;

struct data{
	int tot;
	set<string> user; 
};
map<string,data> mta;
typedef map<string,data>::iterator it;
struct dat{
	string a,b;int num,id;
}; 

int tt,tot,talkTot;
dat rec[N];
char talk[N][200],st[200];
string str;
map<string,int> names;
set<string> have;
typedef map<string,int>::iterator its;

int rep(dat &u){
	it i=mta.find(u.a);
	return (i->second).user.find(u.b)!=(i->second).user.end()?250:550;
}
void connect(int l,int r){
	cout<<"Connection between "<<rec[1].a<<" and "<<rec[l].a<<endl;
	cout<<"     HELO "<<rec[1].a<<endl;
	cout<<"     "<<250<<endl;
	cout<<"     MAIL FROM:<"<<rec[1].b<<"@"<<rec[1].a<<">"<<endl;
	cout<<"     "<<250<<endl;
	int findOne=0;
	for (int i=l;i<=r;i++){
		int t=rep(rec[i]);
		if (t==250) findOne=1;
		cout<<"     RCPT TO:<"<<rec[i].b<<"@"<<rec[i].a<<">"<<endl;
		cout<<"     "<<t<<endl;
	}
	if (findOne){
		cout<<"     DATA"<<endl;
     	cout<<"     354"<<endl;
     	for (int i=1;i<=talkTot;i++) printf("     %s\n",talk[i]);
		printf("     .\n");
		printf("     250\n");
	}
	printf("     QUIT\n");
	printf("     221\n");
}
bool cmp(const dat &x,const dat &y){
	return x.id<y.id||(x.id==y.id&&x.num<y.num);
}
void output(){
	sort(rec+2,rec+tt+1,cmp);
	int l=2,r=2;
	while (r<=tt){
		while (rec[r].a==rec[l].a) r++;
		connect(l,r-1);
		l=r;
	}
}
void trans(const string &str,string &a,string &b){
	a="";b="";
	int len=str.size();
	int flag=1;
	for (int i=0;i<len;i++){
		if (str[i]=='@') {flag=0;continue;}
		if (flag) a+=str[i];else b+=str[i];
	}
}
void getID(){
	int kk=0;
	names.clear();
	for (int i=2;i<=tt;i++){
		its j=names.find(rec[i].a);
		if (j!=names.end()) rec[i].id=j->second;
		else{
			kk++;
			names[rec[i].a]=kk;
			rec[i].id=kk;
		}
	}
}

int main(){
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	while (cin>>str&&str!="*"){
		if (str=="MTA"){
    		tot++;
            data a;string name;
            cin>>name;
            cin>>a.tot;
            for (int i=1;i<=a.tot;i++){
                cin>>str;
                a.user.insert(str);
            }
           	mta.insert(pair<string,data>(name,a));
		}
	}
	while (cin>>str&&str!="*"){
		have.clear();
		tt=1;
		trans(str,rec[1].b,rec[1].a);
		while (cin>>str&&str!="*"){
			if (have.find(str)!=have.end()) continue;
			have.insert(str);
			tt++;
			trans(str,rec[tt].b,rec[tt].a);
			rec[tt].num=tt;
		}
		getID();
		getchar();
		talkTot=0;
		while (gets(st)&&strcmp(st,"*")!=0){
			strcpy(talk[++talkTot],st);
		}
		output();
	}
	return 0;
}

