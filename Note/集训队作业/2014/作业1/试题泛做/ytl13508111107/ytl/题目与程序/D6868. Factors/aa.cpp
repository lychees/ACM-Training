#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
typedef long long LL;
typedef map<LL,LL>::iterator it;

map<LL,LL> my;
LL x,y;
int main(){
	freopen("search.out","r",stdin);
	freopen("biao.out","w",stdout);
	while (scanf("%I64d%I64d",&x,&y)!=EOF){
		if (x==1) continue;
		if (my.find(y)==my.end()){
			my[y]=x;
		}else my[y]=min(my[y],x); 
	}
	//printf("%d\n",my.size());
	//for (it i=my.begin();i!=my.end();i++) printf("%I64d %I64d\n",i->first,i->second);
	for (it i=my.begin();i!=my.end();i++) printf(",%I64d",i->first);printf("\n");
	for (it i=my.begin();i!=my.end();i++) printf(",%I64d",i->second);printf("\n");
	return 0;
}
