//By ytl 2014-1-7
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int use[30],len;
char str[1005];
int work(){
    for (int i=1;i<=26;i++) use[i]=0;
    for (int i=0;i<len;i++){
        int x=str[i]-'A'+1,t=0;
        for (int j=x;j<=26;j++) if (use[j]){
            use[j]=0;
            use[x]=1;
            t=1;
            break;
        }
        if (!t) use[x]=1;
    }
    int tot=0;
    for (int i=1;i<=26;i++) if (use[i]) tot++;
    return tot;
}
int main(){
    freopen("containers.in","r",stdin);
    freopen("containers.out","w",stdout);
    int cas=0;
    while (scanf("%s",str)!=EOF&&strcmp(str,"end")!=0){
        len=strlen(str);
        printf("Case %d: %d\n",++cas,work());
    }
    return 0;
}
