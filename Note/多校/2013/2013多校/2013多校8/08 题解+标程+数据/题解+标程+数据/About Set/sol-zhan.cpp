#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>

#define LL(x) ch[x][0]
#define RR(x) ch[x][1]

using namespace std;

const int MaxN=100005*2;
const int INF=1000000000;
int n;
int ch[MaxN][2],tot[MaxN],size,rt,begin[MaxN],end[MaxN],ans[MaxN],root[MaxN];
int f[MaxN];
int set[MaxN];
int v[MaxN];
queue<int> Q,Q1;

int gcd(int a,int b)
{
    if(b==0)return a;
    else return gcd(b,a%b);
}

void update(int tmp)
{
    if(LL(tmp))begin[tmp]=begin[LL(tmp)];
    else begin[tmp]=v[tmp];
    if(RR(tmp))end[tmp]=end[RR(tmp)];
    else end[tmp]=v[tmp];
    ans[tmp]=gcd(v[tmp],gcd(ans[LL(tmp)],ans[RR(tmp)]));
}

void Right_Rotate(int &rt)
{
    int tmp=LL(rt);
    LL(rt)=RR(tmp);
    RR(tmp)=rt;
    tot[tmp]=tot[rt];
    tot[rt]=tot[LL(rt)]+tot[RR(rt)]+1;
    rt=tmp;
    update(RR(rt));
    update(rt);
}

void Left_Rotate(int &rt)
{
    int tmp=RR(rt);
    RR(rt)=LL(tmp);
    LL(tmp)=rt;
    tot[tmp]=tot[rt];
    tot[rt]=tot[LL(rt)]+tot[RR(rt)]+1;
    rt=tmp;
    update(LL(rt));
    update(rt);
}

void Maintain(int &rt,bool flag)
{
    if(rt==0) return;
    if(flag)
    {
        if(tot[RR(RR(rt))]>tot[LL(rt)])
            Left_Rotate(rt);
        else if(tot[LL(RR(rt))]>tot[LL(rt)])
        {
            Right_Rotate(RR(rt));
            Left_Rotate(rt);
        }
        else return;
    }
    else
    {
        if(tot[LL(LL(rt))]>tot[RR(rt)])
            Right_Rotate(rt);
        else if(tot[RR(LL(rt))]>tot[RR(rt)])
        {
            Left_Rotate(LL(rt));
            Right_Rotate(rt);
        }
        else return;
    }
    Maintain(LL(rt),false);
    Maintain(RR(rt),true);
    Maintain(rt,false);
    Maintain(rt,true);
}

int find(int &rt,int num)
{
    if(rt==0||num==v[rt])return v[rt];
    if(num<v[rt])
    {
        int x=find(LL(rt),num);
        if(x==0)return v[rt];
    }
    else return find(RR(rt),num);
}

void insert(int &rt,int num)
{
    if(rt==0)
    {
        rt=Q.front();
        Q.pop();
        LL(rt)=RR(rt)=0;
        tot[rt]=1;
        v[rt]=num;
        begin[rt]=end[rt]=num;
        ans[rt]=num;
        return;
    }
    tot[rt]++;
    if(num<v[rt])
        insert(LL(rt),num);
    else
        insert(RR(rt),num);
    update(rt);
    if(num<v[rt])
        Maintain(rt,false);
    else
        Maintain(rt,true);
}

int delet(int &rt,int num)
{
    //printf("%d:%d  %d,%d    %d\n",n,rt,LL(rt),RR(rt),v[rt]);
    tot[rt]--;
    if(num==v[rt]||(num<v[rt]&&LL(rt)==0)||(num>v[rt]&&RR(rt)==0))
    {
        int tmp=v[rt];
        if(LL(rt)==0||RR(rt)==0)
        {
            Q.push(rt);
            rt=LL(rt)+RR(rt);
            if(rt)update(rt);
        }
        else
        {
            v[rt]=delet(LL(rt),num+1);
            update(rt);
        }
        return tmp;
    }
    if(num<v[rt])
    {
        int x=delet(LL(rt),num);
        update(rt);
        return x;
    }
    else
    {
        int x=delet(RR(rt),num);
        update(rt);
        return x;
    }
}

