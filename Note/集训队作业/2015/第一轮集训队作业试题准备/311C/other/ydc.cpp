#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 100010
#define maxk 10010
using namespace std;
typedef long long LL;
LL h,line[40];
bool use[maxn];
int ntc,nQuery,k,nLine;
struct TreasureCell
{
    LL id;
    int value;
    bool Can;
}cell[maxn];
struct Node_Graph
{
    LL dis;
    int id;
    friend bool operator < (const Node_Graph &a,const Node_Graph &b)
    {
        return a.dis>b.dis;
    }
    Node_Graph() {}
    Node_Graph(LL dis,int id): dis(dis),id(id) {}
};
struct Node_Cell
{
    int value,id;
    friend bool operator < (const Node_Cell &a,const Node_Cell &b)
    {
        return a.value<b.value||(a.value==b.value&&a.id>b.id);
    }
    Node_Cell() {}
    Node_Cell(int value,int id): value(value),id(id) {}
};
priority_queue<Node_Cell> Q;
void Dijkstra(int p)
{
    priority_queue<Node_Graph> heap;
    static LL dis[maxk];
    for(int i=0;i<k;i++)
        dis[i]=h+1;
    dis[1]=0;
    Node_Graph head;
    heap.push(Node_Graph(0,1));
    while(!heap.empty())
    {
        head=heap.top(),heap.pop();
        if(dis[head.id]!=head.dis)
            continue;
        for(int i=1;i<=nLine;i++)
        {
            int q=(head.id+line[i])%k;
            if(dis[q]>head.dis+line[i])
            {
                dis[q]=head.dis+line[i];
                heap.push(Node_Graph(dis[q],q));
            }
        }
    }
    while(!Q.empty())
        Q.pop();
    for(int i=1;i<=ntc;i++)
    {
        cell[i].Can=cell[i].id>=dis[cell[i].id%k];
        if(cell[i].Can==true&&!use[i])
            Q.push(Node_Cell(cell[i].value,i));
    }
}
void read()
{
    scanf("%lld %d %d %d",&h,&ntc,&nQuery,&k);
    for(int i=1;i<=ntc;i++)
        scanf("%lld %d",&cell[i].id,&cell[i].value);
    Dijkstra(0);
}
void Query()
{
    for(int i=1,a,b,c;i<=nQuery;i++)
    {
        scanf("%d",&a);
        if(a==1)
        {
            scanf("%lld",&line[++nLine]);
            Dijkstra(0);
        }
        if(a==2)
        {
            scanf("%d %d",&b,&c);
            if(c==0)
                continue;
            cell[b].value-=c;
            if(cell[b].Can==true&&!use[b])
                Q.push(Node_Cell(cell[b].value,b));
        }
        if(a==3)
        {
            while(!Q.empty()&&cell[Q.top().id].value!=Q.top().value)
                Q.pop();
            if(Q.empty())
            {
                printf("0\n");
                continue;
            }
            use[Q.top().id]=true;
            printf("%d\n",Q.top().value);
            Q.pop();
        }
    }
}
int main()
{
    read();
    Query();
    return 0;
}
