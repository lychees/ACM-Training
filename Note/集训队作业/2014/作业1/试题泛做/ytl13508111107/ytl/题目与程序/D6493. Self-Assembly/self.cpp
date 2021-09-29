#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 60
using namespace std;

int n,flag;
int opposite[N],go[N][N],a[10],Q[N],du[N];
char str[N];

int trans(char a,char b){
	if (a=='0') return -1;
	if (b=='+') return a-'A'+1;
	return a-'A'+1+26;
}
void init(){
	memset(go,0,sizeof(go));
	memset(du,0,sizeof(du));
}
int main(){
	freopen("self.in","r",stdin);
	freopen("self.out","w",stdout);
	for (int i=1;i<=26;i++) opposite[i]=i+26,opposite[i+26]=i;
	while (scanf("%d",&n)!=EOF){
		init();
		for (int i=1;i<=n;i++){
			scanf("%s",str);
			for (int j=1;j<=4;j++) a[j]=trans(str[(j-1)*2],str[(j-1)*2+1]);
			for (int j=1;j<=4;j++)
				for (int k=1;k<=4;k++) if (j!=k)
					if (a[j]!=-1&&a[k]!=-1&&!go[a[j]][opposite[a[k]]]){
						go[a[j]][opposite[a[k]]]=1;
						du[opposite[a[k]]]++;
					}
		}
		int p1,p2=0;
		for (int i=1;i<=52;i++) if (!du[i]) Q[++p2]=i;
		for (p1=1;p1<=p2;p1++){
			int u=Q[p1];
			for (int v=1;v<=52;v++) if (go[u][v]){
				du[v]--;
				if (!du[v]) Q[++p2]=v;
			}
		}
		printf("%s\n",p2<52?"unbounded":"bounded");
	}
	return 0;
}