int find_kth(int &rt,int k)
{
    int tmp=tot[rt]-tot[RR(rt)];
    if(tmp==k)
        return v[rt];
    if(k<tmp)
        return find_kth(LL(rt),k);
    else
        return find_kth(RR(rt),k-tmp);
}
void init()
{
    LL(rt)=RR(rt)=0;
    tot[0]=0;
    v[0]=0;
    while(!Q.empty())Q.pop();
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&f[i]);
        Q.push(i);
        Q.push(i+n);
        set[i]=set[i+n]=i+n;
        root[i+n]=0;
        begin[i+n]=end[i+n]=0;
        LL(i+n)=RR(i+n)=0;
        tot[i+n]=0;
        insert(root[i+n],f[i]);
    }
}

int find(int x)
{
    if(x==set[x])return x;
    else return set[x]=find(set[x]);
}

void dfs(int rt)
{
    if(rt==0)return;
    dfs(LL(rt));
    dfs(RR(rt));
    //printf("find %d\n",v[rt]);
    Q.push(rt);
    Q1.push(v[rt]);
}

int dfs2(int rt,int l,int r)
{
    //printf("%d[%d,%d]%d [%d,%d] [%d,%d] (%d,%d)\n",tot[rt],begin[rt],end[rt],v[rt],begin[LL(rt)],end[LL(rt)],begin[RR(rt)],end[RR(rt)],l,r);
    if(l<=begin[rt] && end[rt]<=r)return ans[rt];
    int p;
    if(l<=v[rt] && v[rt]<=r)p=v[rt];
    else p=0;
    if(LL(rt)&& l<=end[LL(rt)])p=gcd(p,dfs2(LL(rt),l,r));
    if(RR(rt)&& begin[RR(rt)]<=r)p=gcd(p,dfs2(RR(rt),l,r));
    return p;
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int m,p,u,v,l,r,x,a,b,ans,cas=0,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        printf("Case #%d:\n",++cas);
        init();
        while(m--)
        {
            scanf("%d",&p);
            if(p==1)
            {
                scanf("%d%d",&u,&v);
                u=find(u);
                v=find(v);
                if(u==v)continue;
                if(tot[root[u]]>tot[root[v]])swap(u,v);
                set[u]=v;
                while(!Q1.empty())Q1.pop();
                dfs(root[u]);
                while(!Q1.empty())
                {
                    //printf("insert %d\n",Q1.front());
                    insert(root[v],Q1.front());
                    Q1.pop();
                }
            }
            else if(p==2)
            {
                scanf("%d%d",&u,&v);
                delet(root[find(u)],f[u]);
                insert(root[find(v)],f[u]);
                set[u]=find(v);
            }
            else if(p==3)
            {
                scanf("%d%d",&u,&x);
                delet(root[find(u)],f[u]);
                f[u]=x;
                insert(root[find(u)],f[u]);
            }
            else if(p==4)
            {
                scanf("%d",&u);
                u=find(u);
                if(tot[root[u]]==1)
                {
                    puts("1");
                    continue;
                }
                a=find_kth(root[u],1);
                b=find_kth(root[u],2);
                ans=2;
                do
                {
                    x=find(root[u],a+b);
                    if(x)
                    {
                        a=b;
                        b=x;
                        ans++;
                    }
                }while(x);
                printf("%d\n",ans);
            }
            else if(p==5)
            {
                scanf("%d%d%d",&u,&l,&r);
                u=find(u);
                x=dfs2(root[u],l,r);
                if(x==0)x=-1;
                printf("%d\n",x);
            }
        }
    }
    return 0;
}
