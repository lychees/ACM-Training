#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100,inf = 100000000;
int can[2000*50+10],button = 0,n;
int stack[maxn],type[maxn];
char str[50];
int main()
{
    freopen("pilgrimage.in","r",stdin);
    freopen("pilgrimage.out","w",stdout);
    while(scanf("%d",&n)==1 && n){
        int add = 0,top = 0,minv = 0,maxv = 0,num = 0,k;
        for(int i=1;i<=n;i++){
            scanf("%s %d",str,&k);
            if(str[0]=='I'){
                add+=k;
                stack[++top]=k;type[top]=1;
                }else if(str[0]=='O'){
                    add-=k;minv=min(minv,add);
                    stack[++top]=k;type[top]=2;
                    }else if(str[0]=='P'){
                        if(top){
                            if(type[top]!=3)
                                stack[++top]=k;
                            else stack[top]+=k;
                            type[top]=3;
                            }
                        }
            }
        int derta = 0;
        for(int i=1;i<top;i++){
            if(type[i]==1)derta+=stack[i];
            if(type[i]==2)derta-=stack[i];
            if(type[i]!=3)continue;
                maxv = max(maxv,stack[i]-derta);
                num++;
                for(int q=1;q<=stack[i];q++)
                    if(q>derta && stack[i]%q==0){
                        if(can[q-derta]<=button)can[q-derta]=button;
                        //if(can[stack[i]/q-derta]<=button)can[stack[i]/q-derta]=button;
                        can[q-derta]++;
                        //if(q*q<stack[i])can[stack[i]/q-derta]++;
                        }
                }
        if(num == 0){
            printf("SIZE >= %d\n",-minv+1);
            }else{
            bool ok = 0;
            //cout<<"maxv = "<<maxv<<endl;
            for(int i=-minv+1;i<=maxv;i++)
                if(can[i]==button + num){
                    printf("%d ",i);
                    ok=1;
                    }
            if(!ok)printf("IMPOSSIBLE");
            putchar('\n');
            }
        button += num+10;
        }
    
    return 0;
}
