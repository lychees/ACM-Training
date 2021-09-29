//By ytl 2013-11-11
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 30
#define M 30
using namespace std;

int tot,all,tt[N],query;
string page[N][M],str[M];
struct data{int x,num;}w[N];


bool cmp(const data &a,const data &b){
	return a.x>b.x||(a.x==b.x&&a.num<b.num);
}

int main(){
	freopen("page.in","r",stdin);
	freopen("page.out","w",stdout);
	char op;
	printf("Query Pages\n");
	while (scanf("%c",&op)!=EOF&&op!='E'){
		for (int i=1;i<=tot;i++) str[i]="";tot=0;
		while (1){
			char c=getchar();
			while (c<=32&&c!='\n') c=getchar();
			if (c=='\n') break;
			tot++;
			while (c>32&&c!='\n'){
				if (c>='A'&&c<='Z') c=c-'A'+'a';
				str[tot]+=c;
				c=getchar();
			}
			if (c=='\n') break;
		}
		if (op=='P'){
			all++;
			for (int i=1;i<=tot;i++) page[all][i]=str[i];
			tt[all]=tot;
			continue;
		}
		else if (op=='Q'){
			for (int i=1;i<=all;i++){
				w[i].num=i;
				w[i].x=0;
				for (int j=1;j<=tt[i];j++)
					for (int k=1;k<=tot;k++)
						if (page[i][j]==str[k]) 
							w[i].x+=(8-j+1)*(8-k+1);
			}
			sort(w+1,w+all+1,cmp);
			printf("Q%d:",++query);
			for (int i=1;i<=min(all,5);i++) if (w[i].x) printf(" P%d",w[i].num);
			printf("\n");	
		}
	}
	return 0;
}
