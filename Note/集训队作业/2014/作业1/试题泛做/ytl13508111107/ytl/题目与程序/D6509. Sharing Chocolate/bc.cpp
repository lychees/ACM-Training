#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 20
#define S 32768
using namespace std;
int g[S],Pow[N],n,num[N],f[110][S],head[S],next[S];

void build(int a,int b){
 next[b]=head[a];head[a]=b;
}
bool search(int x,int sum,int s){
    if (f[x][s]!=-1) return f[x][s];
    f[x][s]=0;
    int y=sum/x;
    for (int k=1;k<=(x>>1);k++){
        for (int i=head[k*y];i;i=next[i])
        if ((s|i)==s&&search(min(k,y),k*y,i)&&search(min(x-k,y),(x-k)*y,s-i)) return f[x][s]=1;
    }
    for (int k=1;k<=(y>>1);k++){
        for (int i=head[x*k];i;i=next[i])
        if ((s|i)==s&&search(min(x,k),x*k,i)&&search(min(x,y-k),x*(y-k),s-i)) return f[x][s]=1;
    }
    return 0;
}
bool work(){
    int x,y,all=(1<<n)-1;
    scanf("%d%d",&x,&y);
    int sum=0;
    for (int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        sum+=num[i];
    }
    if (sum!=x*y){
        printf("!!!\n");
        exit(0);
    }
    memset(f,0xff,sizeof(f));
    memset(head,0,sizeof(head));
    memset(g,0,sizeof(g));
    memset(next,0,sizeof(next));
    for (int i=1;i<all;i++){
        for (int j=1;j<=n;j++)
        if (i&(1<<(j-1))) g[i]+=num[j];
        build(g[i],i);
    }
    for (int i=0;i<n;i++){
        int len=(int)sqrt(num[i+1]);
        for (int j=1;j<=len;j++)
        if (num[i+1]%j==0) f[j][Pow[i]]=1;
    }
    return search(min(x,y),sum,all);
}
int main(){
    freopen("chocolate.in","r",stdin);
    freopen("bc.out","w",stdout);
    Pow[0]=1;
    for (int i=1;i<N;i++) Pow[i]=Pow[i-1]*2;
    int T=0;
    while (scanf("%d",&n)!=EOF){
        if (n==0) return 0;
        T++;
        printf("Case %d: ",T);
        if (work()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
