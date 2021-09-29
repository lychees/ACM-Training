#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
const int maxn = 110,maxm = 510;
typedef struct TwoSet{
    int head[maxn*2],next[3*4*500+100],to[3*4*500+100],op;
    int n,mark[maxn*2],stack[maxn],top;
    
    void init(int n){
        this->n=n;
        memset(head,0,sizeof(head));
        memset(mark,0,sizeof(mark));
        op=0;
        }
    void build(int a,int b){
        next[++op]=head[a];head[a]=op;to[op]=b;
        }
    bool dfs(int u){
        if(mark[u])return 1;
        if(mark[u^1])return 0;
        mark[u]=1;
        stack[++top]=u;
        for(int pos=head[u];pos;pos=next[pos])
            if(!dfs(to[pos]))return 0;
        return 1;
        }
    
    void build(int x,int b1,int y,int b2){
        //cout<<x<<" "<<b1<<" "<<y<<" "<<b2<<endl;
        build(x*2+b1,y*2+b2);
        }
    bool solve(){
        for(int i=1;i<=n;i++){
            top = 0;
            if(!dfs(i*2)){
                while(top)mark[stack[top--]]=0;
                if(!dfs(i*2+1))return 0;
                }
            }
        return 1;
        }
    };
TwoSet T;
int n,m;
int K[maxm],Num[maxm][4],Type[maxm][4],data[maxn];
bool isok(int k,int b){
    //cout<<"------   DEBUG  ---------"<<endl;
    T.init(n);
    T.build(k,b^1,k,b);
    
    for(int i=1;i<=m;i++)
        if(K[i]<=2){
            for(int q=0;q<K[i];q++)
                T.build(Num[i][q],Type[i][q]^1,Num[i][q],Type[i][q]);
            }else{
            for(int q=0;q<K[i];q++)
                for(int p=0;p<K[i];p++)
                    if(q!=p)T.build(Num[i][q],Type[i][q]^1,Num[i][p],Type[i][p]);
            }
    
    return T.solve();
    }
bool solve(){
    for(int i=1;i<=n;i++){
        if(isok(i,0)){
            if(isok(i,1))data[i]=3;
            else data[i]=0;
            }else{
            if(isok(i,1))data[i]=1;
            else return 0;
            }
        //break;
        }
    for(int i=1;i<=n;i++)
        if(data[i]==3)
            putchar('?');
        else putchar(data[i]?'y':'n');
    return 1;
    }
int main()
{
    char c;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&K[i]);
        for(int q=0;q<K[i];q++){
            scanf("%d%s",&Num[i][q],&c);
            Type[i][q]=(c=='y');
            }
        }
    if(!solve())
        printf("impossible\n");
    
    return 0;   
}
