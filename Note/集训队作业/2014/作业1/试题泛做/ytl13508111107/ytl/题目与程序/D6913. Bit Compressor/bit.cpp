//By ytl 2014-1-7
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int len,n,l,ans;
char str[100];
void search(int now,int tot,int tot1){
    if (now==len+1){
        if (tot==l&&tot1==n) ans++;
        if (ans>1){
            printf("NOT UNIQUE\n");
            exit(0);
        }
        return;
    }
    if (str[now]=='0'){
        if (tot+1<=l) search(now+1,tot+1,tot1);
        return;
    }
    int r=min(len,now+16-1);
    if (now==len||str[now+1]=='0') search(now+1,tot+1,tot1+1);
    if (now+1<=len&&((str[now+1]=='1'&&now+1==len)||(str[now+1]=='1'&&str[now+2]=='0'))) search(now+2,tot+2,tot1+2); 
    int tt=0;
    for (int i=now;i<=r;i++){
        tt=(tt<<1)+(str[i]-'0');
        if (tot+tt>l||tot1+tt>n) break;
        if (i>=now+2&&(i==len||str[i+1]=='0')){
            search(i+1,tot+tt,tot1+tt);
        }
    }
}
int main(){
    freopen("bit.in","r",stdin);
    freopen("bit.out","w",stdout);
    scanf("%d%d",&l,&n);
    scanf("%s",str+1);
    len=strlen(str+1);
    search(1,0,0);
    printf("%s\n",ans?"YES":"NO");
    return 0;
}
